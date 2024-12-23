/*
    Alteracoes:

    N hora de dar insert nos intervalos, ver qual tipo de merge que deve considerar l-r r+1-r2 vira l-r2 ou se nao.
*/
template <class TT = int>
struct STI{
    struct interval{
        TT l,r;
        interval(TT l,TT r) : l(l),r(r){}
        interval(TT x) : l(x),r(x){}

        bool operator <(const interval & ot)const{
            if(l == ot.l) return r < ot.r;
            return l < ot.l;
        }
    };

    set<interval> st;
    TT qtd = 0; // qtd de pontos
    const TT off_l = -1; // o L mais a esquerda, pra nao existir 

    void clear(){
        qtd = 0;
        st.clear();
    }

    void insert(TT l, TT r){
        // arrumando os caras que me pega por tras
        auto it = st.lower_bound(interval(l,off_l));
        while(!st.empty() && it != st.begin()){
            it--;
            // (l1-r1),(r1+1-r2) -> (l1-r2)
            // if(it->r < l-1) break;
            // (l1-r1),(r+1-r2) -> (l1-r1),(r+1-r2)
            if(it->r < l) break;
            qtd -= it->r - it->l + 1;
            l = min(it->l,l);
            r = max(it->r,r);
            it = st.erase(it);
        }
        // arrumando os caras que eu pego
        it = st.lower_bound(interval(l,off_l));
        while(!st.empty() && it != st.end()){
            // (l1-r1),(r1+1-r2) -> (l1-r2)
            // if(it->l > r+1) break;
            // (l1-r1),(r+1-r2) -> (l1-r1),(r+1-r2)
            if(it->l > r) break;
            qtd -= it->r - it->l + 1;
            l = min(it->l,l);
            r = max(it->r,r);
            it = st.erase(it);
        }
        qtd += r - l + 1;
        st.insert(interval(l,r));
    }
    void insert(TT x){
        insert(x,x);
    }
};
