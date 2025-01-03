/*
    Indexado em 1

    Alteracoes:

    Ver se precisa adicionar coisa no gp do smol
*/
struct DSU{
    // o que cada grupo carrega de informacao
    struct gp{
        // se precisa adicionar coisa a mais
        int tam;

        // inicializar o smol
        void init(int x){
            // se precisa inicializar coisa a mais, passa por parametro
            tam=1;
        }
        void clear(){
            
        }
        ~gp(){}
    };
    
    vector<int> repre;
    vector<gp> smol;
    int n;

    // inicializar passando a qtd de vertices, grupos iniciais
    DSU (int n) : n(n){
        repre.resize(n+10);
        smol.resize(n+10);
        for(int i=1; i<=n; i++){
            repre[i]=i;
            smol[i].init(i);
        }
    }
    ~DSU(){
        repre.clear();
        smol.clear();
    }
    void init(int n){
        this->n = n;
        for(int i=1; i<=n; i++){
            repre[i] = i;
            smol[i].init(i);
        }
    }
    void clear(){
        for(int i=1; i<=n; i++){
            smol[i].clear();
        }
    }

    // achar o representante do u
    int rep(int u){
        if(u == repre[u]) return u;
        return repre[u]=rep(repre[u]);
    }

    // unir u e v
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

    // fazer o merge de 2 grupos
    void merge(gp &x, gp &y){
        // faz o merge se precisar

        x.tam+=y.tam;
    }
};
