// Indexado de 0
// Query com op associativa e update em ponto
// Init(N*(1 + O(merge))), Query(2*log(N)*O(merge)), Update(log(N)*O(merge))
// Inicializar o node com valor identidade
struct node{
    
    node(){}
    friend void merge(node &x, node &y, node &at){
        // o at eh o merge do x(esq) e y(dir)

    }
};
struct upd{

    upd(){}
    // aplicar um update em node
    friend void apply(node &at, upd& x){
        
    }
};
template<class node,class upd>
struct Seg{
    #define lef(x) ((x)<<1)
    #define rig(x) (lef(x)|1)
    int n; vector<node> seg;
    Seg(int nn = 0, vc<node> v = {}) : n(nn), seg(nn<<1){
        if(!v.empty()) build(v);
    }
    void build(vc<node>& v){
        for(int u=0; u<n; u++) seg[u+n] = v[u];
        for(int u=n-1; u; u--) merge(seg[lef(u)],seg[rig(u)],seg[u]);
    }
    // query inclusiva [l,r]
    node query(int l,int r){
        assert(0 <= l && l <= r && r < n);
        node vl,vr,aux;
        for(l+=n,r+=n+1;l<r;l>>=1,r>>=1){
            if(l&1) merge(aux=vl,seg[l++],vl);
            if(r&1) merge(seg[--r],aux=vr,vr);
        } 
        merge(vl,vr,aux); return aux;
    }
    void update(int id,upd x){
        assert(0 <= id && id < n);
        id += n; apply(seg[id],x); 
        for(id>>=1; id; id>>=1) merge(seg[lef(id)],seg[rig(id)],seg[id]);
    }
    #undef lef
    #undef rig
};
