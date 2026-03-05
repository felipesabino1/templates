// Armazena funções slope-trickables, que sao funcoes que seguem as regras:
// Sao continuas, podem ser divididas em diversas secoes tal que todas as lineares com slopes inteiros e
// sao concavas/convexas
struct SlopeTrick{
    struct func{
        ll a,b;
        func(ll aa = 0, ll bb = 0) : a(aa), b(bb){}
        friend ostream& operator<<(ostream& out, func f){return out << f.a << "x " << (f.b < 0 ? '-' : '+') << abs(f.b);}
        void operator+=(func ot){a += ot.a, b += ot.b;}
    };
    priority_queue<pair<ll,ll>> pts; // slope change (pos,qtd)
    func f; // right linear func

    void add(ll X){
        pts.emplace(X,2);
        f += func(1,-X);
    }
    ll bst(){
        return f.b;
    }
};
