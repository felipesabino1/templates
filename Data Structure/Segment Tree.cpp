/*
    Alteracoes:
    
    Adicionar o que tem no node e na lazy da seg.
    Ver se os tipos das coisas ta certo (vetor inicial da seg e parametros do update)
*/
typedef int T;
struct Seg{
    // inicializar a estrura, fazer o a indexado de 1
    Seg(vector<T> &a,int n){
        seg.resize(n<<2);
        lazy.resize(n<<2);
        vec=a;
        this->n=n;
        build(1,1,n);
    }
    
    // o que vai ter dentro do no de cada seg
    struct node{

    };
    // o que vai ter dentro do no de cada lazy
    struct sono{

        bool operator ==(const sono &o){
            return 
        }
    };

    vector<T> vec;
    int n;
    // no nulo
    const node off = {};
    // lazy nula
    const sono off_lazy = {}; 
    vector<node> seg;
    vector<sono> lazy;
    // operacao de unir dois nos
    node merge(node x, node y){

    }

    // coisar a lazy pra baixo
    void push(int u,int tl,int tr){
        if(tl == tr || lazy[u] == off_lazy) return;
        // atualizar os filhos

        // atualizar as lazies dos filhos

        lazy[u]=off_lazy;
    }

    // inicializar a seg
    void build(int u,int tl,int tr){
        if(tl == tr){
            // inicializar os caras bases
            seg[u]=
            lazy[u]=off_lazy;
            return;
        }
        int tmid=tl+tr;
        tmid>>=1;
        build(lef(u),tl,tmid);
        build(rig(u),tmid+1,tr);
        seg[u]=merge(seg[lef(u)],seg[rig(u)]);
        lazy[u]=off_lazy;
    }

    // consulta em range
    node query_(int u,int tl,int tr,int l, int r){
        if(l > r) return off;
        if(tl == l && tr == r) return seg[u];
        push(u,tl,tr);
        int tmid=tl+tr;
        tmid>>=1;
        return merge(query_(lef(u),tl,tmid,l,min(tmid,r)),query_(rig(u),tmid+1,tr,max(tmid+1,l),r));
    }
    node query(int l,int r){
        return query_(1,1,n,l,r);
    }

    // update em range
    void update_(int u,int tl,int tr,int l,int r,T x){
        if(l > r) return;
        if(tl == l && tr == r){
            // atualizar a seg e o lazy
            seg[u]=
            lazy[u]=
            return;
        }
        push(u,tl,tr);
        int tmid=tl+tr;
        tmid>>=1;
        update_(lef(u),tl,tmid,l,min(tmid,r),x);
        update_(rig(u),tmid+1,tr,max(tmid+1,l),r,x);
        seg[u]=merge(seg[lef(u)],seg[rig(u)]);
    }
    void update(int l,int r, T x){
        update_(1,1,n,l,r,x);
    }
};
