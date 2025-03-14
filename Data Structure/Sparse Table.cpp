/*
    Indexado de 1.
    Responde uma operacao num subarray, a operacao precisa ser associativa e de preferencia ter uma identidade.
    Init: O(N*log(N)).
    Query: O(log(N)) ou O(1) para operacoes idempotentes. 

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

    SparseTable(int n) : n(n){
        pot2.resize(n+10);
        pot2[1] = 0;
        for(int i=2; i<=n; i++) pot2[i] = pot2[i>>1] + 1;
        tab.resize(n+10,vector<TT>(pot2[n]+1));
        TETO = pot2[n]+1;    
    }
    SparseTable(int n, vector<TT> & a) : n(n){
        pot2.resize(n+10);
        pot2[1] = 0;
        for(int i=2; i<=n; i++) pot2[i] = pot2[i>>1] + 1;
        tab.resize(n+10,vector<TT>(pot2[n]+1));
        TETO = pot2[n]+1;
        build(a); // build da Sparse Table
    }
    SparseTable(int n, TT * a) : n(n){
        pot2.resize(n+10);
        pot2[1] = 0;
        for(int i=2; i<=n; i++) pot2[i] = pot2[i>>1] + 1;
        tab.resize(n+10,vector<TT>(pot2[n]+1));
        TETO = pot2[n]+1;
        build(a); // build da Sparse Table
    }

    ~SparseTable(){tab.clear(); pot2.clear();}

    void init(int n_new,vector<TT> & a){
        n = n_new;
        TETO = pot[n] + 1;
        build(a);
    }
    void init(int n_new,TT * a){
        n = n_new;
        TETO = pot[n] + 1;
        build(a);
    }

    void build(vector<TT> & a){
        for(int i=1; i<=n; i++) tab[i][0] = a[i];
        for(int j=1; j<TETO; j++) for(int i=0; i+(1<<j)-1 <= n; i++) tab[i][j] = f(tab[i][j-1],tab[i+(1<<(j-1))][j-1]);
    }
    void build(TT * a){
        for(int i=1; i<=n; i++) tab[i][0] = a[i];
        for(int j=1; j<TETO; j++) for(int i=0; i+(1<<j)-1 <= n; i++) tab[i][j] = f(tab[i][j-1],tab[i+(1<<(j-1))][j-1]);
    }

    // operacao da sparse table
    TT f(TT x, TT y){
        return ;
    }

    TT query(int l,int r){
        if(l > r) return off;
        TT ans = off;
        for(int j=TETO-1; j>=0; j--){
            if(l+(1<<j)-1 <= r){
                ans = f(ans, tab[l][j]);
                l +=(1<<j);
            }
        }
        return ans;
    }
    // query idempotente
    TT query_id(int l,int r){
        if(l > r) return off;
        int diff = pot2[r-l+1];
        return f(tab[l][diff],tab[r-(1<<diff)+1][diff]);
    }
};
