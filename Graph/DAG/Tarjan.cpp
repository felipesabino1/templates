// Indexado de 0
// Constroi a DAG de um grafo direcionado
// O(N+M)
struct Tarjan{
    vvc<int> &graph;
    vc<int> tin,low,root,st; int timer = 0, comp = 0;
    vvc<int> ng;
    Tarjan(vvc<int>& g) : graph(g), tin(g.size(),0), low(g.size(),0), root(g.size(),-1){
        int n = graph.size();
        for(int i=0; i<n; i++) if(!tin[i]) dfs(i,-1);
        for(int i=0; i<n; i++){
            int u = root[i];
            for(auto v : graph[i]) if(u != root[v]) ng[u].push_back(root[v]);
        }
        tin.clear(), low.clear(), root.clear(), st.clear();
    } 
    void dfs(int u,int ant){
        tin[u] = low[u] = ++timer;
        st.push_back(u);
        for(auto v : graph[u]){
            if(!tin[v]) dfs(v,u),low[u] = min(low[u],low[v]);
            else if(root[v] == -1) low[u] = min(low[u],tin[v]);
        }
        if(tin[u] == low[u]){
            ng.push_back({});
            while(true){
                int v = st.back(); st.pop_back();
                root[v] = comp; if(u == v) break;
            }
            comp++;
        }
    }
};
