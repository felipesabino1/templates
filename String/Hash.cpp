/*
  Indexado de 0
  
  O static eh variavel de classe.
*/
struct Hash {
    int qt_hash = 2; // qtd de hashs
    inline const static vector<uint64_t> p = {33,73};
    inline const static vector<uint64_t> mod = {1'000'000'007,1'000'000'009};
    vector<vector<uint64_t>> h; // quantas hashs eu quiser guardar por string
    /*
        Quando vc quer declarar variavel de classe e quer definir ela dentro da classe, vc tem que usar o inline
        https://medium.com/@martin00001313/mastering-static-objects-in-c-initialization-destruction-and-best-practices-760b17734195
    */
    inline static vector<vector<uint64_t>> ppow;
    inline static int tam_ppow=0;
    int n;

    Hash(string & s) {
        n = s.size();
        build();
        init(s);
    }

    void build(){
        if(ppow.empty()){
            ppow.resize(qt_hash);
            
            tam_ppow=1;
            for(int t=0; t<qt_hash; t++) ppow[t].resize(1);
            for(int t=0; t<qt_hash; t++) ppow[t][0] = 1;
        }
        if(tam_ppow < n+2){
            for(int t=0; t<qt_hash; t++) ppow[t].resize(n+2);
            
            for(int i = tam_ppow; i<n+2; i++)
                for(int t=0; t<qt_hash; t++) 
                    ppow[t][i] = (ppow[t][i-1] * p[t]) % mod[t];
            
            tam_ppow=n+2;
        }
    }
 
    void init(string &s) {
        h.resize(qt_hash);
        for(int t=0; t<qt_hash; t++) h[t].resize(s.size() + 2);
        for(int t=0; t<qt_hash; t++) h[t][0] = 5389ULL;

        for (size_t i = 0; i < s.size(); i++) {
            int code = s[i];
            for(int  t=0; t<qt_hash; t++)
                h[t][i+1] = (h[t][i] * p[t] + code) % mod[t];
        }
    }
 
    // vou incluir o range [i,j], indexado de 0
    vector<uint64_t> get_hash(int i, int j) {
        vector<uint64_t> r(qt_hash);
        for(int t=0; t<qt_hash; t++) 
            r[t] = (h[t][j+1] - (h[t][i] * ppow[t][j-i+1]) % mod[t] + mod[t]) % mod[t];
        return r;
    }
};
