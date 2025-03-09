template <class TT = ll>
struct Line{
    // coef angular, linear, criterio de comparacao
    mutable T k,m,p;
    // aqui eu quero sempre deixar os com menor coef angular mais pra frente, conc pra baixo
    bool operator <(const Line & o) const{
        return k>o.k;
    }
    bool operator <(const T o) const{
        return p<o;
    }
};
struct CHT : multiset<Line,less<>>{
    static const T inf = std::numerical_limit<TT>::max();
    T div(T a, T b){
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
    void add(T k, T m){
        auto z= insert({k,m,0});
        auto y=z++;
        auto x=y;
        while(insect(y,z)) z=erase(z);
        if(x != begin() && insect(--x,y))
            insect(x,y=erase(y));
        while((y=x) != begin() && (--x)->p >= y->p)
            insect(x,erase(y));
    }
    T query(T x){
        auto ans=lower_bound(x);
        return ans->k*x+ans->m;
    }
};
