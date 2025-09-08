// must have modint
struct Comb{
    vector<mi> fato,fatoinv;
    vector<vector<mi>> tomatoma;
 
    // setar so os fatorias e inversos
    Comb(int n) : fato(n+1),fatoinv(n+1){
        fato[0] = 1;
        for(int i=1; i<=n; i++) fato[i] = fato[i-1] * i;

        fatoinv[n] = fexp(fato[n],mod-2);
        for(int i=n-1; i>=0; i--) fatoinv[i] = fatoinv[i+1] * (i+1);
    }
    Comb(int n,int m) : tomatoma(n+1,vector<mi>(m+1)){
        for(int i=0; i<=m; i++) tomatoma[0][i] = 0;
        for(int i=0; i<=n; i++) tomatoma[i][0] = 1;
        for(int i=1; i<=n; i++) for(int j=1; j<=m; j++) tomatoma[i][j] = tomatoma[i-1][j-1] + tomatoma[i-1][j];
    }

    mi fat(int x){assert(x < fato.size()); return fato[x];}
    mi fat_inv(int x){assert(x < fatoinv.size()); return fatoinv[x];}
    // binomial coefficient
    mi toma(ll n,ll k, bool k_pequeno = false){
        if(n < 0 || k > n) return mi(0);
        mi ans;
        if(tomatoma.size() > n && tomatoma[0].size() > k) ans = tomatoma[n][k];
        else if(k_pequeno){
            ans = 1;
            for(ll i=n; i>n-k; i--) ans *= i;
            ans *= fat_inv(k);
        }else ans = fat(n)*fat_inv(n-k)*fat_inv(k);
        return ans;
    }
    // stars and bars (n stars in k boxes or x1+x2+...+xk = n)
    mi sb(ll n, ll k){
        return toma(n+k-1,k-1);
    }
    // catalan number (how to label n+k pairs of parentheses with k already fixed)
    // k == 0 means normal catalan
    // count how many trees of size n exists when k == 0
    mi catalan(ll n, ll k){
        return mi(k+1) * toma(2*n+k,n) / (n+k+1);
    }
    mi fat_rep(vector<int> &vec){
        mi tot = 0;
        for(int qt : vec) tot += qt;
        mi ans = fat(tot);
        for(int qt : vec) ans /= fat(qt);
        return ans;
    }

    // Soma de uma PA, termo inicial e final, qtd de termos
    mi PA(mi a, mi b, mi n){return (a+b)*n/2;}
    // Soma de uma PG, termo inicial e final, razao
    mi PG(mi a, mi b, mi r){return (b*r - a)/(r-1);}
    // Soma de uma PG infinita (|r| < 1), termo inicial e razao
    mi PG(mi a, mi r){return a/mi(1-r);}
    // Soma de uma PAG (somatorio((a0+i*ra)*(g0*rg^i))), os termos de uma PA multiplicados pelos termos de uma PG
    // (a0+i) - termo da PA || (g0*rg^i) - termo da PG
    // a formula fechada sai pela derivada de uma PG que vira uma PAG (derivar em funcao de rg) 
    // termo inicial e final da PA e a razao, termo inicial e final da PG e a razao
    mi PAG(mi a0, mi an, mi ra, mi g0, mi gn, mi rg){
        return ((an+ra)*(gn*rg) - a0*g0)/(rg-1) + ra*rg*(gn*rg - g0)/((rg-1)*(rg-1));
    }
    // Soma de uma PAG infinita (|r| < 1)
    mi PAG(mi a0, mi ra, mi g0, mi rg){
        return a0*g0/(1-r) + ra*rg*g0/((1-r)*(1-r));
    }
};
