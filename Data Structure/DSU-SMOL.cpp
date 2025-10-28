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
    vector<int> repre;
    vector<gp> smol;

    // se t = 0, aloca sem init
    DSU (int nn,int t = 1) : n(nn), repre(nn+1), smol(nn+1){
        if(t){
            for(int i=1; i<=n; i++){
                repre[i]=i;
                smol[i].init(i);
            }
        }
    }
    void init(int nn){
        n = nn;
        for(int i=1; i<=n; i++){
            repre[i] = i;
            smol[i].init(i);
        }
    }


    int rep(int u){
        return repre[u] = (repre[u] == u ? u : rep(repre[u]));
    }
    gp & smoll(int u){
        return smol[rep(u)];
    }

    // unir u e v
    void unite(int u,int v,int t = 0){
        u = rep(u), v = rep(v);
        if(u == v) return;
        auto &x=smol[u];
        auto &y=smol[v];
        if(y.tam > x.tam){
            unite(v,u,t);
            return;
        }
        // da merge nos smols
        merge(x,y,t);
        repre[v]=u;
    }

    // fazer o merge de 2 grupos
    void merge(gp &x, gp &y,int t){
        // faz o merge se precisar
        x.tam += y.tam;
        y.clear();
    }
};
