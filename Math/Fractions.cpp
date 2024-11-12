template <class TT = ll>
struct frac{
    TT num,den; // o valor negativo da fracao fica so no numerador
 
    frac (TT num,TT den){
        TT g = __gcd(num,den);
        num/=g;
        den/=g;
        if((num < 0 && den < 0) || (num > 0 && den > 0)){
            num=abs(num);
            den=abs(den);
        }else if(num > 0){
            num*=-1;
            den*=-1;
        }
        this->num=num;
        this->den=den;
    }
 
    bool const operator <(const frac & o)const{
        if((den < 0 && o.den < 0) || (den > 0 && o.den > 0)) return num*o.den < o.num*den;
        return num*o.den > o.num*den; 
    }
 
    bool operator !=(const frac &o){
        return num != o.num || den != o.den;
    }
};
