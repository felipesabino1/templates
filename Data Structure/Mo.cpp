/*
    Indexado de 1 (os l e r)

    Alteracoes:

    Ver como calcula a query
    Ler as queries
    Ver como imprime a resposta
    Ver as funcoes de add e rmv do mo
*/
typedef int TT;
struct Mo{
    const int K = 450;

    struct query{
        int idx,l,r;

        bool operator <(const query &o){
            if(l/K == o.l/K){
                if((l/K)&1) return r>o.r;
                return r<o.r;
            }
            return l/K < o.l/K;
        }
    };

	vector<query> q;
	vector<TT> ans;

    // qtd de queries
	Mo(int q){
        this->q.resize(q);
    }


    // adiciona na posicao x
	void add(int x){
        
    }

    // remove na posicao x
	void rmv(int x){

    }

    // calcula a resposta pra query
	TT calc(){

    }

	void solve(){
		sort(q.begin(),q.end());
		ans.resize(q.size());
		int i,j;
		i=1;
		j=0;
        for(auto [idx,l,r] : q){
			while(j < r){
				add(++j);
			}
			while(i > l){
				add(--i);
			}

			while(j > r){
				rmv(j--);
			}
			while(i < l){
				rmv(i++);
			}

			ans[idx]=calc();
		}
	}

    // ler as queries
    void ler(){
        for(int i=0; i<q.size(); i++) {
            cin >> q[i].l >> q[i].r;
            q[i].idx=i;
        }
    }

	void show(){
        // imprime a resposta
	}
};
