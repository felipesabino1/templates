// Indexado de 0
// Query com op associativa e update em ponto
// Query e update: 4*log(N)
// N*log(N) de memoria (cada update adiciona log(N))
// Definir tudo que ta fora de Seg
struct node{
    
    bool off = false;int l = 0,r = 0;
    node(){}
    friend void merge(node &x,node &y,node &at){
        if(x.off) return void(at = y);
        if(y.off) return void(at = x);
        // o at eh o merge do x(esq) e y(dir)
        
    }
};
struct upd{

    // aplica upd
    friend void apply(node &at,upd &x){

    }
};
template <class node, class upd>
struct perSeg{
    #define lef(x) seg[x].l
    #define rig(x) seg[x].r
    perSeg(int nn = 0,vc<node> &v = {}) : n(nn),seg(1),rev(1,0){
        if(!v.empty()) build(1,0,n-1,v);
    }
    int n; vc<node> seg;
    vc<int> rev; // raiz da revisao
    node ret,aux;
    void build(int u,int tl,int tr,vc<node>& v){
        if(tl == tr) return void(seg[u] = v[tl]);
        int tmid = tl + tr; tmid >>= 1;
        lef(u) = seg.size(); seg.emplace_back();
        rig(u) = seg.size(); seg.emplace_back();
        build(lef(u),tl,tmid,v),build(rig(u),tmid+1,tr,v);
        merge(seg[lef(u)],seg[rig(u)],seg[u]);
    }
    void query(int u,int tl,int tr,int l,int r){
        if(l > r) return;
        if(l == tl && tr == r) return merge(aux = ret,seg[u],ret);
        int tmid = tl + tr; tmid >>= 1;
        query(lef(u),tl,tmid,l,min(r,tmid)),query(rig(u),tmid+1,tr,max(l,tmid+1),r);
    }
    node query(int l,int r,int R){
        ret.off = true; query(rev[R],0,n-1,l,r);
        return ret;
    }
    void update(int u,int nu,int tl,int tr,int id,upd &x){
        if(tl == tr){
            seg.push_back(seg[u]);
            apply(seg.back(),x);
            return;
        }
        int tmid = tl + tr; tmid >>= 1;
        lef(nu) = lef(u), rig(nu) = rig(u);
        if(id <= tmid){
            lef(nu) = seg.size();
            update(lef(u),lef(nu),tl,tmid,id,x);
        }else{
            rig(nu) = seg.size();
            update(rig(u),rig(nu),tmid+1,tr,id,x);
        }
        merge(seg[lef(u)],seg[rig(u)],seg[u]);
    }
    void update(int id,upd x,int r){
        rev.push_back(seg.size()); seg.emplace_back();
        update(rev[r],rev.back(),0,n-1,id,x);
    }
    #undef lef
    #undef rig
};
