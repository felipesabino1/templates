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
    // multiplicacao de matrizes
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
        if(TT(fatoinv.size()) == x+1) return fatoinv[x] = (fatoinv[x] == -1 ? fexp(fat(x),mod-2) : fatoinv[x]);
        if(fatoinv[x] != -1) return fatoinv[x];
        return fatoinv[x]=fatinv(x+1)*(x+1)%mod;
    }
 
    TT toma(TT n, TT k,int k_pequeno = 0){
        if(n < 0) return 0;
        if(k > n) return 0;
        TT ans;
        if(tomatoma.size() > n && tomatoma[0].size() > k){
            ans = tomatoma[n][k];
        }else if(k_pequeno == 0){
            ans=fat(n);
            ans=ans*fatinv(k)%mod;
            ans=ans*fatinv(n-k)%mod;
        }else{
            // quando k eh pequeno, podemos fazer fat(N)/fat(k)/fat(N-k) = N*(N-1)*(N-2)*...*(N-k+1)/fat(K), ai pra fazer o termo de cima
            // eh so iterar k caras, o de baixo eh de boa tambem.
            ans = 1;
            for(ll i = n; i>n-k; i--) ans = ans*i%mod;
            ans=ans*fatinv(k)%mod;
        }
        return ans;
    }
 
    TT inv(TT x){
        return fexp(x,mod-2);
    }

    // Calcula a soma de uma PA, somatorio_i=k1_k2(a + r*i), temos que k1 >= 0 e k2 >= k1
    // Passa como parametro o termo inicial (a), a razao (r) e k1 e k2
    TT PA(TT a, TT r, TT k1, TT k2){
        if(k1 == 0) return PA_(a,r,k2);
        else return (PA_(a,r,k2) - PA_(a,r,k1-1) + mod)%mod;
    }
    // Calcula a soma de uma PA, somatorio_i=0_k(a + r*i)
    // Passa como parametro o termo inicial (a), a razao (r) e k
    TT PA_(TT a, TT r, TT k){
        return (a + (a + r*k%mod)%mod)%mod * (k+1)%mod * inv(2)%mod;
    }
    // Acha o k-esimo termo de uma PA de razao r comecando do a, e considerando o a como o 0-esimo termo
    TT termPA(TT a, TT r, TT k){
        return (a+r*k%mod)%mod;
    }
 
    // Calcula a soma de uma PG, somatorio_i=k1_k2(a*r^i)
    // Passa como parametro o termo inicial (a), a razao (r) e k1 e k2
    TT PG(TT a, TT r, TT k1, TT k2){
        if(k1 == 0) return PG_(a,r,k2);
        else return (PG_(a,r,k2) - PG_(a,r,k1-1) + mod)%mod;
    }
    // Calcula a soma de uma PG, somatorio_i=0_k(a*r^i)
    // Passa como parametro o termo inicial (a), a razao (r) e k
    TT PG_(TT a, TT r, TT k){
        return a*(fexp(r,k+1)-1+mod)%mod * inv((r-1+mod)%mod)%mod;
    }
    // Calcula a soma de uma PG infinita, somatorio_i=0_inf(a*r^i)
    TT PG(TT a, TT r){
        return a*inv((1-r+mod)%mod)%mod;
    }
    // acha o k-esimo termo de uma PG de razao r comecando do a, e considerando o a como o 0-esimo termo
    TT termPG(TT a, TT r, TT k){
        return a*fexp(r%mod,k)%mod;
    }
 
    // Calcula a soma de uma PAG, somatorio_i=k1_k2(a*(ra*i)*rg^i)
    // Passa como o parametro o termo inicial (a), a razao aritmetica (ra), a razao geometrica (rg) e k1 e k2
    TT PAG(TT a, TT ra, TT rg, TT k1, TT k2){
        if(k1 == 0) return PAG_(a,ra,rg,k2);
        else return (PAG_(a,ra,rg,k2) - PAG_(a,ra,rg,k1-1) + mod)%mod;
    }
    // Calcula a soma de uma PAG, somatorio_i=0_k(a*(ra*i)*rg^i)
    // Passa como o parametro o termo inicial (a), a razao aritmetica (ra), a razao geometrica (rg) e k
    TT PAG_(TT a, TT ra, TT rg, TT k){
        TT ans = a*ra%mod * k%mod *fexp(rg,k+2)%mod;
        ans = (ans - (k+1)*fexp(rg,k+1)%mod + mod)%mod;
        ans = (ans + rg)%mod;
        ans = ans*inv(fexp((1-rg+mod)%mod,2))%mod;
        return ans;
    }
    // Calcula a soma de uma PAG infinita, somatorio_i=0_inf(a*(ra*i)*rg^i)
    // Passa como o parametro o termo inicial (a), a razao aritmetica (ra), a razao geometrica (rg)
    TT PAG(TT a, TT ra, TT rg){
        return a*ra%mod * rg%mod * inv(fexp((1-rg+mod)%mod,2))%mod;
    }
};
