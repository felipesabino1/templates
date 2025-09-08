/*
    Indexado de 1 (internamente eh de zero, mas sempre passa considerando que eh indexado de 1).
    Responde uma operacao num subarray, a operacao precisa ser associativa e de preferencia ter uma identidade.
    Init: O(N*log(N)).
    Query: O(1) 

    Alteracoes: 
    Funcao f(), valor off. O nome do vetor que eu faco as operacoes sobre.
*/
template <class TT = ll>
struct DST{
    int n; // tamanho do vetor original
    vector<vector<TT>> tab; // disjoint sparse table
    vector<int> pot2; // log2 de cada numero
    int TETO_DST;
    const TT off = ; // identidade

    DST(int n_) : n(n_){
        TETO_DST = 32 - __builtin_clz(n);
        int N = 1 << TETO_DST;
        pot2.resize(N); pot2[1] = 0;
        for(int i=2; i<N; i++) pot2[i] = pot2[i>>1] + 1;
        tab.resize(TETO_DST+1,vector<TT>(N,off));
    }
    void init(int n_){
        this->n = n_; 
        TETO_DST = 32 - __builtin_clz(n); 
        int N = 1 << TETO_DST;
        for(int i=0; i<=TETO_DST; i++) for(int j=0; j<N; j++) tab[i][j] = off;
        build();
    }
    void build(){
        // qtd de blocos
        for(int i=0; i<TETO_DST; i++){
            int tam = (1<<(TETO_DST-i)); // tamanho do bloco
            // bloco atual
            for(int j=0; j<(1<<i); j++){
                int init = j*tam;
                int end = (j+1)*tam-1;
                int mid = (init + end)>>1;
    
                // primeira metade eh um sufixo
                tab[i][mid] = (mid+1 <= n ? a[mid+1] : off);
                for(int k=mid-1; k>=init; k--) tab[i][k] = f((k+1 <= n ? a[k+1] : off),tab[i][k+1]);
    
                // segunda metade eh um prefixo
                tab[i][mid+1] = (mid+2 <= n ? a[mid+2] : off);
                for(int k=mid+2; k<=end; k++) tab[i][k] = f((k+1 <= n ? a[k+1] : off),tab[i][k-1]);
            }
        }
        for(int j=0; j<(1<<TETO_DST); j++) tab[TETO_DST][j] = (j+1 <= n ? a[j+1] : off);
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
