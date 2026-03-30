// Indexado de 1
// Query de op associativas e updt sobre paths 
// Init - 8*N
// Query - 4*log^2(N) (vai ser melhor que isso)
// Update - 4*log^2(N) (vai ser melhor que isso)
// Se a op eh simetrica da pra ignorar o iseg e fazer so com o seg (iseg.query(inv(l),inv(r)) -> seg.query(dir(r),dir(l)))
struct HLD{
    // struct Seg{...}
    int n,timer; bool sim;
    vector<int> tam,tin,hd,p,lst;
    #warning definir o tipo do euler
    vector<T> euler; 
    Seg seg,iseg;
    void dfs(int u,int ant=-1, int f=-1){
        tam[u] = 1, euler[tin[u] = ++timer] = VEC[u];
        p[u] = (ant == -1 ? u : ant), hd[u] = (ant == -1 ? u : hd[u]);
        for(auto& v : g[u]) if(v != ant){
            hd[v] = (v == g[u][0] ? hd[u] : v);
            dfs(v,u,f); tam[u] += tam[v];
            if(tam[v] > tam[g[u][0]] || g[u][0] == ant) swap(v,g[u][0]);
        }
        if (ant*f == -1) build_hld(hd[u]=u,-1,timer=0);
    }
    HLD(int nn,int r=1) : n(nn),timer(0),tam(nn+1),tin(nn+1),hd(nn+1),p(nn+1),lst(nn+1,0),euler(nn+1){
        dfs(r,r);
        seg.init(nn,euler); 
        // se for comutativo nao precisa
        reverse(euler.begin()+1,euler.end());
        iseg.init(nn,euler);
        reverse(euler.begin()+1,euler.end());
    }
    // u eh lca de v?
    bool lca(int u, int v){return tin[u] <= tin[v] && tin[v]+tam[v]-1 <= tin[u]+tam[u]-1;}
    #define dir(u) tin[u]
    #define inv(u) n-tin[u]+1
    #define merge seg.merge
    // query no path de u->v
    Seg::node query_path(int u,int v){
        seg::node a1,a2,ru,rv;
        a1.off = a2.off = ru.off = rv.off = true;
        for(; !lca(hd[u],v); u=p[hd[u]])
            merge(a1 = ru, a2 = iseg.query(inv(u),inv(hd[u])), ru);
        for(; !lca(hd[v],u); v=p[hd[v]])
            merge(a2 = seg.query(dir(hd[v]),dir(v)), a1 = rv, rv);
        if(lca(u,v)) merge(a2 = seg.query(dir(u),dir(v)), a1 = rv, rv);
        else merge(a1 = ru, a2 = iseg.query(inv(u),inv(v)), ru);        
        merge(a1 = ru, rv, ru);
        return ru;
    }
    // update no path u->v
    void update_path(int u,int v, sono x){
        for(; !lca(hd[u],v); u=p[hd[u]])
            seg.update(dir(hd[u]),dir(u),x),iseg.update(inv(u),inv(hd[u]),x);
        for(; !lca(hd[v],v); v=p[hd[v]])
            seg.update(dir(hd[v]),dir(v),x),iseg.update(inv(v),inv(hd[v]),x);

        if(lca(u,v))
            seg.update(dir(u),dir(v),x),seg.update(inv(v),inv(u),x);
        else
            seg.update(dir(v),dir(u),x),iseg.update(inv(u),inv(v),x);
    }
    #undef dir
    #undef inv
    #undef merge
    Seg::node query_tree(int u){return seg.query(tin[u],tin[u]+tam[u]-1);}
    void update_tree(int u){seg.update(tin[u],tin[u]+tam[u]-1);}
};
