// Indexado de 0
// Array persistente
// Query e update: log(N)
// N * log(N) de memoria (cada update adiciona log(N))
struct info{
    info(){} // init NULL
};
template<class T>
struct perarray{
    #warning ver se nao conflita com outros define's
    #define lef(x) (prox[x].first)
    #define rig(x) (prox[x].second)
    vc<T> vals; // so guardo as folhas da arvore
    vc<int> rev; // a raiz da revisao
    vc<pair<int,int>> prox; // dado esse no, quais os proximos
    perarray(int n) : rev(1,0),prox(1,{0,0}){
        build(0,0,n-1);
    }
    void build(int u,int tl,int tr){
        if(tl == tr) return void(vals.push_back(off));
        int tmid = tl + tr; tmid >>= 1;
        lef(r) = (tl == tmid ? vals.size() : prox.size());
        prox.emplace_back(0,0);
        rig(r) = (tmid+1 == tr ? vals.size() : prox.size());
        prox.emplace_back(0,0);
        build(lef(u),tl,tmid), build(rig(u),tmid+1,tr);
    }
    T ret;
    void query(int u,int tl,int tr,int id){
        if(tl == tr) return void(ret = vals[id]);
        int tmid = tl + tr; tmid >>= 1;
        if(id <= tmid) query(lef(u),tl,tmid,id);
        else query(rig(u),tmid+1,tr,id);
    }
    T query(int id,int r){query(rev[r],0,n-1,id); return ret;}
    void update(int u,int nu,int tl,int tr,int id,T& x){
        if(tl == tr) return void(vals.push_back(x));
        int tmid = tl + tr; tmid >>= 1;
        lef(nu) = lef(u), rig(nu) = rig(u);
        if(id <= tmid){
            lef(nu) = (tl == tmid ? vals.size() : prox.size());
            prox.emplace_back(0,0);
            update(lef(u),lef(nu),tl,tmid,id,x);
        }else{
            rig(nu) = (tmid+1 == tr ? vals.size() : prox.size());
            prox.emplace_back(0,0);
            update(rig(u),rig(nu),tmid+1,tr,id,x);
        }
    }
    void update(int id,T x,int r){
        rev.push_back(prox.size()), prox.emplace_back(0,0);
        update(rev[r],rev.back(),0,n-1,id,x);
    }
    #undef lef
    #undef rig
};
