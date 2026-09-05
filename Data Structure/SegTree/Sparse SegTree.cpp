// Indexado de 0
// Query com operacao associativa e update em ponto
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

    upd(){}
    // aplica upd e upd lazy
    friend void apply(node &at,upd &x){
        // upd node
    }
};
template <class node, class upd, class T>
struct Seg{
    #define lef(x) prox[x][0]
    #define rig(x) prox[x][1]
    #define msb(x) ((x) == 0 ? -1 : __builtin_clzll(1ll) - __builtin_clzll(x))
    T n; vc<node> seg; vc<array<int,2>> prox;
    node ret,aux;
    Seg(T nn = 1,int q = 0) : n(nn){ // passar qtd de Queries em q
        if(q > 0){
            int tam = 2*q*(msb(n)+1);
            seg.reserve(tam),prox.reserve(tam);
        }
        add(); 
    }
    int add(){
        int x = seg.size();
        seg.emplace_back(),prox.emplace_back();
        return x;
    }
    void add(int u){
        if(lef(u)) return;
        lef(u) = add(), rig(u) = add();
    }
    void query(int u,T tl,T tr,T l, T r){
        if(l > r) return;
        if(l == tl && tr == r) return merge(aux = ret,seg[u],ret);
        T tmid = tl+tr; tmid >>= 1; add(u);
        query(lef(u),tl,tmid,l,min(r,tmid)),query(rig(u),tmid+1,tr,max(l,tmid+1),r);
    }
    node query(T l, T r){
        assert(0 <= l && l <= r && r < n);
        ret.off(); query(0,0,n-1,l,r);
        return ret;
    }
    void update(int u,T tl,T tr,T id, upd& x){
        if(tl == tr) return apply(seg[u],x);
        T tmid = tl+tr; tmid >>= 1; add(u);
        if(tmid >= id) update(lef(u),tl,tmid,id,x);
        else update(rig(u),tmid+1,tr,id,x);
        merge(seg[lef(u)],seg[rig(u)],seg[u]);
    }
    void update(T id, upd x){assert(0 <= id && id < n); update(0,0,n-1,id,x);} // [l,r]
    #undef lef
    #undef rig
    #undef msb
};
