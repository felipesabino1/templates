// Indexado de 0
// Query com op associativa e update em range
// Init(4*N*O(merge)), Query(4*log(N)*O(merge)), Update(4*log(N)*O(merge))
// Inicializar o node com valor off
struct upd{
    bool off = true;
    upd(){}
};
struct node{
    //int mx1, mx2
    node(){}
    void off(){} // transformar na identidade
    friend void merge(node &x,node &y,node &at){ // o at eh o merge do x(esq) e y(dir)
    }
    friend void apply(node& at,upd& lazy,upd& x){ // upd node, clear lazy, upd lazy
    }
    friend bool useless(node& at,upd& x){ // verifica se fazer update aqui faz diferenca
        // exemplo de aplicar minimo na regiao: return at.mx1 <= x.val
    }
    friend bool gud(node& at,upd& x){ // posso fazer update em range de boa?
        // exemplo de aplicar minimo na regiao: at.mx2 < x.val && x.val < at.mx1
    }
};
template<class node,class upd>
struct SegBeats{
    #define lef(x) ((x)<<1)
    #define rig(x) (lef(x)|1)
    int n; vc<node> seg; vc<upd> lazy;
    node ret,aux;
    SegBeats(int nn = 0, vc<node> v = {}) : n(nn), seg(n<<2), lazy(n<<2){
        if(!v.empty()) build(1,0,n-1,v);
    }
    void init(vc<node> &v){
        n = v.size();
        build(1,0,n-1,v);
    }
    void build(int u,int tl,int tr,vc<node> &v){
        if(tl == tr){
            seg[u] = v[tl], lazy[u].off = true;
            return;
        }
        int tmid = tl + tr; tmid >>= 1;
        build(lef(u),tl,tmid,v), build(rig(u),tmid+1,tr,v);
        merge(seg[lef(u)], seg[rig(u)], seg[u]);
        lazy[u].off = true;
    }
    void push(int u,int tl,int tr){
        if(tl == tr || lazy[u].off) return;
        apply(seg[lef(u)],lazy[lef(u)],lazy[u]),apply(seg[rig(u)],lazy[rig(u)],lazy[u]);
        lazy[u].off = true;
    }
    void query(int u,int tl,int tr,int l, int r){
        if(l > r) return;
        if(tl == l && tr == r) return merge(aux = ret,seg[u],ret);
        push(u, tl, tr); int tmid = tl + tr; tmid >>= 1;
        query(lef(u),tl,tmid,l,min(tmid,r)), query(rig(u),tmid+1,tr,max(tmid+1,l),r);   
    }
    node query(int l, int r){
        assert(0 <= l && l <= r && r < n);
        ret.off(); query(1,0,n-1,l,r);
        return ret;
    }
    void update(int u, int tl, int tr, int l, int r, upd& x){
        if(l > r || useless(seg[u],x)) return;
        if(tl == l && tr == r && gud(seg[u],x)) return apply(seg[u],lazy[u],x);
        push(u, tl, tr); int tmid = tl + tr; tmid >>= 1;
        update(lef(u),tl,tmid,l,min(tmid,r),x), update(rig(u),tmid+1,tr,max(tmid+1,l),r,x);
        merge(seg[lef(u)], seg[rig(u)], seg[u]);
    }
    void update(int l, int r, upd x){assert(0 <= l && l <= r && r < n); update(1,0,n-1,l,r,x);} // [l,r]
    #undef lef
    #undef rig
};
