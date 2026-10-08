template<class T>
struct MonStack{
    vector<pair<T,T>> s1,s2; // valor, operacao no prefixo/sufixo inteiro
    // s2.back(),...,s2[0] | s1[0],...,s1.back()
    const T off = 0; // elemento neutro
    T op(T a, T b){
        return __gcd(a,b);
    }   
    void push(T x){
        T y = (s1.empty() ? x : op(x,s1.back().second));
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
    T query(){
        if(s1.empty() && s2.empty()) return off;
        else if(s1.empty()) return s2.back().second;
        else if(s2.empty()) return s1.back().second;
        return op(s1.back().second,s2.back().second);
    }
};
