// Indexado de 1
// Query com op associativa e update em ponto
// Init: 2*N
// Query: 2*log(N)*O(merge)
// Update: log(N)*O(merge)
// Definir: node,upd,merge,build,apply,update
struct Seg{
    Seg(int nn = 0, int t = 1) : n(nn), seg(nn<<1){
        if(t) build();
    }
    void init(int nn){
        n = nn; if(seg.size() < 2*n) seg.resize(n<<1);
        build();
    }
    // No da seg
    struct node{

        bool off = false;
    };
    // Update
    struct upd{

    };

    int n; vector<node> seg;
    void merge(node &x, node &y, node & at){
        if(x.off) return void(at = y);
        if(y.off) return void(at = x);
        // o at eh o merge do x(esq) e y(dir)

    }
    void build(){
        for(int u=1; u<=n; u++) seg[u-1+n] = {a[u],false};
        for(int u=n-1; u; u--) merge(seg[lef(u)],seg[rig(u)],seg[u]);
    }
    // aplicar um update
    void apply(int u,upd x){
        
    }
    // query inclusiva [l,r]
    node query(int l,int r){
        node vl,vr,aux;
        vl.off = vr.off = true;
        for(l+=n-1,r+=n;l<r;l>>=1,r>>=1){
            if (l&1) merge(aux=vl,seg[l++],vl);
            if (r&1) merge(seg[--r],aux=vr,vr);
        } merge(vl,vr,aux); return aux;
    }
    // passa os parametros que dai vai converter pra upd
    void update(int id, ll x){
        id += n-1;
        apply(id,{}); 
        for(id>>=1; id; id>>=1) merge(seg[lef(id)],seg[rig(id)],seg[id]);
    }
};
