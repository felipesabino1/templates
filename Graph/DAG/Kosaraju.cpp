// Indexado de 0
// Constroi a DAG de um grafo direcionado
// O(N+M), internamente cria a inversa do grafo original
struct Kosaraju{
    vvc<int> &graph; vvc<int>inv;
    vc<int> vis,ord; int timer;
    vvc<int> ng; // nova DAG
    Kosaraju(vvc<int>& g) : graph(g), inv(g.size()), vis(g.size(),0){
        int n = graph.size();
        for(int u=0; u<n; u++) for(auto v : graph[u]) inv[v].push_back(u);
        // ordem de saida dos caras
        for(int i=0; i<n; i++) vis[i] = 0;
        for(int i=0; i<n; i++) if(!vis[i]) set_ord(i);
        reverse(ord.begin(),ord.end());
        for(int i=0; i<n; i++) vis[i] = 0;
        // andar no grafo inverso pra arrumar as componentes
        timer = 0;
        for(auto u : ord) if(!vis[u]) timer++,set_comp(u);
        ng.resize(timer);
        for(int i=0; i<n; i++) vis[i]--;
        // criar o novo grafo
        for(int i=0; i<n; i++){
            int u = vis[i];
            for(auto vv: graph[i]) if(u != vis[vv]) ng[u].push_back(vis[vv]);
        }
        inv.clear(), vis.clear(), ord.clear();
    }
    void set_ord(int u){
        vis[u] = 1;
        for(auto v: graph[u]) if(!vis[v]) set_ord(v);
        ord.push_back(u);
    }
    void set_comp(int u){
        vis[u] = timer;
        for(auto v: inv[u]) if(!vis[v]) set_comp(v);
    }
};
