template <class TT = ll>
struct frac{
    TT num,den; // o valor negativo da fracao fica so no numerador
 
    frac(TT num_ = 0,TT den_ = 1) : num(num_), den(den_){
        TT g = __gcd(abs(num),abs(den));
        num/=g; den/=g;
        if((num^den) < 0) num = -abs(num);
        den = abs(den);
    }
    friend ostream &operator<<(ostream & os, const frac o){
        os << o.num << "/" << o.den;
        return os;
    }
 
    explicit operator int() const{return num/den;}
    bool operator<(const frac& ot)const{return 1ll*num*ot.den <1ll* ot.num*den;}
    bool operator==(const frac& ot)const{return num == ot.num && den == ot.den;}
    
    frac operator-(){return frac(-num,den);}
    friend frac inv(frac f){return frac(f.den,f.num);}
    
    friend frac& operator+=(frac& a, frac b){
        TT d = a.den/__gcd(a.den,b.den)*b.den;
        a.num = d/a.den*a.num + d/b.den*b.num;
        return a;
    }
    friend frac& operator-=(frac& a, frac b){
        return a += -b;
    }
    friend frac& operator*=(frac& a, frac b){
        TT d = __gcd(a.num,b.den); a.num /= d; b.den /= d;
        d = __gcd(a.den,b.num); a.den /= d; b.num /= d;
        return a;
    }
    friend frac& operator/=(frac& a, frac b){
        return a *= inv(b);
    }

    friend frac operator+(frac a, frac b){return a += b;}
    friend frac operator-(frac a, frac b){return a -= b;}
    friend frac operator*(frac a, frac b){return a *= b;}
    friend frac operator/(frac a, frac b){return a /= b;}
};
