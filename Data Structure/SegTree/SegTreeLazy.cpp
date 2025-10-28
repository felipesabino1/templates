// Indexado de 1
// Query com op associativa e update em range
// Init: 4*N
// Query: 4*log(N)
// Update: 4*log(N)
// Definir o node e sono
struct Seg{
    Seg(int n_, int t = 1) : n(n_), seg(n_<<2), lazy(n_<<2){
        if(t) build(1,1,n);
    }
    void init(int nn){
        n = nn;
        build(1,1,n);
    }
    // No da seg
    struct node{

        bool operator ==(const node &ot)const{
            return true;
        }
    };
    // Update e lazy
    struct sono{

        bool operator ==(const sono &ot)const{
            return true;
        }
    };

    int n;
    const node off = {};
    const sono off_lazy = {}; 
    vector<node> seg;
    vector<sono> lazy;
    node ret,aux;
    void merge(node &x, node &y, node & at){
        if(x == off) {
            at = y;
            return;
        }
        if(y == off) {
            at = x;
            return;
        }
        // o at eh o merge do x(esq) e y(dir)
        
    }
    // aplicar um update
    void apply(int u,int tl,int tr,sono& x){

    }
    
    void push(int u,int tl,int tr){
        if(tl == tr || lazy[u] == off_lazy) return;
        int tmid = tl + tr; tmid >>= 1;
        apply(lef(u),tl,tmid,lazy[u]), apply(rig(u),tmid+1,tr,lazy[u]);
        lazy[u] = off_lazy;
    }
    void build(int u,int tl,int tr){
        if(tl == tr){
            seg[u] = {}; lazy[u] = off_lazy;
            return;
        }
        int tmid = tl + tr; tmid >>= 1;
        build(lef(u), tl, tmid), build(rig(u), tmid+1, tr);
        merge(seg[lef(u)], seg[rig(u)], seg[u]);
        lazy[u] = off_lazy;
    }
    
    void query(int u,int tl,int tr,int l, int r){
        if(l > r) return;
        if(tl == l && tr == r) {
            merge(aux = ret,seg[u],ret);
            return;
        }
        push(u, tl, tr);
        int tmid= tl + tr; tmid >>= 1;
        query(lef(u),tl,tmid,l,min(tmid,r)), query(rig(u),tmid+1,tr,max(tmid+1,l),r);   
    }
    node query(int l, int r){
        ret = off;
        query(1,1,n,l,r);
        return ret;
    }
    
    void update(int u, int tl, int tr, int l, int r, sono& x){
        if(l > r) return;
        if(tl == l && tr == r){
            apply(u,tl,tr,x);
            return;
        }
        push(u, tl, tr);
        int tmid = tl + tr; tmid >>= 1;
        update(lef(u), tl, tmid, l, min(tmid,r), x), update(rig(u), tmid+1, tr, max(tmid+1,l), r, x);
        merge(seg[lef(u)], seg[rig(u)], seg[u]);
    }
    // passa os parametros que dai vai converter pra sono
    void update(int l, int r, ll x){
        sono vals = {};
        update(1, 1, n, l, r, vals);
    }
};
