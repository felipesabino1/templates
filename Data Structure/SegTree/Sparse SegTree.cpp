// Indexado de 0
// Query com op associativa e update em range
// Query: 4*log(N)
// Update: 4*log(N)
// Q*log(N) de memoria
// Definir tudo que ta fora de Seg
struct node{
    
    bool off = true; int l = 0,r = 0;
    void merge(node &x,node &y,node &at){
        if(x.off) return void(at = y); // as vezes mudar o que o fazer com o off
        if(y.off) return void(at = x);
        // o at eh o merge do x(esq) e y(dir)
    
        at.off = false;
    }
};
struct upd{

    bool off = true; 
    // aplica upd e upd lazy
    friend void apply(node &at,upd &x){
        if(at.off) // init
        // updt seg
        at.off = false;
        if(x.off) // init
        // updt lazy
        x.off = false;
    }
};
template <class node, class upd>
struct Seg{
    #define lef(x) seg[x].l
    #define rig(x) seg[x].r
    Seg(int nn = 0) : n(nn),seg(1),lazy(1){}
    int n; vc<node> seg;  vc<upd> lazy;
    node ret,aux,offn;
    void push(int u,int tl,int tr){
        if(tl == tr || lazy[u].off) return;
        int tmid = tl + tr; tmid >>= 1;
        apply(seg[lef(u)],lazy[u]),apply(seg[rig(u)],lazy[u]);
        lazy[u].off = true;
    }
    int add(){
        int x = seg.size();
        seg.emplace_back(),lazy.emplace_back();
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
        ret.off = true; query(0,0,n-1,l,r);
        if(ret.off) // off val
        return ret;
    }
    void update(int u, int tl, int tr, int l, int r, upd& x){
        if(l > r) return;
        if(l == tl && tr == r) return apply(u,x);
        if(!lef(u)) lef(u) = add(), rig(u) = add();
        push(u,tl,tr); int tmid = tl + tr; tmid >>= 1;
        update(lef(u),tl,tmid,l,min(r,tmid),x),update(rig(u),tmid+1,tr,max(l,tmid+1),r,x);
        merge(seg[lef(u)],seg[rig(u)],seg[u]);
    }
    void update(int l, int r, upd x){update(0,0,n-1,l,r,x);} // [l,r]
    #undef lef
    #undef rig
};
