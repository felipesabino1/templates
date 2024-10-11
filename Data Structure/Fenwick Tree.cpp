/*
    Indexado em 1, n esqueca de especificar se a BIT for de sufixo

    Alteracoes:
    
    Adicionar o valor do off (valor dummy)
    Mudar o tipo das coisas, setar o TT
    Ver como que faz o update da BIT na inicializacao
    Atualizar a funcao da BIT f
*/
typedef ll TT;
struct Fen{
    vector<TT> fen;
    int n; // tamanho da BIT
    int pref; // flag que indica se a Fenwick eh no prefixo(1), ou no sufixo(0)
    const TT off_fen = ; // valor dummy

    Fen(int n, int pref=1){
        fen.resize(n+10);
        this->pref = pref;
        this->n = n;
    }
    Fen(vector<TT> &a, int n, int pref=1){
        fen.resize(n+10);
        this->pref = pref;
        this->n = n;
        // fazer o update com base na operacao da bit
        for(int i=1; i<=n; i++) update();
    }

    // operacao da BIT
    TT f(TT x, TT y){
        return 
    }

    void update(int x, TT v){
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
};
