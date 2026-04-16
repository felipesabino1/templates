// Indexado de 0
// Query com op associativa e update em range
// Init(4*N), Query(4*log(N)), Update(4*log(N))
// Definir tudo que ta fora de Seg
struct node{

    bool off = false;
    node(){}
    friend void merge(node &x,node &y,node &at){
        if(x.off) return void(at = y);
        if(y.off) return void(at = x);
        // o at eh o merge do x(esq) e y(dir)

    }
};
struct upd{

    bool off = true;
    // aplica upd e upd lazy
    friend void apply(node &at, upd &atl, upd &x){
        // upd node
        if(atl.off) // limpa o que tem
        // upd update
        atl.off = false;
    }
};
template<class node,class upd>
struct Seg{
    #define lef(x) ((x)<<1)
    #define rig(x) (lef(x)|1)
    Seg(int nn = 0, vc<node> &v = {}) : n(nn), seg(n<<2), lazy(n<<2){
        if(!v.empty()) build(1,0,n-1,v);
    }
    void init(vc<node> &v){
        assert(v.size() == n);
        build(1,0,n-1,v);
    }
    int n; vc<node> seg; vc<upd> lazy;
    node ret,aux;
    void build(int u,int tl,int tr,vc<node> &v){
        if(tl == tr) return void(seg[u] = v[tl]);
        int tmid = tl + tr; tmid >>= 1;
        build(lef(u),tl,tmid,v), build(rig(u),tmid+1,tr,v);
        merge(seg[lef(u)], seg[rig(u)], seg[u]);
    }
    void push(int u,int tl,int tr){
        if(tl == tr || lazy[u].off) return;
        int tmid = tl + tr; tmid >>= 1;
        apply(seg[lef(u)],lazy[lef(u)],lazy[u]),apply(seg[rig(u)],lazy[rig(u)],lazy[u]);
        lazy[u].off = true;
    }
    void query(int u,int tl,int tr,int l, int r){
        if(l > r) return;
        if(tl == l && tr == r) return merge(aux = ret,seg[u],ret);
        push(u, tl, tr); int tmid= tl + tr; tmid >>= 1;
        query(lef(u),tl,tmid,l,min(tmid,r)), query(rig(u),tmid+1,tr,max(tmid+1,l),r);   
    }
    node query(int l, int r){
        ret.off = true; query(1,0,n-1,l,r);
        return ret;
    }
    void update(int u, int tl, int tr, int l, int r, upd& x){
        if(l > r) return;
        if(tl == l && tr == r) return apply(seg[u],lazy[u],x);
        push(u, tl, tr); int tmid = tl + tr; tmid >>= 1;
        update(lef(u), tl, tmid, l, min(tmid,r), x), update(rig(u), tmid+1, tr, max(tmid+1,l), r, x);
        merge(seg[lef(u)], seg[rig(u)], seg[u]);
    }
    void update(int l, int r, upd x){update(1,0,n-1,l,r,x);} // [l,r]
    #undef lef
    #undef rig
};
