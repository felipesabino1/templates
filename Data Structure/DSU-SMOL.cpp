// Indexado de 0
// Definir o que gp carrega de informacao
// Definir o merge dos grupos
// O(N * log(N) * T) com T a complexidade do merge
struct gp{
    void inite(int x){
                
    }
    void clear(){
        
    }
    // fazer o merge de 2 grupos
    friend void merge(gp &x, gp &y,int t){
        
        y.clear();
    }
};
template<class gp>
struct DSU{
    int n;
    vector<int> rep,tam;
    vector<gp> smol;
    // se t = false, aloca sem init
    DSU (int nn,bool t = true) : n(nn),rep(nn+1),tam(nn+1),smol(nn+1){
        if(t) init(nn);
    }
    void init(int nn){
        n = nn;
        for(int i=0; i<n; i++) 
            rep[i]=i,tam[i]=1,smol[i].init(i);
    }
    int get(int u){return rep[u] = (rep[u] == u ? u : get(rep[u]));}
    gp& smoll(int u){return smol[get(u)];}
    // unir u e v
    void unite(int u,int v,int t = 0){
        u = get(u), v = get(v);
        if(u == v) return;
        if(tam[u] < tam[v]) swap(u,v);
        merge(smoll(u),smoll(v),t);
        rep[v]=u,tam[u]+=tam[v];
    }
};
