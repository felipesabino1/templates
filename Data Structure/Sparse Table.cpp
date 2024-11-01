/*
    Indexado de 1

    Alteracoes: 
    
    Funcao f() da tabela, valor off
*/
template <class TT = ll>
struct SparseTable{
    int n; // tamanho 
    vector<vector<TT>> tab; // sparse table
    int TETO; // Teto do log2(n)
    const TT off = ;

    SparseTable(int n, vector<TT> &a){
        this->n = n;
        int t=0;
        int d=1;
        while(d <= n){
            t++;
            d<<=1;
        }
        TETO = t;
        // build da Sparse Table
        for(int i=1; i<=n; i++) tab[i][0] = a[i];
        for(int j=1; j<TETO; j++) for(int i=0; i+(1<<j)-1 <= n; i++) tab[i][j] = f(tab[i][j-1],tab[i+(1<<(j-1))][j-1]);
    }

    ~SparseTable(){}

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
}
