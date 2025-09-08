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
    const TT off = ;

    SparseTable(int n_) : n(n_), pot2(n_+10){
        pot2[1] = 0;
        for(int i=2; i<=n; i++) pot2[i] = pot2[i>>1] + 1;
        tab.resize(n+10,vector<TT>(pot2[n]+1));
    }
    void build(){
        for(int i=1; i<=n; i++) tab[i][0] = a[i]; // nome do vetor original
        for(int j=1; j<=pot2[n]; j++) for(int i=1; i+(1<<j)-1 <= n; i++) tab[i][j] = f(tab[i][j-1],tab[i+(1<<(j-1))][j-1]);
    }

    // operacao da sparse table
    TT f(TT x, TT y){
        return ;
    }

    TT query(int l,int r){
        if(l > r) return off;
        TT ans = off;
        for(int j=pot2[n]; j>=0; j--){
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
