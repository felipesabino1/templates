/*
    Indexado em 0

    Alteracoes:

    Ver se precisa adicionar coisa no gp do smol
*/
struct DSU{
    struct gp{
        // se precisa adicionar coisa a mais
        int tam;

        // inicializar o smol
        void init(int x){
            // se precisa inicializar coisa a mais, passa por parametro
            tam=1;
        }
    };
    
    vector<int> repre;
    vector<gp> smol;


    DSU (int n){
        repre.resize(n);
        smol.resize(n);
        for(int i=0; i<n; i++){
            repre[i]=i;
            smol[i].init(i);
        }
    }

    int rep(int u){
        if(u == repre[u]) return u;
        return repre[u]=rep(repre[u]);
    }

    void unite(int u,int v){
        u=rep(u);
        v=rep(v);
        if(u == v) return;

        auto &x=smol[u];
        auto &y=smol[v];
        if(y.tam > x.tam){
            unite(v,u);
            return;
        }
        
        // da merge nos smols
        merge(x,y);
        repre[v]=u;
    }

    void merge(gp &x, gp &y){
        // faz o merge se precisar

        x.tam+=y.tam;
    }
};
