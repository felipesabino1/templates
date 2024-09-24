/*
    Indexado de 1
*/
struct Centroid{
    // o pai de cada cara no centroide
    vector<int> p;
    // visitado para construir o centroide
    vector<bool> vis;
    // tam da subarvore
    vector<int> tam;
    // grafo original
    vector<vector<int>> graph;
    int n;
    // raiz do centroide
    int r;

    // passa com o grafo ja lido
    Centroid(vector<vector<int>> &graph,int n){
        this->graph = graph;
        tam.resize(n+10);
        vis.resize(n+10);
        p.resize(n+10);
        this->n = n;
        r=build(1);
    }

    // constroi o centroide
    int build(int u){
        set_tam(u,u);
        while(1){
            int flag=1;
            for(auto v: graph[u]){
                if(vis[v]) continue;
                if(tam[v]*2 > tam[u]){
                    tam[u]-=tam[v];
                    tam[v]+=tam[u];
                    u=v;
                    flag=0;
                    break;
                }
            }
            if(flag) break;
        }
        vis[u]=1;
        p[u]=u;
        for(auto v: graph[u]){
            if(vis[v]) continue;
            int x=build(v);
            p[x]=u;
        }    
        return u;
    }

    void set_tam(int u,int ant){
        tam[u]=1;
        for(auto v: graph[u]){
            if(v == ant || vis[v]) continue;
            set_tam(v,u);
            tam[u]+=tam[v];
        }
    }
};
