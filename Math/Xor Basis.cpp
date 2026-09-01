// Add(TAM), Has(TAM)
template<class T = ll>
struct Basis{
    vector<T> b;
    int tam;
    Basis(int tamm) : b(tamm,0), tam(tamm){}
    void add(T x){
        for(int i=tam-1; i>=0; i--) if(get_bit(x,i)){
            if(!b[i]) return void(b[i] = x);
            x ^= b[i];
            // as vezes vc vai ter uma outra condicao ao inves de so x^=basis[i]
            // if(time[i] > tx) swap(time[i],tx), swap(b[i],x)
            // x ^= b[i]
        }
    }
    bool has(TT x){
        for(int i=tam-1; i>=0; i--) if(get_bit(x,i)){
            if(!b[i]) return false;
            x ^= b[i];
        }
        return true;
    }
};
