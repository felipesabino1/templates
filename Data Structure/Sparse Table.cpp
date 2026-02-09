// Indexado de 0
// Responde operacao associativa em range, nao precisa ter identidade
// Init: O(N * log(N))
// Query: O(log(N)) ou O(1) para idempotente
// Alterar a operacao associativa e o valor off
template <class TT = ll>
struct SparseTable{
    int n; vvc<TT> tab;
    const TT off = ;

    SparseTable(vc<TT>& vec) : n(vec.size()), tab(31-__builtin_clz(vec.size()),vc<TT>(vec.size())){
        for(int i=0; i<n; i++) tab[0][i] = vec[i];
        for(int j=1; j<tab.size(); j++) for(int i=0; i+(1<<j)-1<n; i++) 
            tab[j][i] = f(tab[j-1][i],tab[j-1][i+(1<<(j-1))]);
    }

    // operacao da sparse table
    TT f(TT x, TT y){
        return ;
    }

    TT query(int l,int r){
        if(l > r || r < 0 || l >= n) return off;
        TT ans = off;
        for(int j=0; j<tab.size(); j++) if(get_bit(r-l+1,j)){
            ans = f(ans,tab[j][l]);
            l += (1<<j);
        }
        return ans;
    }
    // query idempotente
    TT query_id(int l,int r){
        if(l > r || r < 0 || l >= n) return off;
        int t = 31 - __builtin_clz(r-l+1);
        return f(tab[t][l],tab[t][r-(1<<t)+1]);
    }
};
