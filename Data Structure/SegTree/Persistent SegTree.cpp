// Indexado de 0
// Query com operacao associativa e update em ponto
// Query(4*log(N)*O(merge)), Update(4*log(N)*O(merge))
// Cada update adiciona log(N) de memoria
// Inicializar o node com valor identidade
struct upd{

    upd(){}
};
struct node{
    
    node(){}
    void off(){} // transformar esse node na identidade
    friend void merge(node &x,node &y,node &at){
        // o at eh o merge do x(esq) e y(dir)
        
    }
    // aplica upd
    friend void apply(node &at,upd &x){
        // upd node
    }
};
template <class node, class upd>
struct perSeg{
    #define lef(x) prox[x][0]
    #define rig(x) prox[x][1]
    #define check(x) x = x == -1 ? add() : x
    int n; vc<node> seg; vc<array<int,2>> prox; vc<int> rev; // raiz da revisao    
    node ret,aux;
    perSeg(int nn = 0,vc<node> v = {},int q = 0) : n(nn),rev(1,0){
        if(n > 0 || q > 0){
            int tam = n<<2;
            tam += 2*q*(32-__builtin_clz(n));
            seg.reserve(tam),prox.reserve(tam);
        }
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
    void query(int u,int tl,int tr,int l,int r){
        if(l > r) return;
        if(l == tl && tr == r) return merge(aux = ret,seg[u],ret);
        int tmid = tl + tr; tmid >>= 1;
        query(lef(u),tl,tmid,l,min(r,tmid)),query(rig(u),tmid+1,tr,max(l,tmid+1),r);
    }
    node query(int l,int r,int R){
        assert(0 <= l && l <= r && r < n);
        ret.off(); query(rev[R],0,n-1,l,r);
        return ret;
    }
    void update(int u,int nu,int tl,int tr,int id,upd &x){
        if(tl == tr) return apply(seg[nu],x);
        int tmid = tl + tr; tmid >>= 1;
        if(id <= tmid) lef(nu) = clone(lef(u)), update(lef(u),lef(nu),tl,tmid,id,x);
        else rig(nu) = clone(rig(u)), update(rig(u),rig(nu),tmid+1,tr,id,x);
        merge(seg[lef(nu)],seg[rig(nu)],seg[nu]);
    }
    void update(int id,upd x,int r){
        assert(0 <= id && id < n);
        rev.push_back(seg.size());
        update(rev[r],clone(rev[r]),0,n-1,id,x);
    }
    #undef lef
    #undef rig
    #undef check
};
