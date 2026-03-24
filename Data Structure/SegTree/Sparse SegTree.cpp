// Indexado de 1
// Query com op associativa e update em range
// Query: 4*log(N)
// Update: 4*log(N)
// Q*log(N) de memoria
// Definir: node,sono,merge,apply,build,update
#warning verificar se tem conflito com os defines
#define lef(x) prox[x].first
#define rig(x) prox[x].second
struct Seg{
    Seg(int nn = 0) : n(nn),seg(1),lazy(1),prox(1,{0,0}){}
    // No da seg
    struct node{

        bool off = true;
    };
    // Update e lazy
    struct sono{
        
        bool off = true;
    };
    
    int n; vc<node> seg;  vc<sono> lazy;
    vc<pair<int,int>> prox;
    node ret,aux,offn;
    void merge(node &x, node &y, node &at){
        if(x.off) return void(at = y); // as vezes mudar o que o fazer com o off
        if(y.off) return void(at = x);
        // o at eh o merge do x(esq) e y(dir)

        at.off = false;
    }
    // aplica o updt e updt lazy
    void apply(int u,int tl,int tr,sono& x){
        if(seg[u].off) // init
        // updt seg
        seg[u].off = false;
        if(lazy[u].off) // init
        // updt lazy
        lazy[u].off = false;
    }
    void push(int u,int tl,int tr){
        if(tl == tr || lazy[u].off) return;
        int tmid = tl + tr; tmid >>= 1;
        apply(lef(u),tl,tmid,lazy[u]),apply(rig(u),tmid+1,tr,lazy[u]);
        lazy[u].off = true;
    }
    int add(){
        int x = seg.size();
        seg.emplace_back(),lazy.emplace_back(),prox.emplace_back(0,0);
        return x;
    }
    void query(int u,int tl,int tr,int l, int r){
        if(l > r) return;
        if(l == tl && tr == r) return merge(aux = ret,seg[u],ret);
        if(!lef(u)) lef(u) = add(), rig(u) = add();
        push(u,tl,tr); int tmid = tl + tr; tmid >>= 1;
        query(lef(u),tl,tmid,l,min(r,tmid)),query(rig(u),tmid+1,tr,max(l,tmid+1),r);
    }
    node query(int l, int r){
        ret.off = true; query(0,1,n,l,r);
        if(ret.off) // off val
        return ret;
    }
    
    void update(int u, int tl, int tr, int l, int r, sono& x){
        if(l > r) return;
        if(l == tl && tr == r) return apply(u,tl,tr,x);
        if(!lef(u)) lef(u) = add(), rig(u) = add();
        push(u,tl,tr); int tmid = tl + tr; tmid >>= 1;
        update(lef(u),tl,tmid,l,min(r,tmid),x),update(rig(u),tmid+1,tr,max(l,tmid+1),r,x);
        merge(seg[lef(u)],seg[rig(u)],seg[u]);
    }
    // passa os parametros que dai vai converter pra sono
    void update(int l, int r){
        sono vals = {}; update(0,1,n,l,r,vals);
    }
};
