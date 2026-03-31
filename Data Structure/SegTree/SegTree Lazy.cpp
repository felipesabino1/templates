// Indexado de 0
// Query com op associativa e update em range
// Init: 4*N
// Query: 4*log(N)
// Update: 4*log(N)
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
struct sono{

    bool off = false;
    // aplica upd e upd lazy
    friend void apply(node &at, sono &x){
        // upd seg
        if(x.off) // limpa o que tem
        // upd lazy
        x.off = false;
    }
};
template<class node,class sono>
struct Seg{
    Seg(int nn = 0, vc<node> &v = {}) : n(nn), seg(n<<2), lazy(n<<2){
        if(!v.empty()) build(1,n-1,0,v);
    }
    int n; vc<node> seg; vc<sono> lazy;
    node ret,aux;
    void build(int u,int tl,int tr,vc<node> &v){
        if(tl == tr){
            seg[u] = v[tl],lazy[u].off = true;
            return;
        }
        int tmid = tl + tr; tmid >>= 1;
        build(lef(u),tl,tmid,v), build(rig(u),tmid+1,tr,v);
        merge(seg[lef(u)], seg[rig(u)], seg[u]);
        lazy[u].off = true;
    }
    void push(int u,int tl,int tr){
        if(tl == tr || lazy[u].off) return;
        int tmid = tl + tr; tmid >>= 1;
        apply(seg[lef(u)],lazy[u]),apply(seg[rig(u)],lazy[u]);
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
    void update(int u, int tl, int tr, int l, int r, sono& x){
        if(l > r) return;
        if(tl == l && tr == r) return apply(u,x);
        push(u, tl, tr); int tmid = tl + tr; tmid >>= 1;
        update(lef(u), tl, tmid, l, min(tmid,r), x), update(rig(u), tmid+1, tr, max(tmid+1,l), r, x);
        merge(seg[lef(u)], seg[rig(u)], seg[u]);
    }
    void update(int l, int r, sono x){update(1,0,n-1,l,r,x);} // [l,r]
};
