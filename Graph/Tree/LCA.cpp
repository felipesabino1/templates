/*
    Indexado de 1

    Alteracoes:

    As vezes mudar como calcula o calc do lca
*/
struct LCA{
    vector<vector<int>> &graph; // grafo original
    int n; // qtd de vertices
    int timer=0;
    // entrada, saida, e euler tour 
    vector<int> tin,tout,euler;
    int flag; // (flag == 1 ? tin != tout : tin == tout)
    vector<int> dist; // distancia de cada cara pra raiz
    vector<vector<int>> pai; // tabela de ancestrais
    int r; // raiz
    int TETO; // teto(log2(n))

    LCA(int n, vector<vector<int>> &graph, int flag=0, int r=1) : n(n), graph(graph), flag(flag), r(r){
        tin.resize(n+10);
        tout.resize(n+10);
        euler.resize((flag ? 2*n+10 : n+10));
        dist.resize(n+10);
        int t=0;
        int d=1;
        while(d <= n){
            t++;
            d<<=1;
        }
        TETO = t;
        pai.resize(n+10,vector<int>(TETO));

        build(r,r);
    }

    void build(int u,int ant){
        if(u == ant) dist[u]=0;
        else dist[u]=dist[ant]+1;
        
        // construir tabela de ancestrais
        pai[u][0]=ant;
        for(int i=1; i < TETO; i++) {
            pai[u][i]=pai[pai[u][i-1]][i-1];
        }
        
        tin[u]=++timer;
        for(auto v: graph[u]){
            if(v == ant) continue;
            build(v,u);
        }
        
        tout[u]=(flag ? ++timer : timer);
    }

    // x eh lca de y?
    bool lca(int x,int y){
        return tin[x] <= tin[y] && tout[x] >= tout[y];
    }

    // calcula alguma coisa, deixei como se fosse dist, entre x e y
    int calc(int x,int y){
        if(lca(x,y)) return dist[y]-dist[x];
        else if(lca(y,x)) return dist[x]-dist[y];
        int z=x;
        for(int i=TETO-1; i>=0; i--){
            if(!lca(pai[z][i],y)) z=pai[z][i];
        }
        z=pai[z][0];
        return dist[x]+dist[y]-2*dist[z];
    }
};
