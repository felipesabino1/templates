// Indexado de 0
// Query com operacao associativa e update em range
// Query(4*log(N)*O(merge)), Update(4*log(N)*O(merge))
// Cada update/query adiciona log(N) de memoria
// Inicializar o node com valor identidade
// Se precisar da range de cada node, lembra de passar true quando inicializar a Seg
struct node{

    // T tl,tr; // range do node
    node(){}
    void off(){} // transformar esse node na identidade
    friend void merge(node &x,node &y,node &at){
        // o at eh o merge do x(esq) e y(dir)

        // se for usar range do node
        // if(x.tl == -1) at.tl = y.tl, at.tr = y.tr;
        // else if(y.tl == -1) at.tl = x.tl, at.tr = x.tr;
        // else at.tl = x.tl, at.tr = y.tr;
    }
};
struct upd{

    bool off = true;
    upd(){}
    // aplica upd e upd lazy
    friend void apply(node &at,upd &lazy,upd &x){
        // upd node
        if(lazy.off) // limpa o que tem
        // upd lazy
        lazy.off = false;
    }
};
template <class node, class upd, class T>
struct Seg{
    #define lef(x) prox[x][0]
    #define rig(x) prox[x][1]
    #define msb(x) ((x) == 0 ? -1 : __builtin_clzll(1ll) - __builtin_clzll(x))
    T n; vc<node> seg; vc<upd> lazy; vc<array<int,2>> prox;
    node ret,aux; bool flag;
    Seg(T nn = 1,bool range=false,int q = 0) : n(nn), flag(range){ // passar qtd de Queries em q
        if(q > 0) seg.reserve(2*q*(msb(n)+1));
        add(); if(flag) seg[0].tl = 0, seg[0].tr = n-1;
    }
    int add(){
        int x = seg.size();
        seg.emplace_back(),lazy.emplace_back(),prox.emplace_back();
        return x;
    }
    void add(int u){
        if(lef(u)) return;
        lef(u) = add(), rig(u) = add();
        if(flag){
            T tl = seg[u].tl, tr = seg[u].tr;
            T tmid = tl+tr; tmid >>= 1;
            seg[lef(u)].tl = tl, seg[lef(u)].tr = tmid;
            seg[rig(u)].tl = tmid+1, seg[rig(u)].tr = tr;
        }
    }
    void push(int u,T tl,T tr){
        if(tl == tr || lazy[u].off) return;
        apply(seg[lef(u)],lazy[lef(u)],lazy[u]),apply(seg[rig(u)],lazy[rig(u)],lazy[u]);
        lazy[u].off = true;
    }
    void query(int u,T tl,T tr,T l, T r){
        if(l > r) return;
        if(l == tl && tr == r) return merge(aux = ret,seg[u],ret);
        T tmid = tl+tr; tmid >>= 1;
        add(u); push(u,tl,tr);
        query(lef(u),tl,tmid,l,min(r,tmid)),query(rig(u),tmid+1,tr,max(l,tmid+1),r);
    }
    node query(T l, T r){
        ret.off(); query(0,0,n-1,l,r);
        return ret;
    }
    void update(int u,T tl,T tr,T l, T r, upd& x){
        if(l > r) return;
        if(l == tl && tr == r) return apply(seg[u],lazy[u],x);
        T tmid = tl+tr; tmid >>= 1;
        add(u); push(u,tl,tr);
        update(lef(u),tl,tmid,l,min(r,tmid),x),update(rig(u),tmid+1,tr,max(l,tmid+1),r,x);
        merge(seg[lef(u)],seg[rig(u)],seg[u]);
    }
    void update(T l, T r, upd x){update(0,0,n-1,l,r,x);} // [l,r]
    #undef lef
    #undef rig
    #undef msb
};
