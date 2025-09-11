/*
    Indexado de 1
*/
struct Centroid{
    vector<vector<int>> & graph; // referencia da arvore original
    int n; // qtd de vertices 
    vector<int> tam; // tam da subarvore
    vector<bool> vis; // visitado para construir o centroide
    vector<int> p; // o pai de cada cara no centroide
    int r; // raiz do centroide
    // vector<ll> cnt;
    // ll qt = 0;

    Centroid(int nn, vector<vector<int>> & ggraph) : n(nn), graph(ggraph), tam(nn+1),vis(nn+1,false),p(nn+1){
        // cnt.resize(nn+1);
        r = build(1);
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
            calc(v,u,sz);
        }
    }
    void update(int u,int ant){
        // faz algum tipo de update
        for(auto v: graph[u]){
            if(v == ant || vis[v]) continue;
            update(v,u);
        }
    }
    void reset(int u,int ant){
        // reseta as coisas que eu fiz nos updates
        for(auto v: graph[u]){
            if(v == ant || vis[v]) continue;
            reset(v,u);
        }
    }
    void calc(int u){
        for(auto v: graph[u]){
            if(vis[v]) continue;
            calc(v,u,tam[u]); // calcular essa subarvore, passo esse tamanho pra dar uma otimizada no limite dessa subarvore
            update(v,u); // atualizar essa subarvore
        }
        // limpa as coisas
        reset(u,u);
    }
};
