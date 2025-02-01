/*
    Indexado de 1.

    Alteracoes:
*/
struct VirtualTree{
    struct VTLCA{
        vector<vector<int>> &graph; // grafo original
        int n; // qtd de vertices
        int timer=0;
        // entrada, saida 
        vector<int> tin,tout;
        int flag; // (flag == 1 ? tin != tout : tin == tout)
        vector<int> dist; // distancia de cada cara pra raiz
        vector<vector<int>> pai; // tabela de ancestrais
        int r; // raiz
        int TETO; // teto(log2(n))

        VTLCA(int n, vector<vector<int>> &graph, int flag=0, int r=1) : n(n), graph(graph), flag(flag), r(r){
            tin.resize(n+10);
            tout.resize(n+10);
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

        int calc_lca(int x,int y){
            if(lca(x,y)) return x;
            else if(lca(y,x)) return y;
            int z=x;
            for(int i=TETO-1; i>=0; i--){
                if(!lca(pai[z][i],y)) z=pai[z][i];
            }
            z = pai[z][0];
            return z;
        }
    };

    vector<vector<int>> & graph; // grafo original
    vector<vector<int>> tree; // virtual tree
    int r; // raiz da virtual tree
    int n; // qtd de vertices
    VTLCA lca;

    VirtualTree(int n, vector<vector<int>> & graph) : n(n), graph(graph), lca(n,graph){
        tree.resize(n+10);
    }

    void build(vector<int> & vtx){
        // ordena pelo tempo de entrada
        sort(vtx.begin(),vtx.end(),[&](int x,int y){
            return lca.tin[x] < lca.tin[y];
        });
        // adiciona os lcas
        int sz = vtx.size();
        for(int i=0; i<sz-1; i++) vtx.push_back(lca.calc_lca(vtx[i],vtx[i+1]));
        sort(vtx.begin(),vtx.end(),[&](int x,int y){
            return lca.tin[x] < lca.tin[y];
        });
        // tira os caras repetidos e limpa a arvore de queries anteriores
        unique(vtx.begin(),vtx.end());
        sz = vtx.size();
        for(int i=0; i<sz; i++) tree[vtx[i]].clear();
        
        // arruma as arestas da virtual tree
        vector<int> st;
        st.push_back(vtx[0]);
        r = vtx[0];
        for(int i=1; i<sz; i++){
            while(!lca.lca(st.back(),vtx[i])) st.pop_back();
            
            tree[st.back()].push_back(vtx[i]);
            tree[vtx[i]].push_back(st.back());
            
            st.push_back(vtx[i]);
        }        
    }
};
