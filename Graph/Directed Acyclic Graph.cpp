/*
    Indexado de 1
*/
struct DAG{
    int n,timer=1;
    vector<int> vis,ord; // no visitado vai ser qual a componente de cada vertice, o timer tem a qtd de componentes total
    vector<vector<int>> graph,inv; // grafo original
    vector<vector<int>> ngraph; // novo grafo

    DAG(int n) : n(n){
        vis.resize(n+10,0);
        graph.resize(n+10);
        inv.resize(n+10);
    }
    ~DAG(){
        vis.clear();
        ord.clear();
        graph.clear();
        inv.clear();
        ngraph.clear();
    }

    void read_edge(int m){
        int x,y;
        for(int i=0; i<m; i++){
            cin >> x >> y;
            graph[x].push_back(y);
            inv[y].push_back(x);
        }
    }

    void set_ord(int u){
        vis[u] = 1;
        for(auto v: graph[u]){
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
        // ordem de saida dos caras
        for(int i=1; i<=n; i++) vis[i] = 0;
        for(int i=0; i<=n; i++) if(!vis[i]) set_ord(i);
        reverse(ord.begin(),ord.end());
        for(int i=1; i<=n; i++) vis[i] = 0;
        // andar no grafo inverso pra arrumar as componentes
        for(auto u : ord) if(!vis[u]) set_comp(u),timer++;
        timer--;
        ngraph.resize(timer+10);
        // criar o novo grafo
        for(int i=1; i<=n; i++){
            int u = vis[i];
            for(auto vv: graph[i]) {
                int v = vis[vv];
                if(u == v) continue;
                ngraph[u].push_back(v);
            }
        }
    }
};
