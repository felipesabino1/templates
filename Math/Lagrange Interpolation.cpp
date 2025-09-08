/*
    Alteracoes:

    Precisa de modint
    Alterar a funcao f que calcula os valores y do polinomio
    O(N) tal que N eh o grau do polinomio
*/
struct Lagrange{
    vector<mi> pref,suf,invfat,y;
    // valor x que quer calcular e o grau n do polinomio
    ll x;
    int n;
    // geralmente o negocio da funcao precisa de mais informacao
    ll pte;

    mi fexp(mi a, ll b){
        mi ans = 1;
        while(b){
            if(b&1) ans *= a;
            b >>= 1;
            a *= a;
        }
        return ans;
    }
    // funcao que calcula os valores do polinomio real
    mi f(){
        
    }
    Lagrange(ll xx, int nn, ll ptee) : pref(nn+3),suf(nn+3),invfat(nn+3),y(nn+3),x(xx),n(nn),pte(ptee){
        pref[0]=1; suf[n+2]=1;
        for(int i=1; i<=n+1; i++) pref[i]=pref[i-1]*(x-i);
        for(int i=n+1; i>0; i--) suf[i]=suf[i+1]*(x-i);

        mi fat = 1;
        for(int i=1; i<=n+1; i++) fat *= i;
        invfat[n+1] = 1/fat;
        for(int i=n; i>=0; i--) invfat[i] = invfat[i+1]*(i+1);
        
        y[0]=0;
        // na maioria das vezes o y vai ser um somatorio dos anteriores, mas pode n acontecer, y[i] eh o valor do polinomio real em i 
        for(int i=1; i<=n+1; i++) y[i]= y[i-1]+f();
    }

    // se eu so quiser mudar o x que eu calculo do polinomio, so preciso alterar o prefixo e o sufixo
    void mudaX(ll xx){
        this->x = xx;
        pref[0]=1;
        suf[n+2]=1;
        for(int i=1; i<=n+1; i++) pref[i]=pref[i-1]*(x-i);
        for(int i=n+1; i>0; i--) suf[i]=suf[i+1]*(x-i);        
    }

    // o que calcula o valor do polinomio no ponto X, com grau N
    mi lg(){
        mi ans = 0;
        if(x <= n+1){
            // so calcula o valor do polinomio
            ans = y[x];
        }else{
            for(int i=1; i<=n+1; i++){
                // f(i)*produtorio(x-j)/produtorio(i-j)
                mi aux = y[i] * pref[i-1] * suf[i+1] * invfat[n+1-i] * invfat[i-1];
                // o -1 do produtorio(i-j)
                if((n+1-i)&1) aux *= -1;
                // adiciona essa funcao auxiliar
                ans += aux;
            }
        }
        return ans;
    }
};
