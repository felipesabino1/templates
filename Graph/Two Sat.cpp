/*
    Indexado de 1

    Arrumar o jeito que faz a leitura do grafo, eh na leitura que constroi o grafo.
*/
struct TWOSAT{
    int n; // quantidade de proposicoes
    vector<vector<int>> graph,inv;
    vector<int> ord,vis;
    int timer=1;
    vector<int> val;

    TWOSAT(int n) : n(n){
        int n2 = (n+1)<<1;
        val.resize(n+10,0);
        graph.resize(n2+10);
        inv.resize(n2+10);
        vis.resize(n2+10,0);
    }
    ~TWOSAT(){
        graph.clear();
        inv.clear();
        ord.clear();
        vis.clear();
        val.clear();
    }

    inline int pos(int x){return (x<<1);}
    inline int neg(int x){return pos(x)|1;}

    // adicionar um OR
    // cada vertice eh uma proposicao, pra cada proposicao tem dois novos vertices (x<<1) e (x<<1)|1
    void add_edge(int a,int b,int na,int nb){
        int aa = a<<1;
        int bb = b<<1;
        aa^=na;
        bb^=nb;
        graph[aa^1].push_back(bb);
        graph[bb^1].push_back(aa);
        inv[bb].push_back(aa^1);
        inv[aa].push_back(bb^1);
    }

    void read_edge(int m){
        // ler as arestas, ai faz os esquemas pra transformar tudo em OR
        for(int i=0; i<m; i++){
          
        }
    }

    void set_ord(int u){
        vis[u] = 1;
        for(auto v : graph[u]){
            if(vis[v]) continue;
            set_ord(v);
        }
        ord.push_back(u);
    }

    void set_comp(int u){  
        vis[u] = timer;
        for(auto v: inv[u]){
            if(vis[v]) continue;
            set_comp(v);
        }
    }

    void solve(){
        // componentes conexas
        for(int i=1; i<=n; i++) {
            if(!vis[pos(i)]) set_ord(pos(i));
            if(!vis[neg(i)]) set_ord(neg(i));
        }
        reverse(ord.begin(),ord.end());
        for(int i=1; i<=n; i++) vis[pos(i)] = vis[neg(i)] = 0;
        for(auto u : ord) if(!vis[u]) set_comp(u),timer++;

        // ver se tem contradicao
        for(int i=1; i<=n; i++) if(vis[pos(i)] == vis[neg(i)]) val[0] = 1;
        
        // setar os valores de cada proposicao
        for(int i=1; i<=n; i++){
            if(vis[pos(i)] < vis[neg(i)]) val[i] = 0; // eh falso
            else val[i] = 1; // eh verdadeiro
        }
    }

    void show(){
        // se for val[0] == 1 eh pq nao dar
        if(val[0] == 1) cout << "IMPOSSIBLE\n";
        else{
            for(int i=1; i<=n; i++){
                if(i != 1) cout << ' ';
                cout << (val[i] ? '+' : '-');
            }
            cout << '\n';
        }
    }
};
