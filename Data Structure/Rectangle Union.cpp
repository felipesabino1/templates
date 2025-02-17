template <class TTT = int>
struct RectangleUnion{
    vector<TTT> compressed; // ordered coordinates
    TTT N; // total covered length

    template <class TT = TTT>
    struct Seg{
        // allocate the needed size
        Seg(int n,const vector<TT> & compressed) : n(n), compressed(compressed){
            seg.resize(n<<2);
            lazy.resize(n<<2);
        }

        // init the structure
        void init(int n_new){
            n = n_new;
            seg.resize(n<<2);
            lazy.resize(n<<2);
            build(1,1,n);
        }

        // info of each node
        struct node{
            TT mini, qt;
            TT l_min, r_min;
            TT tl, tr;

            node(){}
            node(TT mini, TT qt,TT l_min = 0, TT r_min = 0, TT tl = 0,TT tr = 0) : mini(mini), qt(qt), l_min(l_min), r_min(r_min), tl(tl), tr(tr){}

            bool operator ==(const node & ot)const{
                return mini == ot.mini && qt == ot.qt && l_min == ot.l_min && r_min == ot.r_min && tl == ot.tl && tr == ot.tr;
            }

            void show(){
                cout << mini << ' ' << qt << ' ' << l_min << ' ' << r_min << ' ' << tl << ' ' << tr << endl;
            }
        };
        // info of each lazy node
        struct sono{
            TT qt;
            bool operator ==(const sono &ot)const{
                return qt == ot.qt;
            }
        };

        int n; // count of nodes
        const vector<TT> &compressed;
        const node off = {-1,-1,-1,-1,-1,-1}; // null node
        const sono off_lazy = {0}; // null lazy node
        vector<node> seg;
        vector<sono> lazy;
        // merge two nodes
        node merge(node x, node y){
            if(x == off) return y;
            if(y == off) return x;
            node ret;
            ret.mini = min(x.mini, y.mini);
            ret.qt = 0;
            if(x.mini == ret.mini) ret.qt += x.qt;
            if(y.mini == ret.mini) ret.qt += y.qt;
            
            if(min(x.r_min, y.l_min) == ret.mini) ret.qt += y.tl - x.tr - 1;

            ret.l_min = x.l_min, ret.r_min = y.r_min;
            ret.tl = x.tl, ret.tr = y.tr;
            
            return ret;
        }

        // spread the lazy
        void push(int u,int tl,int tr){
            if(tl == tr || lazy[u] == off_lazy) return;
            // update the sons
            seg[lef(u)].mini += lazy[u].qt;
            seg[rig(u)].mini += lazy[u].qt;

            seg[lef(u)].l_min += lazy[u].qt, seg[lef(u)].r_min += lazy[u].qt;
            seg[rig(u)].l_min += lazy[u].qt, seg[rig(u)].r_min += lazy[u].qt;

            // update the sons's lazies
            lazy[lef(u)].qt += lazy[u].qt;
            lazy[rig(u)].qt += lazy[u].qt;

            lazy[u]=off_lazy;
        }

        // init the seg 
        void build(int u,int tl,int tr){
            if(tl == tr){
                // init the bases nodes
                seg[u] = node(0,1,0,0,compressed[tl-1],compressed[tl-1]);
                lazy[u]=off_lazy;
                return;
            }
            int tmid=tl+tr;
            tmid>>=1;
            build(lef(u),tl,tmid);
            build(rig(u),tmid+1,tr);
            seg[u]=merge(seg[lef(u)],seg[rig(u)]);
            lazy[u]=off_lazy;
        }

        // range query
        node query_(int u,int tl,int tr,int l, int r){
            if(l > r) return off;
            if(tl == l && tr == r) return seg[u];
            push(u,tl,tr);
            int tmid=tl+tr;
            tmid>>=1;
            return merge(query_(lef(u),tl,tmid,l,min(tmid,r)),query_(rig(u),tmid+1,tr,max(tmid+1,l),r));
        }
        node query(int l,int r){
            return query_(1,1,n,l,r);
        }

        // range update
        void update_(int u,int tl,int tr,int l,int r,TT x){
            if(l > r) return;
            if(tl == l && tr == r){
                // update seg and lazy
                seg[u].mini += x;
                seg[u].l_min += x, seg[u].r_min += x;
                lazy[u].qt += x;
                return;
            }
            push(u,tl,tr);
            int tmid=tl+tr;
            tmid>>=1;
            update_(lef(u),tl,tmid,l,min(tmid,r),x);
            update_(rig(u),tmid+1,tr,max(tmid+1,l),r,x);
            seg[u]=merge(seg[lef(u)],seg[rig(u)]);
        }
        void update(int l,int r, TT x){
            update_(1,1,n,l,r,x);
        }
    };
    Seg<TTT> seg; // segment tree

    RectangleUnion(vector<TTT> &coord) : seg(compressed.size(),compressed){
        for(int v : coord){
            compressed.push_back(v-1);
            compressed.push_back(v);
        }
        sort(compressed.begin(),compressed.end());
        compressed.erase(unique(compressed.begin(), compressed.end()),compressed.end());        
        N = compressed.back() - compressed[0] + 1;
        seg.init(compressed.size());
    }

    int compress(TTT x){return lower_bound(compressed.begin(), compressed.end(), x) - compressed.begin() + 1;} 
    // if it's compressed, pass the compressed coordinates
    void update(int l,int r,TTT v){ 
        seg.update(l,r-1,v); // segment
    }  
    int covered_length(){
        auto ret = seg.query(1,compressed.size());
        return (ret.mini > 0 ? N : N - ret.qt);
    }
};
