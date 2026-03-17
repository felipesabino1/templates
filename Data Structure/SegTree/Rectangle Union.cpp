template <class T = ll>
struct RectangleUnion{
    vc<T> comp; // coord comprimida
    T N; // tamanho total

    struct Seg{
        Seg(vc<T>& vecc) : vec(vecc){}
        void init(int nn){
            n = nn;
            seg.resize(n<<2), lazy.resize(n<<2);
            build(1,1,n);
        }
        struct node{
            T val,qt;
            T vl,vr; // o valor do cara mais a esq e dir
            T l,r; // range real do node nas coord
        };
        struct sono{
            T qt;
        };

        int n;
        vc<node> seg; vc<sono> lazy;
        vc<T>& vec;
        node ret,aux;
        void merge(node& x, node& y, node& at){
            if(x.val == -1) return void(at = y);
            if(y.val == -1) return void(at = x);
            at.val = min(x.val,y.val), at.qt = 0;
            at.qt += (x.val == at.val) * x.qt;
            at.qt += (y.val == at.val) * y.qt;
            at.qt += (min(x.vr,y.vl) == at.val) * (y.l-x.r-1);
            at.vl = x.vl, at.vr = y.vr, at.l = x.l, at.r = y.r;
        }
        void apply(int u,sono& upd){
            seg[u].val += upd.qt, seg[u].vl += upd.qt, seg[u].vr += upd.qt;
            lazy[u].qt += upd.qt;
        }
        void push(int u,int tl,int tr){
            if(tl == tr || !lazy[u].qt) return;
            apply(lef(u),lazy[u]), apply(rig(u),lazy[u]);
            lazy[u] = {0};
        }
        void build(int u,int tl,int tr){
            if(tl == tr){
                seg[u] = {0,1,0,0,vec[tl-1],vec[tl-1]};
                lazy[u] = {0};
                return;
            }
            int tmid=tl+tr; tmid>>=1;
            build(lef(u),tl,tmid), build(rig(u),tmid+1,tr);
            merge(seg[lef(u)],seg[rig(u)],seg[u]), lazy[u] = {0};
        }
        void query(int u,int tl,int tr,int l, int r){
            if(l > r) return;
            if(tl == l && tr == r) return merge(aux = ret,seg[u],ret);
            push(u,tl,tr);
            int tmid=tl+tr; tmid>>=1;
            query(lef(u),tl,tmid,l,min(tmid,r)),query(rig(u),tmid+1,tr,max(tmid+1,l),r);
        }
        node query(int l,int r){
            ret.val = -1;
            query(1,1,n,l,r);
            return ret;
        }
        void update(int u,int tl,int tr,int l,int r,sono& upd){
            if(l > r) return;
            if(tl == l && tr == r) return apply(u,upd);
            push(u,tl,tr);
            int tmid=tl+tr; tmid>>=1;
            update(lef(u),tl,tmid,l,min(tmid,r),upd),update(rig(u),tmid+1,tr,max(tmid+1,l),r,upd);
            merge(seg[lef(u)],seg[rig(u)],seg[u]);
        }
        void update(int l,int r, T x){
            sono upd = {x};
            update(1,1,n,l,r,upd);
        }
    };
    Seg seg; // segment tree

    RectangleUnion(vc<T> &coord) : seg(comp){
        assert(comp.empty());
        for(auto v : coord) comp.push_back(v-1),comp.push_back(v);
        sort(comp.begin(),comp.end());
        comp.erase(unique(comp.begin(),comp.end()),comp.end());
        N = comp.back()-comp[0]+1;
        seg.init(comp.size());
    }
    int get(T x){return lower_bound(comp.begin(),comp.end(),x) - comp.begin()+1;}
    // update em [l,r], as vezes dependendo do segmento o update eh ate r-1 na vdd
    // passar as coordenadas normais, eu comprimo
    void update(int l,int r,T v){seg.update(get(l),get(r-1),v);}  
    T cover_len(){
        auto ret = seg.query(1,comp.size());
        return (ret.val > 0 ? N : N - ret.qt);
    }
};
