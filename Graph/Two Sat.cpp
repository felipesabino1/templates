// Indexado de 1
struct TWOSAT{
    #define pos(x) ((x)<<1)
    #define neg(x) (pos(x)|1)
    int n; // quantidade de proposicoes
    vector<vector<int>> graph,inv;
    vector<int> ord,vis,val;
    int timer=1;

    TWOSAT(int nn) : n(nn),graph(pos(nn)+2),inv(pos(nn)+2),vis(pos(nn)+2), val(nn+1,0){}
    void init(int nn){n = nn;}
    void clear(){
        for(int i=0; i<=n; i++) val[i] = 0;
        for(int i=1; i<=n; i++) graph[pos(i)].clear(),graph[neg(i)].clear();
        for(int i=1; i<=n; i++) inv[pos(i)].clear(),inv[neg(i)].clear();
        ord.clear();
    }

    // adicionar um OR
    // cada vertice eh uma proposicao, pra cada proposicao tem dois novos vertices (x<<1) e (x<<1)|1 (ele normal e negado)
    // o na,nb diz se eu me refiro a proposicao a,b negadas
    void add_edge(int a, int na, int b,int nb){
        int aa = pos(a)^na, bb = pos(b)^nb;
        graph[aa^1].push_back(bb);
        graph[bb^1].push_back(aa);
        inv[bb].push_back(aa^1);
        inv[aa].push_back(bb^1);
    }

    void set_ord(int u){
        vis[u] = 1;
        for(auto v : graph[u]){
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
    void solve(){
        for(int i=1; i<=n; i++) vis[pos(i)] = vis[neg(i)] = 0;
        // componentes conexas
        for(int i=1; i<=n; i++) {
            if(!vis[pos(i)]) set_ord(pos(i));
            if(!vis[neg(i)]) set_ord(neg(i));
        }
        reverse(ord.begin(),ord.end());
        for(int i=1; i<=n; i++) vis[pos(i)] = vis[neg(i)] = 0;
        for(auto u : ord) if(!vis[u]) set_comp(u),timer++;

        // ver se tem contradicao
        for(int i=1; i<=n; i++) if(vis[pos(i)] == vis[neg(i)]) val[0] = 1;
        
        // setar os valores de cada proposicao
        for(int i=1; i<=n; i++){
            if(vis[pos(i)] < vis[neg(i)]) val[i] = 0; // eh falso
            else val[i] = 1; // eh verdadeiro
        }
    }

    void show(){
        // se for val[0] == 1 eh pq nao da
        if(val[0]) cout << "IMPOSSIBLE\n";
        else{
            for(int i=1; i<=n; i++){
                if(i != 1) cout << ' ';
                cout << (val[i] ? '+' : '-');
            }
            cout << '\n';
        }
    }
    #undef pos
    #undef neg
};
