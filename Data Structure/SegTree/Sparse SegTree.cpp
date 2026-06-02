// Indexado de 0
// Query com op associativa e update em range
// Query: 4*log(N)
// Update: 4*log(N)
// Q*log(N) de memoria
// Definir tudo que ta fora de Seg, cuidado quando o retorno da query estiver off
// Nao precisa atualizar as ranges no merge, eu faco isso quando crio o node
template<class T>
struct node{

    bool off = true;
    int l = 0,r = 0; T tl,tr; // ponteiros, range do node
    node(){}
    friend void merge(node<T> &x,node<T> &y,node<T> &at){
        if(x.off) return void(at = y); // as vezes mudar o que o fazer com o off
        if(y.off) return void(at = x);
        // o at eh o merge do x(esq) e y(dir)

        at.off = false;
    }
};
template<class T>
struct upd{

    bool off = true;
    upd(){}
    // aplica upd e upd lazy
    friend void apply(node<T> &at,upd<T> &lazy,upd<T> &x){
        if(at.off) // init
        // updt seg
        at.off = false;
        if(lazy.off) // init
        // updt lazy
        lazy.off = false;
    }
};
template <class node, class upd, class T>
struct Seg{
    #define lef(x) seg[x].l
    #define rig(x) seg[x].r
    Seg(T nn = 0) : n(nn),seg(1),lazy(1){
        seg[0].tl = 0, seg[0].tr = n-1;
    }
    T n; vc<node> seg;  vc<upd> lazy;
    node ret,aux,offn;
    void push(int u,T tl,T tr){
        if(tl == tr || lazy[u].off) return;
        T tmid = tl + tr; tmid >>= 1;
        apply(seg[lef(u)],lazy[lef(u)],lazy[u]),apply(seg[rig(u)],lazy[rig(u)],lazy[u]);
        lazy[u].off = true;
    }
    int add(){
        int x = seg.size();
        seg.emplace_back(),lazy.emplace_back();
        return x;
    }
    void query(int u,T tl,T tr,T l, T r){
        if(l > r) return;
        if(l == tl && tr == r) return merge(aux = ret,seg[u],ret);
        T tmid = tl + tr; tmid >>= 1;
        if(!lef(u)) lef(u) = add(), seg[lef(u)].tl = tl, seg[lef(u)].tr = tmid;
        if(!rig(u)) rig(u) = add(), seg[rig(u)].tl = tmid+1, seg[rig(u)].tr = tr;
        push(u,tl,tr);
        query(lef(u),tl,tmid,l,min(r,tmid)),query(rig(u),tmid+1,tr,max(l,tmid+1),r);
    }
    node query(T l, T r){
        ret.off = true; query(0,0,n-1,l,r);
        return ret; // vc que trata quando o ret.off == true
    }
    void update(int u, T tl, T tr, T l, T r, upd& x){
        if(l > r) return;
        if(l == tl && tr == r) return apply(seg[u],lazy[u],x);
        T tmid = tl + tr; tmid >>= 1;
        if(!lef(u)) lef(u) = add(), seg[lef(u)].tl = tl, seg[lef(u)].tr = tmid;
        if(!rig(u)) rig(u) = add(), seg[rig(u)].tl = tmid+1, seg[rig(u)].tr = tr;
        push(u,tl,tr);
        update(lef(u),tl,tmid,l,min(r,tmid),x),update(rig(u),tmid+1,tr,max(l,tmid+1),r,x);
        merge(seg[lef(u)],seg[rig(u)],seg[u]);
    }
    void update(T l, T r, upd x){update(0,0,n-1,l,r,x);} // [l,r]
    #undef lef
    #undef rig
};
