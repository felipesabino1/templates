/*
  Indexado de 0
  
  O static eh variavel de classe.
*/
struct Hash {
    const static uint64_t p=33,mod=1000000007, p2=73, mod2=1000000009;
    vector<pair<uint64_t, uint64_t>> h;
    /*
        Quando vc quer declarar variavel de classe e quer definir ela dentro da classe, vc tem que usar o inline
        https://medium.com/@martin00001313/mastering-static-objects-in-c-initialization-destruction-and-best-practices-760b17734195
    */
    inline static vector<uint64_t> ppow,ppow2;
    inline static int tamp=0;
    int n;

    Hash(string & s) {
        n = s.size();
        build();
        init(s);
    }

    void build(){
        if(ppow.empty()){
            tamp=1;
            ppow.resize(1);
            ppow2.resize(1);
            ppow[0]=ppow2[0]=1;
        }
        if(tamp < n+10){
            ppow.resize(n+10);
            ppow2.resize(n+10);
            for(int i = tamp; i<n+10; i++){
                ppow[i] = (ppow[i-1] * p) % mod;
                ppow2[i] = (ppow2[i-1] * p2) % mod2;
            }
            tamp=n+10;
        }
    }
 
    void init(string &s) {
        h.resize(s.size()+2);
        h[0] = {5389ULL, 5389ULL};
        for (size_t i = 0; i < s.size(); i++) {
            int code = s[i];
            h[i+1].first = (h[i].first * p + code) % mod;
            h[i+1].second = (h[i].second * p2 + code) % mod2;
        }
    }
 
    // vou incluir o range [i,j], indexado de 0
    pair<uint64_t, uint64_t> get_hash(int i, int j) {
        pair<uint64_t, uint64_t> r;
        r.first = (h[j+1].first - (h[i].first * ppow[j-i+1]) % mod + mod) % mod;
        r.second = (h[j+1].second - (h[i].second * ppow2[j-i+1]) % mod2 + mod2) % mod2;
        return r;
    }
};
