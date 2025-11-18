struct Line{
    // coef angular, linear, criterio de comparacao
    mutable ll k,m,p;
    // aqui eu quero sempre deixar os com menor coef angular mais pra frente, conc pra baixo
    bool operator <(const Line & ot) const{
        return k>ot.k;
    }
    // isso aqui n muda
    bool operator <(const ll x) const{
        return p<x;
    }
};
struct CHT : multiset<Line,less<>>{
    // (for doubles, use inf = 1/.0, div(a,b) = a/b)
    static const ll inf = std::numeric_limits<ll>::max();
    ll div(ll a, ll b){
        return a/b-((a^b) < 0 && a%b);
    }
 
    // x eh melhor que y?
    bool insect(iterator x, iterator y){
        if(y == end()){
            x->p=inf;
            return false;
        }
        if(x->k == y->k)
            x->p= x->m <= y->m ? inf : -inf;
        else
            x->p=div(y->m-x->m,x->k-y->k);
        return x->p >= y->p;
    }
    void add(ll k, ll m){
        auto z= insert({k,m,0});
        auto y=z++;
        auto x=y;
        while(insect(y,z)) z=erase(z);
        if(x != begin() && insect(--x,y))
            insect(x,y=erase(y));
        while((y=x) != begin() && (--x)->p >= y->p)
            insect(x,erase(y));
    }
    ll query(ll x){
        auto ans=lower_bound(x);
        #warning cuidado com overflow
        return ans->k*x+ans->m;
    }
};
