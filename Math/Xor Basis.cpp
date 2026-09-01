// Add(TAM), Has(TAM)
template<class TT = ll>
struct Basis{
    vector<TT> basis;
    int tam;
    Basis(int tamm) : basis(tamm,0), tam(tamm){}
    void add(TT x){
        for(int i=tam-1; i>=0; i--) if(get_bit(x,i)){
            if(!basis[i]) return void(basis[i] = x);
            else x ^= basis[i];
            // as vezes vc vai ter uma outra condicao ao inves desse else
            // if(time[i] > tx) swap(time[i],tx), swap(x,basis[i])
            // else x ^= basis[i]
        }
    }
    bool has(TT x){
        for(int i=tam-1; i>=0; i--) if(get_bit(x,i)){
            if(!basis[i]) return false;
            else x ^= basis[i];
        }
        return true;
    }
};
