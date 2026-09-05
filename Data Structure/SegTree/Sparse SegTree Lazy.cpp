// Indexado de 0
// Query com operacao associativa e update em range
// Query(4*log(N)*O(merge)), Update(4*log(N)*O(merge))
// Cada update/query adiciona log(N) de memoria
// Inicializar o node com valor identidade
// Se precisar usar a range, eh melhor passar no apply ao inves de colocar no node
struct node{

    node(){}
    void off(){} // transformar esse node na identidade
    friend void merge(node &x,node &y,node &at){
        // o at eh o merge do x(esq) e y(dir)
        
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
};template <class node, class upd, class T>
struct Seg{
    #define lef(x) prox[x][0]
    #define rig(x) prox[x][1]
    #define check(x) x = x == -1 ? add() : x    
    T n; vc<node> seg; vc<upd> lazy; vc<array<int,2>> prox;
    node ret,aux;
    Seg(T nn = 1,int q = 0) : n(nn){ // passar qtd de Queries em q
        if(q > 0){
            int tam = 2*q*(64-__builtin_clzll(n));
            seg.reserve(tam),lazy.reserve(tam),prox.reserve(tam);
        }
        add(); 
    }
    int add(){
        int x = seg.size();
        seg.emplace_back(),lazy.emplace_back(),prox.push_back({-1,-1});
        return x;
    }
    void push(int u,T tl,T tr){
        if(tl == tr || lazy[u].off) return;
        check(lef(u)), check(rig(u));
        apply(seg[lef(u)],lazy[lef(u)],lazy[u]),apply(seg[rig(u)],lazy[rig(u)],lazy[u]);
        lazy[u].off = true;
    }
    void query(int u,T tl,T tr,T l, T r){
        if(l > r) return;
        if(l == tl && tr == r) return merge(aux = ret,seg[u],ret);
        T tmid = tl+tr; tmid >>= 1; push(u,tl,tr);
        check(lef(u)), check(rig(u));
        query(lef(u),tl,tmid,l,min(r,tmid)), query(rig(u),tmid+1,tr,max(l,tmid+1),r);
    }
    node query(T l, T r){
        assert(0 <= l && l <= r && r < n);
        ret.off(); query(0,0,n-1,l,r);
        return ret;
    }
    void update(int u,T tl,T tr,T l, T r, upd& x){
        if(l > r) return;
        if(l == tl && tr == r) return apply(seg[u],lazy[u],x);
        T tmid = tl+tr; tmid >>= 1; push(u,tl,tr);
        check(lef(u)), check(rig(u));
        update(lef(u),tl,tmid,l,min(r,tmid),x), update(rig(u),tmid+1,tr,max(l,tmid+1),r,x);
        merge(seg[lef(u)],seg[rig(u)],seg[u]);
    }
    void update(T l, T r, upd x){assert(0 <= l && l <= r && r < n); update(0,0,n-1,l,r,x);} // [l,r]
    #undef lef
    #undef rig
    #undef check
};
