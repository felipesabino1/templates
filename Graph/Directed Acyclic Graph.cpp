/*
    Indexado de 1. O grafo condensado ta em ngraph, tem que ter um graph e inv globais
*/
namespace DAG{
    int timer;
    vector<int> vis,ord,ngraph;
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
    void solve(int n){
        vis.resize(n); ord.clear();
        // ordem de saida dos caras
        for(int i=1; i<=n; i++) vis[i] = 0;
        for(int i=0; i<=n; i++) if(!vis[i]) set_ord(i);
        reverse(ord.begin(),ord.end());
        for(int i=1; i<=n; i++) vis[i] = 0;
        // andar no grafo inverso pra arrumar as componentes
        timer = 1;
        for(auto u : ord) if(!vis[u]) set_comp(u),timer++;
        timer--;
        ngraph.resize(timer+1);
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
}
using namespace DAG;
