/*
    Indexado de 1.
    Responde uma operacao num subarray, a operacao precisa ser associativa e de preferencia ter uma identidade.
    Init: O(N*log(N)).
    Query: O(1) 

    Alteracoes: 
    Funcao f(), valor off
*/
template <class TT = ll>
struct DST{
    int n; // tamanho do vetor original
    vector<vector<TT>> tab; // disjoint sparse table
    const TT off = ; // identidade
    int TETO_DST; // menor potencia tal que 2^TETO_DST >= n
    vector<int> pot2; // log2 de cada numero

    DST(int n_) : n(n_){
        TETO_DST = 0;
        int lim = 1;
        while(lim < n) lim <<= 1, TETO_DST++;
        pot2.resize(lim);
        pot2[1] = 0;
        for(int i=2; i<lim; i++) pot2[i] = pot2[i>>1] + 1;
        tab.resize(TETO_DST+1,vector<TT>(lim,off));
    }
    DST(int n_, vector<TT> & a) : n(n_){
        TETO_DST = 0;
        int lim = 1;
        while(lim < n) lim <<= 1, TETO_DST++;
        pot2.resize(lim);
        pot2[1] = 0;
        for(int i=2; i<lim; i++) pot2[i] = pot2[i>>1] + 1;
        tab.resize(TETO_DST+1,vector<TT>(lim,off));
        init(a);
    }

    void init(vector<TT> & a){
        int lim = 1<<TETO_DST;
        // qtd de blocos
        for(int i=0; i<TETO_DST; i++){
            int tam = (1<<(TETO_DST-i)); // tamanho do bloco
            // bloco atual
            for(int j=0; j<(1<<i); j++){
                int init = j*tam;
                int end = (j+1)*tam-1;
                int mid = (init + end)>>1;

                // primeira metade eh um sufixo
                tab[i][mid] = (mid+1 <= n ? a[mid+1] : off); // vetor de entrada eh indexado de 1
                for(int k=mid-1; k>=init; k--) tab[i][k] = f((k+1 <= n ? a[k+1] : off),tab[i][k+1]);

                // segunda metade eh um prefixo
                tab[i][mid+1] = (mid+2 <= n ? a[mid+2] : off); // vetor de entrada eh indexado de 1
                for(int k=mid+2; k<=end; k++) tab[i][k] = f((k+1 <= n ? a[k+1] : off),tab[i][k-1]);
            }
        }   
        for(int j=0; j<lim; j++) tab[TETO_DST][j] = (j+1 <= n ? a[j+1] : off);
    }

    // operacao da DST
    TT f(TT x, TT y){
        return ;
    }

    // query inclusiva nos ranges
    TT query(int l,int r){
        if(l > r) return off;
        l--, r--;
        if(l == r) return tab[TETO_DST][l];
        int level = TETO_DST - pot2[l^r] - 1;
        return f(tab[level][l],tab[level][r]);
    }
};
