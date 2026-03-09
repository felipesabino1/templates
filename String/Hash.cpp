// Indexado de 0
// Se quiser economizar memoria coloca o ppow global
// Quando for escolher os primos, escolhe um do tamanho do alfabeto mais ou menos
// O(n)
const int qt_hash = 2;
const vc<uint64_t> p = {33,73}, mod = {1e9+7,1e9+9};
struct Hash {
    vvc<uint64_t> h,ppow;

    Hash(string & s) {
        init(s);
    }
    Hash(){}
 
    void init(string &s){
        int n = s.size();
        ppow.resize(qt_hash), h.resize(qt_hash);
        for(int t=0; t<qt_hash; t++) h[t].resize(s.size() + 2), ppow[t].resize(s.size()+2);
        for(int t=0; t<qt_hash; t++) h[t][0] = 5389ULL, ppow[t][0] = 1;
        for(int t=0; t<qt_hash; t++) for(int i=1; i<s.size()+2; i++) ppow[t][i] = ppow[t][i-1] * p[t] % mod[t];
        for(int t=0; t<qt_hash; t++) for(int i=0; i<s.size(); i++) h[t][i+1] = (h[t][i] * p[t] + s[i]) % mod[t];
    }
 
    // vou incluir o range [i,j], indexado de 0
    // se quiser que seja mais rapido retorna um pair
    vc<uint64_t> get_hash(int l,int r){
        vc<uint64_t> r(qt_hash);
        for(int t=0; t<qt_hash; t++)
            r[t] = (h[t][j+1] - (h[t][i] * ppow[t][j-i+1]) % mod[t] + mod[t]) % mod[t];
        return r;
    }
};
