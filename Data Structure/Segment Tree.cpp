/*
    Indexado de 1.
    Responde uma operacao num subarray, suporta update em range
    Init: O(4*N).
    Query: O(4*log(N))
    Update: O(4*log(N))
*/
template <class TT = int>
struct Seg{
    // inicializar so o tamanho da seg, n fazer o build
    Seg(int n_) : n(n_){
        seg.resize(n<<2);
        lazy.resize(n<<2);
    }

    // fazer o build da estrutura
    void init(int n_new, TT * a){
        n = n_new;
        vec = a;
        build(1,1,n);
    }

    // o que vai ter dentro do no de cada seg
    struct node{

        bool operator ==(const node &ot)const{
            return true;
        }
    };
    // o que vai ter dentro do no de cada lazy
    struct sono{

        bool operator ==(const sono &ot)const{
            return true;
        }
    };

    TT * vec;
    int n;
    // no nulo
    const node off = {};
    // lazy nula
    const sono off_lazy = {}; 
    vector<node> seg;
    vector<sono> lazy;
    // operacao de unir dois nos
    node merge(node x, node y){
        if(x == off) return y;
        if(y == off) return x;
    
    }

    // coisar a lazy pra baixo
    void push(int u,int tl,int tr){
        if(tl == tr || lazy[u] == off_lazy) return;
        // atualizar os filhos

        // atualizar as lazies dos filhos

        lazy[u] = off_lazy;
    }

    // inicializar a seg
    void build(int u,int tl,int tr){
        if(tl == tr){
            // inicializar os caras bases
            seg[u] = {};
            lazy[u] = off_lazy;
            return;
        }
        int tmid = tl + tr;
        tmid >>= 1;
        build(lef(u), tl, tmid);
        build(rig(u), tmid+1, tr);
        seg[u] = merge(seg[lef(u)], seg[rig(u)]);
        lazy[u] = off_lazy;
    }

    // consulta em range
    node query_(int u,int tl,int tr,int l, int r){
        if(l > r) return off;
        if(tl == l && tr == r) return seg[u];
        push(u, tl, tr);
        int tmid= tl + tr;
        tmid >>= 1;
        return merge(query_(lef(u), tl, tmid, l, min(tmid,r)), query_(rig(u), tmid+1, tr, max(tmid+1,l), r));
    }
    node query(int l, int r){
        return query_(1, 1, n, l, r);
    }

    // update em range
    void update_(int u, int tl, int tr, int l, int r, TT x){
        if(l > r) return;
        if(tl == l && tr == r){
            // atualizar a seg e o lazy
            
            return;
        }
        push(u, tl, tr);
        int tmid = tl + tr;
        tmid >>= 1;
        update_(lef(u), tl, tmid, l, min(tmid,r), x);
        update_(rig(u), tmid+1, tr, max(tmid+1,l), r, x);
        seg[u] = merge(seg[lef(u)], seg[rig(u)]);
    }
    void update(int l, int r, TT x){
        update_(1, 1, n, l, r, x);
    }
};
