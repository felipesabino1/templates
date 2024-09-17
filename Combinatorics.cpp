struct Comb{
    vector<ll> fato,fatoinv;

    Comb(int n){
        fato.resize(n+10,-1);
        fatoinv.resize(n+10,-1);
    }

    Comb(){}

    void set_tam(int n){
        fato.resize(n+10,-1);
        fatoinv.resize(n+10,-1);
    }

    ll fexp(ll a, ll b){
        ll ans=1;
        while(b){
            if(b&1) ans=ans*a%mod;
            b>>=1;
            a=a*a%mod;
        }
        return ans;
    }

    ll fat(ll x){
        if(x <= 1) return 1;
        if(fato[x] != -1) return fato[x];
        return fato[x]=fat(x-1)*x%mod;
    }

    ll fatinv(ll x){
        if(x <= 1) return 1;
        if(fatoinv[x] != -1) return fatoinv[x];
        return fatoinv[x]=fexp(fat(x),mod-2);
    }

    ll toma(ll n, ll k){
        if(k > n) return 0;
        ll ans=fat(n);
        ans=ans*fatinv(k)%mod;
        ans=ans*fatinv(n-k)%mod;
        return ans;
    }
};
