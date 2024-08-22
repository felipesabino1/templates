struct FlowEdge{
    int v,u;
    long long cap, flow=0;
    FlowEdge(int v,int u, long long cap) : v(v), u (u), cap(cap){}
};

struct Dinic{
    const long long flow_inf = 1e18;
    vector<FlowEdge> edges;
    vector<vector<int>> adj;
    int n, m = 0;
    int s,t;
    vector<int> level,ptr;
    queue<int> q;

    Dinic (int n,int s,int t) : n(n), s(s), t(t){
        adj.resize(n);
        level.resize(n);
        ptr.resize(n);
    }

    void add_edge(int v,int u, long long cap){
        edges.emplace_back(v,u,cap);
        edges.emplace_back(u,v,0);
        adj[v].push_back(m);
        adj[u].push_back(m+1);
        m+=2;
    }

    bool bfs(){
        fill(leve.begin(),level.end(),-1);
        level[s]=0;
        q.push(s);
        while(!q.empty()){
            int v = q.front();
            q.pop();
            for(int id : adj[v]){
                // se eu n consigo passar flow na aresta, continue
                if(edges[id].cap - edges[id].flow < 1) continue;
                // se eu ja fui no cara do destino antes (ja visitei o cara), continue
                if(level[edges[id].u] != -1) continue;
                level[edges[id].u] = level[v]+1;
                q.push(edges[id].u);
            }
        }
        // se o sink n eh alcancavel, entao n existe caminho
        return level[t] != -1;
    }

    long long dfs(int v, long long pushed){
        if(pushed == 0) return 0;
        // se eu cheguei no sink, retorna o tanto que eu consegui passar de flow
        if(v == t) return pushed;
        // esse vetor eh pra dizer dentro de uma lista de adjacencia ate que ponto eu explorei essa lista de
        // adjacencia, pra eu n repetir aresta, so pra isso mesmo
        for(int &cid = ptr[v]; cid < (int) adj[v].size(); cid++){
            int id = adj[v][cid];
            int u = edges[id].u;
            // se o level do destino (u), for diferente do level atual+1, entao significa que esse cara n faz
            // parte da arvore do bfs, entao eu nem vou andar no cara, ou se eu n consigo passar flow pela aresta
            // entao eu so dou continue 
            if(level[v] + 1 != level[u] || edges[id].cap - edges[id].flow < 1) continue;
            // o tanto que eu vou conseguir passar vai ser o minimo da capacidade e do que eu ja pushei
            long long tr = dfs(u, min(pushed, edges[id].cap-edges[id].flow));
            // n consegui passar fluxo na aresta pro sink
            if(tr == 0) continue;
            // passei o fluxo tr
            edges[id].flow += tr;
            // na aresta reversa eu diminuo o fluxo que passa por ela
            edges[id^1].flow -= tr;
            // consegui passar fluxo numa aresta
            return tr;
        }
        // n consegui passar fluxo
        return 0;
    }

    long long f = 0;
    long long flow(){
        while(true){
            // n consegui construir uma arvore que de pra passar fluxo pro sink
            if(!bfs()) break;
            // resetei o visitado das arestas
            fill(ptr.begin(),ptr.end(),0);
            // enquanto da pra passar fluxo, eu vou passar
            while(long long pushed = dfs(s,flow_inf)) f += pushed;
        }
        return f;
    }

    vector<pair<int,int>> mincut(){
        vector<pair<int,int>> cut;
        bfs();
        for(auto &e : edges){
            // se essa aresta ta saturada, eu consigo alcancar o primeiro cara (v), mas n consigo alcancar
            // o segundo cara (u), entao significa que eu cortei essa aresta, ta no corte minimo
            if(e.flow == e.cap && level[e.v] != -1 && level[e.u] == -1 && e.cap > 0) 
                cut.emplace(e.v,e.u);
        }
        return cut;
    }
};
