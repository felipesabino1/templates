/*
    Alteracoes:

    Alterar a funcao g de dentro da funcao de lagrange
    Na funcao que o faz o lagrange mesmo, alterar os parametros da funcao g de acordo com o que foi faz
*/
struct Lagrange{
    vector<ll> pref,suf;
    vector<ll> invfat;
    vector<ll> y;
    // valor x que quer calcular e o grau do polinomio n
    ll x,n;
    ll mod;
    // geralmente o negocio da funcao precisa de mais informacao
    ll pte;

    void set__(){
        pref[0]=1;
        suf[n+2]=1;
        for(ll i=1; i<=n+1; i++) pref[i]=pref[i-1]*((x-i)%mod)%mod;
        for(ll i=n+1; i>0; i--) suf[i]=suf[i+1]*((x-i)%mod)%mod;
        ll fat=1;
        invfat[0]=1;
        for(ll i=1; i<=n+1; i++){
            fat=fat*i%mod;
            invfat[i]=fexp(fat,mod-2);
        }
        y[0]=0;
        for(int i=1; i<=n+1; i++) y[i]=(y[i-1]+g())%mod;
    }

    void set2__(){
        pref[0]=1;
        suf[n+2]=1;
        for(ll i=1; i<=n+1; i++) pref[i]=pref[i-1]*((x-i)%mod)%mod;
        for(ll i=n+1; i>0; i--) suf[i]=suf[i+1]*((x-i)%mod)%mod;
    }

    Lagrange(ll x, ll n,ll mod, ll pte){
        pref.resize(n+3);
        suf.resize(n+3);
        invfat.resize(n+3);
        y.resize(n+3);
        
        this->x=x;
        this->n=n;
        this->mod=mod;
        this->pte=pte;
        
        set__();
    }

    // exponenciacao binaria
    ll fexp(ll a, ll b){
        a%=mod;
        ll ans=1;
        while(b){
            if(b&1) ans=ans*a%mod;
            b>>=1;
            a=a*a%mod;
        }
        return ans;
    }

    // se eu so quiser mudar o x que eu calculo do polinomio, so preciso alterar o prefixo e o sufixo
    void mudax(ll x){
        this->x = x;

        set2__();
    }

    // funcao de dentro do polinomio de lagrange
    ll g(){
        
    }

    // o que calcula o valor do polinomio no ponto n, com grau k (lg - lagrange)
    ll lg(){
        if(x <= n+1){
            ll ans=0;
            // calcula o somatorio ate o n normal
            for(int i=1; i<=x; i++) ans=(ans+g())%mod;
            return ans;
        }else{
            ll ans=0;
            for(int i=1; i<=n+1; i++){
                // g(i)*produtorio(x-j)/produtorio(i-j)
                ll aux=y[i]*pref[i-1]%mod;
                aux=aux*suf[i+1]%mod;
                aux=aux*invfat[n+1-i]%mod;
                aux=aux*invfat[i-1]%mod;

                // o -1 do produtorio(i-j)
                if((n+1-i)&1) aux*=-1;
                while(aux < 0) aux+=mod;

                // adiciona esse cara no polinomio de lagrange
                ans=(ans+aux)%mod;
            }

            return ans;
        }
    }
};
