// Indexado de 0
// Realiza a Centroid Decomposition da arvore
// O(N * log(N))
struct Centroid{
    vector<vector<int>> & graph; // referencia da arvore original
    int r; // raiz do centroid
    vc<int> tam,p; vc<bool> vis; // tam de subarvore, pais do centroide
    // vc<ll> cnt;
    // ll qt = 0;

    Centroid(vvc<int> &g) : graph(g),tam(g.size()),p(g.size()),vis(g.size()){
        r = build(0);
    }

    // constroi o centroid decomposition
    int build(int u){
        set_tam(u,u);
        u = get(u);
        vis[u]=1;

        // se tiver que fazer algum calculo durante o centroid decomposition
        // calc(u);

        p[u]=u;
        for(auto v: graph[u]) if(!vis[v]) p[build(v)] = u;
        return u;
    }

    void set_tam(int u,int ant){
        tam[u]=1;
        for(auto v: graph[u]) if(v != ant && !vis[v]){
            set_tam(v,u);
            tam[u]+=tam[v];
        }
    }
    int get(int u){
        for(auto v : graph[u]) if(!vis[v] && 2*tam[v] > tam[u]){
            tam[u]-=tam[v];
            tam[v]+=tam[u];
            return get(v);
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
