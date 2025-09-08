namespace MD{
    const ll off = -1; // valor que indica que deu erro em conta
    ll mygcd(ll a, ll b){
        if(a < 0) a*=-1; if(b < 0) b*=-1; if(a > b) swap(a,b);
        ll aux;
        while(a != 0){
            aux = b%a;
            b = a;
            a = aux;
        }
        return b;
    }
    // acha os coeficientes de a*x + b*y = gcd(a,b)
    pair<ll,ll> extended_euclides(ll a, ll b){
        bool trocou = 0, nega = 0, negb = 0;
        if(a < 0) nega=1,a*=-1; if(b < 0) negb=1,b*=-1; if(a > b) swap(a,b),trocou = 1;
        vector<pair<ll,ll>> st;
        ll aux,g,s,t;
        while(a != 0){
            st.push_back(make_pair(a,b));
            aux = b%a; b = a; a = aux;
        }
        g = b, s = 0, t = 1;
        while(!st.empty()){
            a = st.back().first, b = st.back().second, t = s;
            s = (g-t*b)/a;
            st.pop_back();  
        }
        if(nega) t*=-1,s*=-1;
        if(trocou) return make_pair(t,s);
        else return make_pair(s,t);
    }
    // calcula o inverso de a modulo m
    ll inv(ll a, ll m){
        a %= m; if(a < 0) a = m+a;
        if(gcd(a,m) != 1) return off; // nao existe inverso modular
        pair<ll,ll> coef = extended_euclides(a,m);
        return coef.first%m;
    }
    // resolve equacoes do tipo a*x = b (mod m)
    ll solveLinear(ll a, ll b, ll m){
        a %= m; if(a < 0) a = m+a;
        b %= m; if(b < 0) b = m+b;
        ll g;
        while((g = gcd(a,m)) != 1){
            if(b % g != 0) return off; // nao eh uma relacao possivel
            a/=g, b/=g, m/=g;
        }
        a %= m; b %= m;
        pair<ll,ll> coef = extended_euclides(a,m);
        b = b*(coef.first%m)%m;
        return b;
    }
}
using namespace MD;
