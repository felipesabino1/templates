template <class TT = ll>
struct frac{
    TT num,den; // o valor negativo da fracao fica so no numerador
    frac(TT numm = 0,TT denn = 1) : num(numm), den(denn){
        TT g = __gcd(abs(num),abs(den));
        num/=g, den/=g; 
        num = ((num^den) < 0 ? -1 : 1) * abs(num); den = abs(den);
    }
    friend ostream &operator<<(ostream & out, const frac at){
        return out << at.num << '/' << at.den;
    }
    explicit operator int()const{return num/den;}
    explicit operator double()const{return double(num)/den;}
    bool operator<(const frac& ot)const{return 1ll*num*ot.den < 1ll*ot.num*den;}
    bool operator>(const frac& ot)const{return 1ll*num*ot.den > 1ll*ot.num*den;}
    bool operator<=(const frac &ot)const{return 1ll*num*ot.den <= 1ll*ot.num*den;}
    bool operator>=(const frac &ot)const{return 1ll*num*ot.den >= 1ll*ot.num*den;}
    bool operator==(const frac& ot)const{return num == ot.num && den == ot.den;}

    frac operator-(){return frac(-num,den);}
    friend frac inv(frac f){return frac(f.den,f.num);}    
    friend frac& operator+=(frac& a, frac b){
        TT d = a.den/__gcd(a.den,b.den)*b.den;
        a.num *= d/a.den, b.num *= d/b.den;
        a.num += b.num, a.den = d;
        return a;
    }
    friend frac& operator-=(frac& a, frac b){
        return a += -b;
    }
    friend frac& operator*=(frac& a, frac b){
        TT d = __gcd(a.num,b.den); a.num /= d, b.den /= d;
        d = __gcd(a.den,b.num); a.den /= d, b.num /= d;
        a.num *= b.num, a.den *= b.den;
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
