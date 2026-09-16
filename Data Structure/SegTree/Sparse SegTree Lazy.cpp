// Indexado de 0
// Query com operacao associativa e update em range
// Query(4*log(N)*O(merge)), Update(4*log(N)*O(merge))
// Cada update/query adiciona log(N) de memoria
// Inicializar o node com valor identidade e upd com valo off
// Se precisar usar a range, eh melhor passar no apply ao inves de colocar no node
struct upd{

    upd(){}
    void off(){} // transforma na identidade
    bool is_off(){} // esse cara eh identidade?
};
struct node{

    upd lazy;
    node(){}
    void off(){} // transformar na identidade
    friend void merge(node &x,node &y,node &at){
        // o at eh o merge do x(esq) e y(dir)
        
    }
    friend void apply(node& at, upd& x){ // aplica upd e upd lazu
        // upd node, clear lazy, upd lazy
    }
};
template <class node, class upd, class T>
struct Seg{
    #define lef(x) prox[x][0]
    #define rig(x) prox[x][1]
    #define check(x) x = x == -1 ? add() : x    
    T n; vc<node> seg; vc<array<int,2>> prox;
    node ret,aux;
    Seg(T nn = 1,int tam = 0) : n(nn){
        if(tam) seg.reserve(tam), prox.reserve(tam);
        add(); 
    }
    int add(){
        int x = seg.size();
        seg.emplace_back(),prox.push_back({-1,-1});
        return x;
    }
    void push(int u,T tl,T tr){
        if(tl == tr || seg[u].lazy.is_off()) return;
        check(lef(u)), check(rig(u));
        apply(seg[lef(u)],seg[u].lazy),apply(seg[rig(u)],seg[u].lazy);
        seg[u].lazy.off();
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
        if(l == tl && tr == r) return apply(seg[u],x);
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
