// Indexado de 1
// Query de op associativas sobre paths com updates
// Na media as consultas e updates vao ser poucos (acessar poucos nodes da Seg)
// Init - 8*N
// Query - 4*log^2(N)
// Update - 4*log^2(N)
// Se for fazer build em vector, passar o vector como parametro
// Se a op eh comutativa da pra ignorar o iseg e fazer so com o seg
struct HLD{
    // struct Seg{...}
    int n,timer;
    vector<int> tam,tin,hd,p,lst;
    #warning definir o tipo do euler
    vector<T> euler; 
    vector<Seg> seg,iseg;
    void dfs_tam(int u,int ant){
        tam[u] = 1;
        for(auto& v : graph[u]){
            if(v == ant) continue;
            dfs_tam(v,u); tam[u] += tam[v];
            if(graph[u][0] == ant || tam[v] > tam[graph[u][0]]) swap(v,graph[u][0]);
        }
    }
    void dfs(int u,int ant){
        tin[u] = ++timer, euler[timer] = VEC[u];
        if(u == ant) p[u] = hd[u] = u;
        for(auto v : graph[u]){
            if(v == ant) continue;
            p[v] = u, hd[v] = (v == graph[u][0] ? hd[u] : v);
            dfs(v,u);
        }
    }
    HLD(int nn) : n(nn),timer(0),tam(nn+1),tin(nn+1),hd(nn+1),p(nn+1),lst(nn+1,0),euler(nn+1),seg(nn+1),iseg(nn+1){
        dfs_tam(1,1); dfs(1,1);
        for(int i=1; i<=n; i++) lst[hd[i]] = ((lst[hd[i]] == 0 || tin[i] > tin[lst[hd[i]]]) ? i : lst[hd[i]]);
        #define range euler.begin()+tin[i],euler.begin()+tin[lst[i]]+1
        #define sz tin[lst[i]]-tin[i]+1
        #warning ver como realizar o build
        for(int i=1; i<=n; i++) if(hd[i] == i){
            seg[i].init(sz, vector<int>(range));
            reverse(range);
            iseg[i].init(sz, vector<int>(range));
            reverse(range);
        }
        #undef range
        #undef sz
    }
    // u eh lca de v?
    bool lca(int u, int v){return tin[u] <= tin[v] && tin[v]+tam[v]-1 <= tin[u]+tam[u]-1;}
    #define dir(u) tin[u]-tin[hd[u]]+1
    #define inv(u) tin[lst[hd[u]]]-tin[u]+1
    #define merge seg[0].merge
    // query no path de u->v
    Seg::node query(int u,int v){
        auto aux = seg[0].off, aux2 = seg[0].off, ru = seg[0].off, rv = seg[0].off;
        for(; !lca(hd[u],v); u=p[hd[u]])
            merge(aux = ru, aux2 = iseg[hd[u]].query(inv(u),inv(hd[u])), ru);
        for(; !lca(hd[v],u); v=p[hd[v]])
            merge(aux2 = seg[hd[v]].query(dir(hd[v]),dir(v)), aux = rv, rv);
        if(lca(u,v)) merge(aux2 = seg[hd[v]].query(dir(u),dir(v)), aux = rv, rv);
        else merge(aux = ru, aux2 = iseg[hd[u]].query(inv(u),inv(v)), ru);        
        merge(aux = ru, rv, ru);
        return ru;
    }
    #warning ver como fazer o update
    // update no path u->v
    void update(int u,int v, int x){
        for(; !lca(hd[u],v); u=p[hd[u]]){
            seg[hd[u]].update(dir(hd[u]),dir(u),x);
            iseg[hd[u]].update(inv(u),inv(hd[u]),x);
        }
        for(; !lca(hd[v],v); v=p[hd[v]]){
            seg[hd[v]].update(dir(hd[v]),dir(v),x);
            iseg[hd[v]].update(inv(v),inv(hd[v]),x);
        }
        if(lca(u,v)){
            seg[hd[u]].update(dir(u),dir(v),x);
            iseg[hd[u]].update(inv(v),inv(u),x);
        }else{
            seg[hd[v]].update(dir(v),dir(u),x);
            iseg[hd[v]].update(inv(u),inv(v),x);
        }
    }
    #undef dir
    #undef inv
    #undef merge
};
