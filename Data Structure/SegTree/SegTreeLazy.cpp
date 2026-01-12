// Indexado de 1
// Query com op associativa e update em range
// Init: 4*N
// Query: 4*log(N)
// Update: 4*log(N)
// Definir: node,sono,merge,apply,build,update
struct Seg{
    Seg(int nn = 0, int t = 0) : n(nn), seg(nn<<2), lazy(nn<<2){
        if(t) build(1,1,n);
    }
    void init(int nn){
        if(seg.size() < (nn<<2)) seg.resize(nn<<2),lazy.resize(nn<<2);
        n = nn;
        build(1,1,n);
    }
    // No da seg
    struct node{

        bool off = false;
    };
    // Update e lazy
    struct sono{

        bool off = false;
    };

    int n;
    vector<node> seg;
    vector<sono> lazy;
    node ret,aux;
    void merge(node &x, node &y, node & at){
        if(x.off) return void(at = y);
        if(y.off) return void(at = x);
        // o at eh o merge do x(esq) e y(dir)
        
    }
    // aplicar um update
    void apply(int u,int tl,int tr,sono& x){

    }
    
    void push(int u,int tl,int tr){
        if(tl == tr || lazy[u].off) return;
        int tmid = tl + tr; tmid >>= 1;
        apply(lef(u),tl,tmid,lazy[u]), apply(rig(u),tmid+1,tr,lazy[u]);
        lazy[u].off = true;
    }
    void build(int u,int tl,int tr){
        if(tl == tr){
            seg[u] = {}; lazy[u].off = true;
            return;
        }
        int tmid = tl + tr; tmid >>= 1;
        build(lef(u), tl, tmid), build(rig(u), tmid+1, tr);
        merge(seg[lef(u)], seg[rig(u)], seg[u]);
        lazy[u].off = true;
    }
    
    void query(int u,int tl,int tr,int l, int r){
        if(l > r) return;
        if(tl == l && tr == r) return merge(aux = ret,seg[u],ret);
        push(u, tl, tr);
        int tmid= tl + tr; tmid >>= 1;
        query(lef(u),tl,tmid,l,min(tmid,r)), query(rig(u),tmid+1,tr,max(tmid+1,l),r);   
    }
    node query(int l, int r){
        ret.off = true;
        query(1,1,n,l,r);
        return ret;
    }
    
    void update(int u, int tl, int tr, int l, int r, sono& x){
        if(l > r) return;
        if(tl == l && tr == r) return apply(u,tl,tr,x);
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
