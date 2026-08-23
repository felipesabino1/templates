// Indexado de 0
// Se quiser economizar memoria coloca o ppow global
// Quando for escolher os primos, escolhe um do tamanho do alfabeto mais ou menos
// O(n)
const int qt_hash = 2;
const array<uint64_t,2> p = {33,73}, mod = {1e9+7,1e9+9};
struct Hash {
    vc<array<uint64_t,2>> h,ppow;

    Hash(string & s) {init(s);}
    Hash(){}
 
    void init(string &s){
        h.resize(s.size() + 2), ppow.resize(s.size()+2);
        for(int t=0; t<qt_hash; t++) h[0][t] = 5389ULL, ppow[0][t] = 1;
        for(int i=1; i<s.size()+2; i++) for(int t=0; t<qt_hash; t++) ppow[i][t] = ppow[i-1][t] * p[t] % mod[t];
        for(int i=0; i<s.size(); i++) for(int t=0; t<qt_hash; t++) h[i+1][t] = (h[i][t] * p[t] + s[i]) % mod[t];
    }
 
    // vou incluir o range [i,j], indexado de 0
    // se quiser que seja mais rapido retorna um pair
    array<uint64_t,2> get_hash(int i,int j){
        array<uint64_t,2> r;
        for(int t=0; t<qt_hash; t++)
            r[t] = (h[j+1][t] - (h[i][t] * ppow[j-i+1][t]) % mod[t] + mod[t]) % mod[t];
        return r;
    }
};
