/*
    Indexado de 1
*/
struct Centroid{
    vector<int> p; // o pai de cada cara no centroide
    vector<bool> vis; // visitado para construir o centroide
    vector<int> tam; // tam da subarvore
    vector<vector<int>> & graph; // referencia da arvore original
    int n; // qtd de vertices 
    int r; // raiz do centroide
    // vector<ll> cnt;
    // ll qt = 0;

    Centroid(int n, vector<vector<int>> & graph) : graph(graph), n(n){
        tam.resize(n+10);
        vis.resize(n+10);
        qtd.resize(n+10);
        // p.resize(n+10);
        r=build(1);
    }

    // constroi o centroid decomposition
    int build(int u){
        set_tam(u,u);
        u = find_centroid(u);
        vis[u]=1;

        // se tiver que fazer algum calculo durante o centroid decomposition
        // calc(u);

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
    int find_centroid(int u){
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
        return u;
    }

    void calc(int u,int ant, int sz){
        // faz algum tipo de calculo
        for(auto v: graph[u]){
            if(v == ant || vis[v]) continue;
            calc(v,u,d+1,sz);
        }
    }
    void update(int u,int ant){
        // faz algum tipo de update
        for(auto v: graph[u]){
            if(v == ant || vis[v]) continue;
            update(v,u,d+1);
        }
    }
    void reset(int u,int ant,int d = 0){
        // reseta as coisas que eu fiz nos updates
        for(auto v: graph[u]){
            if(v == ant || vis[v]) continue;
            reset(v,u,d+1);
        }
    }
    void calc(int u){
        qtd[0] = 1;
        for(auto v: graph[u]){
            if(vis[v]) continue;
            calc(v,u,tam[u]); // calcular essa subarvore, passo esse tamanho pra dar uma otimizada no limite dessa subarvore
            update(v,u); // atualizar essa subarvore
        }
        // limpa as coisas
        reset(u,u);
    }
};
