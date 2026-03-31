// Revisoes da stack indexadas de 0
// Push e pop: O(1)
struct perstack{
    struct info{

    };
    struct node{
        info val;int prox = 0;
        node(info vall,int proxx) : val(vall),prox(proxx){}
    };
    vc<node> vals; // nodes
    vc<int> rev; // qual o node do topo dessa revisao?
    void push(info x, int r=-1){rev.push_back(st.size()), st.emplace_back(x,r);}
    void pop(int r=-1){rev.push_back(vals[rev[r]].prox);}
};
