/*
    Alteracoes:

    Ver como calcula a query
    Ler as queries
    Ver como imprime a resposta
    Ver as funcoes de add e rmv do mo
*/
typedef int T
struct Mo{
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
	vector<T> ans;

	MO(int q){
        this->q=q;
    }

    // ler as queries
    void ler(){
        
    }

	void add(int x){
		
	}

	void rmv(int x){
		
	}

    // calcula a resposta pra query
	T calc(){

    }

	void solve(){
		sort(q.begin(),q.end());
		ans.resize(q.size());
		int i,j;
		i=1;
		j=0;
		for(auto [idx,l,r] : q){
			while(j < r){
				add(++j,1);
			}
			while(i > l){
				add(--i,0);
			}

			while(j > r){
				rmv(j--,1);
			}
			while(i < l){
				rmv(i++,0);
			}

			ans[idx]=calc();
		}
	}

	void show(){
        // imprime a resposta
		for(auto v: ans) cout << v << '\n';
	}
};
