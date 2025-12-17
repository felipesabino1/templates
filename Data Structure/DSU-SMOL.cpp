// Indexado em 1
// Alterar o que cada grupo tem
struct DSU{
    // o que cada grupo carrega de informacao
    struct gp{
        int tam = 0;
        void init(int x){
            tam=1;
        }
        void clear(){
            tam = 0;
        }
    };
    
    int n;
    vector<int> rep;
    vector<gp> smol;

    // se t = 0, aloca sem init
    DSU (int nn,int t = 1) : n(nn), rep(nn+1), smol(nn+1){
        if(t){
            for(int i=1; i<=n; i++){
                rep[i]=i;
                smol[i].init(i);
            }
        }
    }
    void init(int nn){
        n = nn;
        for(int i=1; i<=n; i++){
            rep[i] = i;
            smol[i].init(i);
        }
    }

    int get(int u){
        return rep[u] = (rep[u] == u ? u : get(rep[u]));
    }
    gp & smoll(int u){
        return smol[get(u)];
    }

    // unir u e v
    void unite(int u,int v,int t = 0){
        u = get(u), v = get(v);
        if(u == v) return;
        auto &x=smol[u];
        auto &y=smol[v];
        if(y.tam > x.tam) return void(unite(v,u,t));
        // da merge nos smols
        merge(x,y,t);
        rep[v]=u;
    }

    // fazer o merge de 2 grupos
    void merge(gp &x, gp &y,int t){
        // faz o merge se precisar
        x.tam += y.tam;
        y.clear();
    }
};
