// Armazena funções slope-trickables, que sao funcoes que seguem as regras:
// Sao continuas, podem ser divididas em diversas secoes tal que todas as lineares com slopes inteiros e
// sao concavas/convexas
  struct SlopeTrick{
    struct func{
        ll a,b;
        func(ll aa = 0, ll bb = 0) : a(aa), b(bb){}
        friend ostream& operator<<(ostream& out, func f){return out << f.a << "x " << (f.b < 0 ? '-' : '+') << abs(f.b);}
    };
    multiset<pair<ll,ll>> pts; // slope change (pos,qtd)
    func f; // left,right,mid linear func

    void add(ll x, ll qt){pts.emplace(x,qt);}
    void show(){
        auto st = pts;
        auto mf = f;
        while(!st.empty()){
            auto [x,qt] = *st.begin(); st.erase(st.begin());
            cout << mf << el;
            cout << "x: " << x << el;
            ll y = func.a*x + func.b;
            func.a -= qt;
            func.b = y - func.a*x;
        }
        cout << mf << el;
        cout << "x: inf" << el;            
    }
    ll bst(){
        return f.b;
    }
};
