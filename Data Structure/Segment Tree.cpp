template <class TT = int>
struct Seg{
    // inicializar so o tamanho da seg, n fazer o build
    Seg(int n) : n(n){
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
    
    // busca binaria pela esquerda a partir do ponto inicial x, pra satisfazer alguma funcao (indice mais a esquerda tal que somatorio <= v por exemplo)
    // retorna indice e os valores dos caras mais perto de x
    pair<int,TT> bb_lef_(int u, int tl, int tr, int x, TT v){
        push(u,tl,tr);
        int tmid = tl + tr;
        tmid >>= 1;
        pair<int,TT> ret = make_pair(n+10, -1); /*Mudar segundo parametro de acordo com a operacao*/
        if(tr <= x){
            // achei um segmento antes de x
            ret.second = v - seg[u].sum; /*Mudar de acordo com os atributos do node*/
            if(ret.second >= 0){
                // esse segmento eh bom, ou seja, da pra ir mais pra esquerda
                ret.first = tl;
                ret.second = seg[u].sum; /*Mudar de acordo com os atributos do node*/
                return ret;
            }
            if(tl == tr) return ret; // nao tem como buscar segmentos menores
            // vou ter que ir pra direita achar um segmento que da
            return bb_lef_(rig(u),tmid+1,tr,x,v);
        }else if(tmid+1 <= x){
            // busca nos caras perto de x
            ret = bb_lef_(rig(u),tmid+1,tr,x,v);
            if(ret.first != tmid+1) return ret; // nao tem como ir mais pra esquerda
            ret.second = v - ret.second; // operacao pra fazer com esse segmento que eu ja achei /*Mudar de acordo com os atributos do node*/
            ret = bb_lef_(lef(u),tl,tmid,x,ret.second);
            return make_pair(min(ret.first,tmid+1), ret.second);
        }else return bb_lef_(lef(u),tl,tmid,x,v); // vou pra esquerda ate achar um segmento que nao tem parte maior que x
    }
    int bb_lef(int x, TT v){
        return bb_lef_(1,1,n,x,v).first;
    }

    // busca binaria pela direta a partir do ponto inicial x, pra satisfazer alguma funcao (indice mais a direita tal que somatorio <= v por exemplo)
    // retorna indice e os valores dos caras mais perto de x
    pair<int,TT> bb_rig_(int u,int tl,int tr,int x, TT v){
        push(u,tl,tr);
        int tmid = tl+tr;
        tmid>>=1;
        pair<int,TT> ret = make_pair(-1,-1);
        if(tl >= x){
            // achei um segmento depois de x
            ret.second = v - seg[u].sum; /*Mudar de acordo com os atributos do node*/
            if(ret.second >= 0){
                // esse segmento eh bom, ou seja, da pra ir mais pra esquerda
                ret.first = tr;
                ret.second = seg[u].sum; /*Mudar de acordo com os atributos do node*/
                return ret;
            }
            if(tl == tr) return ret; // nao tem como buscar segmentos menores
            // vou ter que ir pra esquerda achar um segmento que da
            return bb_rig_(lef(u),tl,tmid,x,v);
        }else if(tmid >= x){
            // busca nos caras perto de x
            ret = bb_rig_(lef(u),tl,tmid,x,v);
            if(ret.first != tmid) return ret; // nao tem como ir mais pra direita
            ret.second = v - ret.second; // operacao pra fazer com esse segmento que eu ja achei /*Mudar de acordo com os atributos do node*/
            ret = bb_rig_(rig(u),tmid+1,tr,x,ret.second);
            return make_pair(max(ret.first,tmid), ret.second);
        }else return bb_rig_(rig(u),tmid+1,tr,x,v); // vou pra direita ate achar um segmento que nao tem parte menor que x
    }
    int bb_lef(int x, TT v){
        return bb_lef_(1,1,n,x,v).first;
    }
};
