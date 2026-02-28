// Indexado de 1
// K = N/sqrt(Q)
// alterar o add,rmv,calc,read,show
// O(N*K*T) tal que T eh a complexidade do add e rmv
template <class TT = int>
struct Mo{
    const int K = 450;
    struct query{
        int id,l,r;
        bool operator <(const query &ot)const{
            return (l/K == ot.l/K ? (l/K%2 ? r<ot.r : r>ot.r) : l/K < ot.l/K);
        }
    };

    vc<query> q; vc<TT> ans;
    Mo(int nn) : q(nn),ans(nn){}

    // add in x
	void add(int x){
    }
    // rmv in x
	void rmv(int x){
    }
	TT calc(){
    }

	void solve(){
		sort(q.begin(),q.end());
		int i = 1,j = 0;
        for(auto [idx,l,r] : q){
            while(j < r) add(++j);
            while(i > l) add(--i);
            while(j > r) rmv(j--);
            while(i < l) rmv(i++);
            ans[idx] = calc();
		}
	}

    void read(){
        for(int i=0; i<q.size(); i++) {
            cin >> q[i].l >> q[i].r;
            q[i].idx=i;
        }
    }
    void show(){
        // imprime a resposta
    }
};
