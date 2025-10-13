namespace MD{
    const ll off = -1; // valor que indica que deu erro em conta

    // Euclides estendido: acha x,y tal que ax + by = gcd(a,b)
    // Assume que a,b >= 0, pra converter dps eh facil
    // O(log(min(a,b)))
    tuple<ll,ll,ll> ext_gcd(ll a, ll b){
        if(!a) return {b, 0, sig};
        auto [g,x,y] = ext_gcd(b%a,a);
        return {g,y - b/a*x,x};
    }
    // Combina equacoes modulares lineares: x = a (mod m)
    // O m final eh o lcm dos m's, e a resposta eh unica mod lcm
    // Os m nao precisam ser coprimos e se nao tiver solucao, o 'a' vai ser -1
    struct crt{
        ll a, m;
        crt(ll aa = 0, ll mm = 1) : a(aa), m(mm) {}
        crt operator*(crt c){
            auto [g,x,y] = ext_gcd(m,c.m);
            if((a-c.a)%g) a = -1;
            if(a == -1 || c.a == -1) return crt(-1,0);
            // if(lcm > inf) ai nem precisa de CRT que o a ja vai ser a resposta
            ll lcm = m/g*c.m;
            ll ans = a + (x*(c.a-a)/g % (c.m/g)) * m;
            return crt((ans%lcm + lcm)%lcm,lcm);
        }
    };
    // calcula o inverso de a modulo m
    ll inv(ll a, ll m){
        assert(m > 0);
        a %= m; if(a < 0) a += m;
        auto [g,x,y] = ext_gcd(a,m);
        if(g != 1) return off;
        return x%m + (x < 0 ? m : 0);
    }
    // resolve equacoes do tipo a*x = b (mod m)
    ll solveLinear(ll a, ll b, ll m){
        assert(m > 0);
        a %= m; if(a < 0) a += m;
        b %= m; if(b < 0) b += m;
        ll g = __gcd(a,m);
        if(b%g) return off;
        a /= g, b /= g, m /= g;
        auto [g,x,y] = ext_gcd(a,m);
        return b*(x%m)%m;
    }
}
using namespace MD;
