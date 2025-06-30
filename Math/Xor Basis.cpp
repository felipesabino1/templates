template<class TT = ll>
struct Basis{
    vector<TT> basis;
    int tam;
    Basis(int tam_) : basis(tam_,0), tam(tam_){}
    void add(TT x){
        for(int i=tam-1; i>=0; i--){
            if(!get_bit(x,i)) continue;
            if(basis[i]) x ^= basis[i];
            else{
                basis[i] = x;
                return;
            }
        }
    }
    bool has(TT x){
        for(int i=tam-1; i>=0; i--){
            if(!get_bit(x,i)) continue;
            if(!basis[i]) return false;
            x ^= basis[i];
        }
        return true;
    }
};
