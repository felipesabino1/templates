// Indexado de 1
// Query com op associativa e update em ponto
// Init: 2*N
// Query: 2*log(N)*O(merge)
// Update: log(N)*O(merge)
// Definir: node,upd,merge,build,apply,update
struct Seg{
    Seg(int nn = 0, int t = 1) : n(nn), seg(nn<<2){
        if(t) build(1,1,n);
    }
    // No da seg
    struct node{

        bool off = false;
    };
    // Update
    struct sono{

    };

    int n;
    vector<node> seg;
    node ret,aux;
    void merge(node &x, node &y, node & at){
        if(x.off) return void(at = y);
        if(y.off) return void(at = x);
        // o at eh o merge do x(esq) e y(dir)
      
    }
    // aplicar um update
    void apply(int u,sono& x){
      
    }
    
    void build(int u,int tl,int tr){
        if(tl == tr) return void(seg[u] = {,false});
        int tmid = tl + tr; tmid >>= 1;
        build(lef(u), tl, tmid), build(rig(u), tmid+1, tr);
        merge(seg[lef(u)], seg[rig(u)], seg[u]);
    }
    
    void query(int u,int tl,int tr,int l, int r){
        if(l > r) return;
        if(tl == l && tr == r) return merge(aux = ret,seg[u],ret);
        int tmid= tl + tr; tmid >>= 1;
        query(lef(u),tl,tmid,l,min(tmid,r)), query(rig(u),tmid+1,tr,max(tmid+1,l),r);   
    }
    node query(int l, int r){
        ret.off = true;
        query(1,1,n,l,r);
        return ret;
    }
    
    void update(int u, int tl, int tr, int id, sono& x){
        if(tl == tr) return apply(u,x);
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
