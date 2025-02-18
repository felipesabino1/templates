/*
    Indexado de 1

    Alteracoes: 
    
    Funcao f() da tabela, valor off
*/
template <class TT = ll>
struct SparseTable{
    int n; // tamanho 
    vector<vector<TT>> tab; // sparse table
    vector<int> pot2; // log de cada valor
    int TETO; // Teto do log2(n)
    const TT off = ;

    SparseTable(int n, vector<TT> &a) : n(n){
        int t=0;
        int d=1;
        while(d <= n){
            t++;
            d<<=1;
        }
        TETO = t;
        tab.resize(n+10,vector<TT>(TETO));
        build(a); // build da Sparse Table
    }
    SparseTable(int n, TT * a) : n(n){
        int t=0;
        int d=1;
        while(d <= n){
            t++;
            d<<=1;
        }
        TETO = t;
        tab.resize(n+10,vector<TT>(TETO));
        pot2.resize(n+10);
        build(a); // build da Sparse Table
    }

    ~SparseTable(){tab.clear(); pot2.clear();}

    void build(vector<TT> & a){
        pot2[1] = 0;
        for(int i=2; i<=n; i++) pot2[i] = pot2[i>>1] + 1;
        
        for(int i=1; i<=n; i++) tab[i][0] = a[i];
        for(int j=1; j<TETO; j++) for(int i=0; i+(1<<j)-1 <= n; i++) tab[i][j] = f(tab[i][j-1],tab[i+(1<<(j-1))][j-1]);
    }
    void build(TT * a){
        pot2[1] = 0;
        for(int i=2; i<=n; i++) pot2[i] = pot2[i>>1] + 1;

        for(int i=1; i<=n; i++) tab[i][0] = a[i];
        for(int j=1; j<TETO; j++) for(int i=0; i+(1<<j)-1 <= n; i++) tab[i][j] = f(tab[i][j-1],tab[i+(1<<(j-1))][j-1]);
    }

    // operacao da sparse table
    TT f(TT x, TT y){
        return ;
    }

    TT query(int l,int r){
        TT ans = off;
        for(int j=TETO-1; j>=0; j--){
            if(l+(1<<j)-1 <= r){
                ans = f(ans, tab[l][j]);
                l +=(1<<j);
            }
        }
        return ans;
    }
    // query idepotente
    TT query_id(int l,int r){
        int diff = pot2[r-l+1];
        return f(tab[l][diff],tab[r-(1<<diff)+1][diff]);
    }
};
