// Indexado de 0
// Funciona para operacoes associativas com inverso
// Init(N), Update(1), Query(sqrt(N))
struct node{

	void off(){} // coloca o valor nulo nesse cara
	friend node& operator+=(node& a, node b){
		
	}
	friend node& operator-=(node& a, node b){
		
	}
};
template<class node>
struct Sqrt{
	vc<node> tab,bl; int K;
	Sqrt(vc<node>& v, int sqrtn) : tab(tab), bl(v.size()), K(sqrtn){
		for(int i=0; i<v.size(); i++) bl[i].off();
		for(int i=0; i<v.size(); i++) bl[i/K] += tab[i];
	}
	void update(int x, node v){
		bl[x/K] -= tab[x];
		tab[x] = v;
		bl[x/K] += tab[x];
	}
	// [l,r] inclusivo
	node query(int l, int r){
		node ret; ret.off();
		if(l > r) return ret;
		else if(l/K == r/K) for(int i=l; i<=r; i++) ret += tab[i];
		else{
			int tl = l/K, tr = r/K;
			for(int i=l; i<K*(tl+1); i++) ret += tab[i];
			for(int i=tl+1; i<tr; i++) ret += bl[i];
			for(int i=K*tr; i<=r; i++) ret += tab[i];
		}
		return ret;
	}
};
