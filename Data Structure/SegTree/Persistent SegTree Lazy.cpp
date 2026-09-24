// Indexado de 0
// Query com operacao associativa e update em ponto
// Query(4*log(N)*O(merge)), Update(4*log(N)*O(merge))
// Cada update adiciona log(N) de memoria
// Inicializar o node com valor identidade
struct upd{
    
    upd(){}
    void off(){} // transforma na identidade
    bool is_off(){}
};
struct node{
    
    upd lazy;
    node(){}
    void off(){} // transformar esse node na identidade
    friend void merge(node &x,node &y,node &at){
        // o at eh o merge do x(esq) e y(dir)
        
    }
    friend void apply(node &at,upd &x){ // aplica upd e upd lazy
        // upd node, clear lazy, upd lazy
    }
};
template <class node, class upd>
struct perSeg{
    #define lef(x) prox[x][0]
    #define rig(x) prox[x][1]
    #define check(x) x = x == -1 ? add() : x
    #define inter(a,b) (a <= r && b >= l)
    int n; vc<node> seg; vc<array<int,2>> prox; vc<int> rev; // raiz da revisao    
    node ret,aux;
    perSeg(int nn = 0,vc<node> v = {},int TAM = 0) : n(nn),rev(1,0){
        if(TAM) seg.reserve(TAM), prox.reserve(TAM);
        add(); if(!v.empty()) build(0,0,n-1,v);
    }
    void init(vc<node> &v){
        assert(v.size() == n);
        build(0,0,n-1,v);
    }
    int add(){
        int x = seg.size();
        seg.emplace_back(),prox.push_back({-1,-1});
        return x;
    }
    int clone(int u){
        int x = add();
        seg[x] = seg[u],prox[x] = prox[u];
        return x;
    }
    int get_rev(){return int(rev.size())-1;}
    void build(int u,int tl,int tr,vc<node>& v){
        if(tl == tr) return void(seg[u] = v[tl]);
        int tmid = tl + tr; tmid >>= 1;
        check(lef(u)), check(rig(u));
        build(lef(u),tl,tmid,v),build(rig(u),tmid+1,tr,v);
        merge(seg[lef(u)],seg[rig(u)],seg[u]);
    }
    void push(int u,int nu,int tl,int tr){
        if(tl == tr || seg[u].lazy.is_off()) return;
        lef(nu) = clone(lef(u)), rig(nu) = clone(rig(u));
        apply(seg[lef(nu)],seg[nu].lazy), apply(seg[rig(nu)],seg[nu].lazy);
        seg[nu].lazy.off();
    }
    void query(int u,int nu,int tl,int tr,int l,int r){
        if(l <= tl && tr <= r) return merge(aux = ret,seg[nu],ret);
        push(u,nu,tl,tr); int tmid = tl + tr; tmid >>= 1;
        if(inter(tl,tmid)) query(lef(u),lef(nu),tl,tmid,l,r);
        if(inter(tmid+1,tr)) query(rig(u),rig(nu),tmid+1,tr,l,r);
    }
    node query(int l,int r,int R){
        assert(0 <= l && l <= r && r < n);
        int t = seg.size();
        ret.off(); query(rev[R],clone(rev[R]),0,n-1,l,r);
        t = seg.size()-t;
        while(t--) seg.pop_back(), prox.pop_back();
        return ret;
    }
    void update(int u,int nu,int tl,int tr,int l,int r,upd &x){
        if(l <= tl && tr <= r) return apply(seg[nu],x);
        push(u,nu,tl,tr); int tmid = tl + tr; tmid >>= 1;
        if(inter(tl,tmid)) lef(nu) = (lef(u) == lef(nu) ? clone(lef(u)) : lef(nu)), update(lef(u),lef(nu),tl,tmid,l,r,x);
        if(inter(tmid+1,tr)) rig(nu) = (rig(u) == rig(nu) ? clone(rig(u)) : rig(nu)), update(rig(u),rig(nu),tmid+1,tr,l,r,x);
        merge(seg[lef(nu)],seg[rig(nu)],seg[nu]);
    }
    void update(int l,int r,upd x,int R){
        assert(0 <= l && l <= r && r < n);
        rev.push_back(seg.size());
        update(rev[R],clone(rev[R]),0,n-1,l,r,x);
    }
    #undef lef
    #undef rig
    #undef check
    #undef inter
};
