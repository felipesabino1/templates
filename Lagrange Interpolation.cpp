/*
    Alteracoes:

    Alterar a funcao g de dentro da funcao de lagrange
    Na funcao que o faz o lagrange mesmo, alterar os parametros da funcao g de acordo com o que foi feito
*/
struct Lagrange{
    vector<ll> pref,suf;
    vector<ll> invfat;
    // valor x que quer calcular e o grau do polinomio n
    ll x,n;
    ll mod;

    void set__(){
        pref[0]=1;
        suf[n+2]=1;
        for(ll i=1; i<=n+1; i++) pref[i]=pref[i-1]*(x-i)%mod;
        for(ll i=n+1; i>0; i--) suf[i]=suf[i+1]*(x-i)%mod;
        ll fat=1;
        invfat[0]=1;
        for(ll i=1; i<=n+1; i++){
            fat=fat*i%mod;
            invfat[i]=fexp(fat,mod-2);
        }
    }

    Lagrange(ll x, ll n,ll mod){
        pref.resize(n+3);
        suf.resize(n+3);
        invfat.resize(n+3);
        
        this->x=x;
        this->n=n;
        this->mod=mod;
        
        set__();
    }

    // exponenciacao binaria
    ll fexp(ll a, ll b){
        ll ans=1;
        while(b){
            if(b&1) ans=ans*a%mod;
            b>>=1;
            a=a*a%mod;
        }
        return ans;
    }


    // funcao de dentro do polinomio de lagrange
    ll g(){
        
    }

    // o que calcula o valor do polinomio no ponto n, com grau k (lg - lagrange)
    ll lg(){
        if(x <= n+1){
            ll ans=0;
            // calcula o somatorio ate o n normal
            for(int i=1; i<=x; i++) ans=(ans+g()%mod)%mod;
            return ans;
        }else{
            ll g2=0;
            ll ans=0;
            for(int i=1; i<=n+2; i++){
                // acumular o valor da funcao de dentro do polinomio de lagrange
                g2=(g2+g())%mod;
                // g(i)*produtorio(x-j)/produtorio(i-j)
                ll aux=g2*pref[i-1]%mod;
                aux=aux*suf[i+1]%mod;
                aux=aux*invfat[n+2-i]%mod;
                aux=aux*invfat[i-1]%mod;

                // o -1 do produtorio(i-j)
                if((n+2-i)&1) aux*=-1;
                while(aux < 0) aux+=mod;

                // adiciona esse cara no polinomio de lagrange
                ans=(ans+aux)%mod;
            }

            return ans;
        }
    }
};
