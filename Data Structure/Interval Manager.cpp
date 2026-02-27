/*
    Alteracoes:

    N hora de dar insert nos intervalos, ver qual tipo de merge que deve considerar l-r r+1-r2 vira l-r2 ou se nao.
*/
template <class TT = int>
struct STI{
    struct interval{
        TT l,r;
        interval(TT a,TT b) : l(a),r(b){}
        interval(TT x) : l(x),r(x){}

        bool operator <(const interval & ot)const{
            if(l == ot.l) return r < ot.r;
            return l < ot.l;
        }
    };

    set<interval> st;
    TT qtd = 0; // qtd de pontos
    const TT off_l = -1; // o L mais a esquerda, pra nao existir 
    // tipo do merge, 1: (a,b)+(b+1,c) = (a,c); 0: (a,b)+(b+1,c) = (a,b) e (b+1,c)
    bool t;

    STI(bool tt = false) : t(tt){}
    void clear(){
        qtd = 0;
        st.clear();
    }

    void insert(TT l, TT r){
        if(l > r) return;
        // arrumando os caras que me pega por tras
        auto it = st.lower_bound(interval(l,off_l));
        while(!st.empty() && it != st.begin()){
            it--;
            if(it->r < l-(t ? 1 : 0)) break;
            qtd -= it->r - it->l + 1;
            l = min(it->l,l), r = max(it->r,r);
            it = st.erase(it);
        }
        // arrumando os caras que eu pego
        it = st.lower_bound(interval(l,off_l));
        while(!st.empty() && it != st.end()){
            if(it->l > r+(t ? 1 : 0)) break;
            qtd -= it->r - it->l + 1;
            l = min(it->l,l), r = max(it->r,r);
            it = st.erase(it);
        }
        qtd += r - l + 1;
        st.insert(interval(l,r));
    }
    void insert(TT x){
        insert(x,x);
    }
};
