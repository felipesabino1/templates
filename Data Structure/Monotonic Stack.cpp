template<class TT>
struct MonStack{
    vector<pair<TT,TT>> s1,s2; // valor, operacao no prefixo/sufixo inteiro
    // s2.back(),...,s2[0] | s1[0],...,s1.back()
    const TT off = 0; // elemento neutro
    TT op(TT a, TT b){
        return __gcd(a,b);
    }   
    void push(TT x){
        TT y = (s1.empty() ? x : op(x,s1.back().second));
        s1.push_back({x,y});
    }
    void pop(){
        if(s2.empty()) {
            while(!s1.empty()){
                auto [x,y] = s1.back();
                s1.pop_back();
                y = (s2.empty() ? x : op(x,s2.back().second));
                s2.push_back({x,y});
            }
        }
        if(!s2.empty()) s2.pop_back();        
    }
    TT query(){
        if(s1.empty() && s2.empty()) return off;
        else if(s1.empty()) return s2.back().second;
        else if(s2.empty()) return s1.back().second;
        return op(s1.back().second,s2.back().second);
    }
};
