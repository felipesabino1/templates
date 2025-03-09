/*
    Indexado em 1, n esqueca de especificar se a BIT for de sufixo

    Alteracoes:
    
    Adicionar o valor do off (valor dummy)
    Atualizar a funcao da BIT f
*/
template <class TT = ll>
struct Fen{
    vector<TT> fen;
    int n; // tamanho da BIT
    int pref; // flag que indica se a Fenwick eh no prefixo(1), ou no sufixo(0)
    const TT off_fen = ; // valor dummy

    Fen(int n_, int pref_=1) : pref(pref_),n(n_){
        fen.resize(n+10,off_fen);
    }
    ~Fen(){fen.clear();}

    // operacao da BIT
    TT f(TT x, TT y){
        return 
    }

    void update(int x, TT v){
        if(x <= 0 || x > n) return;
        if(pref){
            while(x <= n){
                fen[x]=f(fen[x],v);
                x+=(x&-x);
            }
        }else{
            while(x){
                fen[x]=f(fen[x],v);
                x-=(x&-x);
            }
        }
    }

    TT query(int x){
        if(x <= 0 || x > n) return off_fen;
        TT ans = off_fen;
        if(pref){
            while(x){
                ans=f(ans,fen[x]);
                x-=(x&-x);
            }
        }else{
            while(x <= n){
                ans=f(ans,fen[x]);
                x+=(x&-x);
            }
        }
        return ans;
    }
    // TT query(int l, int r){
    //     return query(r) OPERACAO query(l);
    // }
};
