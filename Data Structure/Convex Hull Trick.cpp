// Convex Hull Trick Dinamico
// O(log2(n)) por insercao e query
struct Line{
    // coef angular, linear, criterio de comparacao
    mutable ll k,m,p;
	#warning se for de maximo inverter
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
	#warning se for de maximo inverter
 	ll bst(ll x, ll y){return min(x,y);}
    // x eh melhor que y?
    bool insect(iterator x, iterator y){
        if(y == end()){
            x->p=inf;
            return false;
        }
        if(x->k == y->k)
            x->p= bst(x->m,y->m) == x->m ? inf : -inf;
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


// Convex Hull Trick Estatico
//
// adds tem que serem feitos em ordem de slope
// queries tem que ser feitas em ordem de x
//
// add O(1) amortizado, get O(1) amortizado
struct CHT{
	int it;
	vector<pair<ll,ll>> cht;
	CHT():it(0){}
    ll f(int id, ll x){return cht[id].first*x + cht[id].second;}
    // se vc quer minimizar bota min, senao bota max
    ll bst(ll v1, ll v2){return min(v1,v2);}
    // pra double usar div(a,b) = a/b
    int div(ll a, ll b){return a/b-((a^b) < 0 && a%b);}
	bool useless(){
        int tam = cht.size();
        auto a = cht[tam-3], b = cht[tam-2], c = cht[tam-1];
        return div(b.second-a.second,a.first-b.first) >= div(c.second-b.second,b.first-c.first);
    }
    // add a*x+b
	void add(ll a, ll b){
        if(!cht.empty() && a == cht.back().first) cht.back().second = bst(cht.back().second,b);
        else cht.emplace_back(a,b);

        while(it <= int(cht.size())-3 && useless())
            cht.erase(cht.end()-2);
        
        
        it = min(it, int(cht.size())-1);
	}
    ll query(ll x){
        while(it+1 < cht.size() && f(it+1,x) == bst(f(it+1,x),f(it,x))) it++;
        return f(it,x);
    }
};
