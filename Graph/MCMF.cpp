// Indexado de 0
// Se for um dag, da pra substituir o SPFA por uma DP pra nao
// pagar O(nm) no comeco
// Se nao tiver aresta com custo negativo, nao precisa do SPFA
// O(nm + f * m log n)
template <class TT = int, class TT1 = ll>
struct MCMF {
    struct Edge{
        int from,to;
        TT cap,flow = 0;
        TT1 cost;
        Edge(int aa = 0, int bb = 0, TT cc = 0, TT1 ee = 0) : from(aa), to(bb), cap(cc), cost(ee) {}
    };

    MCMF(int size) : n(size), edges(n), dist(n), pot(n,0), visit(n,false), inf(numeric_limits<TT1>::max()){}

    pair<TT, TT1> mcmf(int src, int sink) {
        pair<TT, TT1> ans(0, 0);
        if(!SPFA(src, sink)) return ans;
        fixPot();
        // can use dijkstra to speed up depending on the graph
        while(SPFA(src, sink)) {
            auto flow = augment(src, sink);
            ans.first += flow.first;
            ans.second += flow.first * flow.second;
            fixPot();
        }
        return ans;
    }

    void add_edge(int fr, int to, TT cap, TT1 cost) {
        edges[fr].push_back(list.size());
        list.emplace_back(fr, to, cap, cost);
        edges[to].push_back(list.size());
        list.emplace_back(to,fr,0,-cost);
    }

    int n;
    vector<vector<int>> edges;
    vector<Edge> list;
    vector<int> from;
    vector<TT1> dist, pot;
    vector<bool> visit;
    TT1 inf;

    // bool dij(int src, int sink) {
    //     dist.assign(n, inf);
    //     from.assign(n, -1);
    //     visit.assign(n, false);
    //     dist[src] = 0;
    //     for(int i = 0; i < n; i++) {
    //         int best = -1;
    //         for(int j = 0; j < n; j++) if(!visit[j] && (best == -1 || dist[best] > dist[j])) best = j;
    //         if(dist[best] >= inf) break;
    //         visit[best] = true;
    //         for(auto e : edges[best]) {
    //             auto ed = list[e];
    //             if(ed.flow == ed.cap) continue;
    //             TT1 toDist = dist[best] + ed.cost + pot[best] - pot[ed.to];
    //             assert(toDist >= dist[best]);
    //             if(toDist < dist[ed.to]) {
    //                 dist[ed.to] = toDist;
    //                 from[ed.to] = e;
    //             }
    //         }
    //     }
    //     return dist[sink] < inf;
    // }

    pair<TT, TT1> augment(int src, int sink) {
        pair<TT, TT1> flow = {list[from[sink]].cap - list[from[sink]].flow, 0};
        for(int v = sink; v != src; v = list[from[v]^1].to){
            auto e = list[from[v]];
            flow.first = min(flow.first, e.cap - e.flow);
            flow.second += e.cost;
        }
        for(int v = sink; v != src; v = list[from[v]^1].to) {
            list[from[v]].flow += flow.first;
            list[from[v]^1].flow -= flow.first;
        }
        return flow;
    }

    queue<int> q;
    bool SPFA(int src, int sink) {
        dist.assign(n, inf);
        from.assign(n, -1);
        q.push(src);
        dist[src] = 0;
        while(!q.empty()) {
            int on = q.front();
            q.pop();
            visit[on] = false;
            for(auto e : edges[on]) {
                auto ed = list[e];
                if(ed.flow == ed.cap) continue;
                TT1 toDist = dist[on] + ed.cost + pot[on] - pot[ed.to];
                if(toDist < dist[ed.to]) {
                    dist[ed.to] = toDist;
                    from[ed.to] = e;
                    if(!visit[ed.to]) {
                        visit[ed.to] = true;
                        q.push(ed.to);
                    }
                }
            }
        }
        return dist[sink] < inf;
    }

    void fixPot() {
        for(int i = 0; i < n; i++) {
            if(dist[i] < inf) pot[i] += dist[i];
        }
    }
};
