/*
    Indexado de 1.
    Responde uma operacao num subarray, suporta update em range
    Init: O(4*N).
    Query: O(4*log(N))
    Update: O(4*log(N))
*/
struct Seg{
    // inicializar so o tamanho da seg, n fazer o build
    Seg(int n_) : n(n_), seg(n_<<2), lazy(n_<<2){
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

    int n;
    // no nulo
    const node off = {};
    // lazy nula
    const sono off_lazy = {}; 
    vector<node> seg;
    vector<sono> lazy;
    node ret;
    // operacao de unir dois nos
    void merge(node &x, node &y, node & at){
        if(x == off) {
            at = y;
            return;
        }
        if(y == off) {
            at = x;
            return;
        }
        // o at eh o merge do x(esq) e y(dir)
        
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
        merge(seg[lef(u)], seg[rig(u)], seg[u]);
        lazy[u] = off_lazy;
    }

    // consulta em range
    void query_(int u,int tl,int tr,int l, int r){
        if(l > r) return;
        if(tl == l && tr == r) {
            merge(ret,seg[u],ret);
            return;
        }
        push(u, tl, tr);
        int tmid= tl + tr;
        tmid >>= 1;
        query_(lef(u),tl,tmid,l,min(tmid,r));
        query_(rig(u),tmid+1,tr,max(tmid+1,l),r);   
    }
    node query(int l, int r){
        ret = off;
        query_(1,1,n,l,r);
        return ret;
    }

    // update em range
    void update_(int u, int tl, int tr, int l, int r, ll x){
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
        merge(seg[lef(u)], seg[rig(u)], seg[u]);
    }
    void update(int l, int r, ll x){
        update_(1, 1, n, l, r, x);
    }
};
