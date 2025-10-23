// Indexado de 1
// Query com op associativa e update em ponto
// Init: 4*N
// Query: 4*log(N)
// Update: 4*log(N)
// Definir o node
struct Seg{
    Seg(int n_) : n(n_), seg(n_<<2){
        build(1,1,n);
    }
    // No da seg
    struct node{

        bool operator ==(const node &ot)const{
            return true;
        }
    };
    // Update
    struct sono{

    };

    int n;
    const node off = {};
    vector<node> seg;
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
    
    void build(int u,int tl,int tr){
        if(tl == tr){
            seg[u] = {};
            return;
        }
        int tmid = tl + tr; tmid >>= 1;
        build(lef(u), tl, tmid), build(rig(u), tmid+1, tr);
        merge(seg[lef(u)], seg[rig(u)], seg[u]);
    }
    
    void query(int u,int tl,int tr,int l, int r){
        if(l > r) return;
        if(tl == l && tr == r) {
            merge(aux = ret,seg[u],ret);
            return;
        }
        int tmid= tl + tr; tmid >>= 1;
        query(lef(u),tl,tmid,l,min(tmid,r)), query(rig(u),tmid+1,tr,max(tmid+1,l),r);   
    }
    node query(int l, int r){
        ret = off;
        query(1,1,n,l,r);
        return ret;
    }
    
    void update(int u, int tl, int tr, int id, sono& x){
        if(tl == tr){
            apply(u,tl,tr,x);
            return;
        }
        int tmid = tl + tr; tmid >>= 1;
        if(tmid >= id) update(lef(u),tl,tmid,id,x);
        else update(rig(u),tmid+1,tr,id,x);
        merge(seg[lef(u)], seg[rig(u)], seg[u]);
    }
    // passa os parametros que dai vai converter pra sono
    void update(int id, ll x){
        sono vals = {};
        update(1, 1, n, id, vals);
    }
};
