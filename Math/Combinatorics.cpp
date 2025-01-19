template <class TT = ll> 
struct Comb{
    vector<TT> fato,fatoinv;
    vector<vector<TT>> tomatoma;

    // setar so os fatorias e inversos
    Comb(int n){
        set_tam(n);
    }

    // setar so o triangulo de pascal
    Comb(int n,int m){
        set_tomatoma(n,m);
    }

    // setar os fatorias e triangulo de pascal
    Comb(int n2,int n,int m){
        set_tam(n2);
        set_tomatoma(n,m);
    }

    Comb(){}

    void set_tam(int n){
        fato.resize(n+10,-1);
        fatoinv.resize(n+10,-1);
    }

    void set_tomatoma(int n,int m){
        tomatoma.resize(n+10,vector<TT>(m+10));
        for(int i=0; i<=m; i++) tomatoma[0][i]=0;
        for(int i=0; i<=n; i++) tomatoma[i][0]=1%mod;
        for(int i=1; i<=n; i++) for(int j=1; j<=m; j++) tomatoma[i][j] = (tomatoma[i-1][j-1] + tomatoma[i-1][j])%mod;
    }

    TT fexp(TT a, TT b){
        TT ans=1;
        while(b){
            if(b&1) ans=ans*a%mod;
            b>>=1;
            a=a*a%mod;
        }
        return ans;
    }
    void mult(vector<vector<TT>> &a, vector<vector<TT>> &b,vector<vector<TT>> & aux){
        int n = a.size();
        int m = a[0].size();
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                aux[i][j] = 0;
                for(int k = 0; k< n; k++) aux[i][j] = (aux[i][j] + a[i][k]*a[k][j]%mod)%mod;
            }
        }
        for(int i=0; i<n; i++) for(int j=0; j<m; j++) a[i][j] = aux[i][j];
    }

    // calcula e guarda as respostas dos fatoriais
    TT fat(TT x){
        if(TT(fato.size()) <= x){
            fato.resize(x+10,-1);
        }
        if(x <= 1) return 1;
        if(fato[x] != -1) return fato[x];
        return fato[x]=fat(x-1)*x%mod;
    }

    TT fatinv(TT x){
        if(TT(fatoinv.size()) <= x){
            fatoinv.resize(x+10,-1);
        }
        if(x <= 1) return 1;
        if(fatoinv[x] != -1) return fatoinv[x];
        return fatoinv[x]=fexp(fat(x),mod-2);
    }

    TT toma(TT n, TT k){
        if(n < 0) return 0;
        if(k > n) return 0;
        TT ans;
        if(tomatoma.size() > n && tomatoma[0].size() > k){
            ans = tomatoma[n][k];
        }else{
            ans=fat(n);
            ans=ans*fatinv(k)%mod;
            ans=ans*fatinv(n-k)%mod;
        }
        return ans;
    }

    TT inv(TT x){
        return fexp(x,mod-2);
    }
};
