/*
    Estrutura para tratar os numeros como sua fatorizacao.
*/
template<class TT = ll> 
struct Factors{
    map<int,int> p; // pra cada primo guarda a qtd de vezes que ele aparece

    // sqrt(x)
    Factors(TT x){
        for(TT i=2; i*i <= x; i++){
            if(x%i == 0){
                int qtd = 0;
                while(x%i == 0){
                    qtd++;
                    x/=i;
                }
                p[i] = qtd;
            }
        }
        if(x != 1)  p[x] = 1;
    }
    Factors(){}
    ~Factors(){p.clear();}

    // O(qtd_primos(x))
    // pra cada primo faz max(0,p - ot.p)
    void operator /=(TT x){
        Factors ot(x);
        for(auto [v,qt] : ot.p){
            qt = p[v] - qt;
            p[v] = qt;
            if(qt <= 0) p.erase(v);
        }
    }
    void operator /=(Factors & ot){
        for(auto [v,qt] : ot.p){
            qt = p[v] - qt;
            p[v] = qt;
            if(qt <= 0) p.erase(v);
        }
    }

    // O(qtd_primos(x))
    void operator *=(TT x){
        Factors ot(x);
        for(auto [v,qt] : ot.p) p[v] += qt;
    }
    void operator *=(Factors & ot){
        for(auto [v,qt] : ot.p) p[v] += qt;
    }

    // this divide x?
    bool divides(TT x){
        return divides(Factors(x));
    }
    bool divides(Factors & ot){
        // a qtd de primos do outro cara tem que ser maior
        if(ot.p.size() < p.size()) return false;
        for(auto [v,qt] : p){
            // o outro cara tem que ter esse primo com qtd maior ou igual a minha
            if(ot.p.count(v)){
                if(ot.p[v] < qt) return false;
            }else return false;
        }
        return true;
    }

    void show(){
        for(auto [v,qt]: p) cout << v << ' ' << qt << '\n';
        cout << "------------\n";
    }
};

/*
    Estrutura para tratar os numeros como sua fatorizacao, implementacao usando set. Mas na questao que eu testei ela ficou mais lenta: https://codeforces.com/contest/1878/problem/F
*/
template<class TT = ll> 
struct Factors{
    set<pair<int,int>> p; // pra cada primo guarda a qtd de vezes que ele aparece

    // sqrt(x)
    Factors(TT x){
        for(TT i=2; i*i <= x; i++){
            if(x%i == 0){
                int qtd = 0;
                while(x%i == 0){
                    qtd++;
                    x/=i;
                }
                p.insert(make_pair(i,qtd));
            }
        }
        if(x != 1)  p.insert(make_pair(x,1));
    }
    Factors(){}
    ~Factors(){p.clear();}

    // O(qtd_primos(x))
    // pra cada primo faz max(0,p - ot.p)
    void operator /=(TT x){
        Factors ot(x);
        for(auto [v,qt] : ot.p){
            auto it = p.lower_bound(make_pair(v,0));
            if(it != p.end() && it->first == v) qt = it->second - qt, p.erase(it);
            if(qt > 0) p.insert(make_pair(v,qt));
        }
    }
    void operator /=(Factors & ot){
        for(auto [v,qt] : ot.p){
            auto it = p.lower_bound(make_pair(v,0));
            if(it != p.end() && it->first == v) qt = it->second - qt, p.erase(it);
            if(qt > 0) p.insert(make_pair(v,qt));
        }
    }

    // O(qtd_primos(x))
    void operator *=(TT x){
        Factors ot(x);
        for(auto [v,qt] : ot.p) {
            auto it = p.lower_bound(make_pair(v,0));
            if(it != p.end() && it->first == v) qt += it->second,p.erase(it);
            p.insert(make_pair(v,qt));
        }
    }
    void operator *=(Factors & ot){
        for(auto [v,qt] : ot.p) {
            auto it = p.lower_bound(make_pair(v,0));
            if(it != p.end() && it->first == v) qt += it->second,p.erase(it);
            p.insert(make_pair(v,qt));
        }
    }

    // this divide x?
    bool divides(TT x){
        return divides(Factors(x));
    }
    bool divides(Factors & ot){
        // a qtd de primos do outro cara tem que ser maior
        if(ot.p.size() < p.size()) return false;
        for(auto [v,qt] : p){
            auto it = ot.p.lower_bound(make_pair(v,0));
            // o outro cara tem que ter esse primo com qtd maior ou igual a minha
            if(it != ot.p.end() && it->first == v){
                if(it->second < qt) return false;
            }else return false;
        }
        return true;
    }

    void show(){
        for(auto [v,qt]: p) cout << v << ' ' << qt << '\n';
        cout << "------------\n";
    }
};
