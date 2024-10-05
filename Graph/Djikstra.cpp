/*
    Indexado de 1

    Alteracoes:
    Mudar a info da priority_queue, o operador tem que como vc n quer que esteja ordenado (negar)
    Mudar o calculo da distancia
*/
typedef ll TT;
struct Djikstra{    
    // o que a priority_queue carrega de info
    struct info{
        TT z;
        int u;

        bool const operator <(const info & o) const{
            // as vezes tem mais coisa

            // !(z < o.z) == z >= o.z (mas n pode ter coisa de igual ou maior se n da merda)
            return z > o.z;
        }
    };

    const TT inf = 1e18;
    vector<TT> dist;
    priority_queue<info> pq;
    int n;

    // qtd de vertices
    Djikstra(int n){
        this->n = n;
        dist.resize(n+10);
    }

    // calculo da distancia
    void calc(int u,int v, TT z, TT c){
        if(dist[v] > z+c){
            dist[v] = z+c;
            pq.push({dist[v], v});
        }
    }

    void solve(int init){
        for(int i=1; i<=n; i++) dist[i]=inf;

        dist[init]=0;
        // passar de acordo com o info
        pq.push({0,init});

        while(!pq.empty()){
            auto [z,u] = pq.top();
            pq.pop();
            if(dist[u] != z) continue;
            for(auto [v,c] : graph[u]){
                // as vezes tem que passar mais coisa
                calc(u,v,z,c);
            }
        } 
    }
};
