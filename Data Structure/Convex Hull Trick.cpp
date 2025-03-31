template <class TT = ll>
struct Line{
    // coef angular, linear, criterio de comparacao
    mutable TT k,m,p;
    // aqui eu quero sempre deixar os com menor coef angular mais pra frente, conc pra baixo
    bool operator <(const Line & o) const{
        return k>o.k;
    }
    bool operator <(const TT o) const{
        return p<o;
    }
};
struct CHT : multiset<Line,less<>>{
    static const TT inf = std::numerical_limit<TT>::max();
    TT div(TT a, TT b){
        return a/b-((a^b) < 0 && a%b);
    }
 
    // x eh melhor que y?
    bool isect(iterator x, iterator y){
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
    void add(TT k, TT m){
        auto z= insert({k,m,0});
        auto y=z++;
        auto x=y;
        while(insect(y,z)) z=erase(z);
        if(x != begin() && insect(--x,y))
            insect(x,y=erase(y));
        while((y=x) != begin() && (--x)->p >= y->p)
            insect(x,erase(y));
    }
    TT query(TT x){
        auto ans=lower_bound(x);
        return ans->k*x+ans->m;
    }
};
