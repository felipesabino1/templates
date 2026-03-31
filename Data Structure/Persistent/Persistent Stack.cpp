// Revisoes da stack indexadas de 0
// Push e pop: O(1)
struct info{
    
};
template<class T>
struct perstack{
    struct node{
        T val;int prox = 0;
        node(info vall,int proxx) : val(vall),prox(proxx){}
    };
    vc<node> vals; // nodes
    vc<int> rev; // topo da revisao
    void push(T x, int r=-1){rev.push_back(st.size()), st.emplace_back(x,r);}
    void pop(int r){rev.push_back(vals[rev[r]].prox);}
};
