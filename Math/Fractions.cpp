template <class TT = ll>
struct Frac{
    TT num,den; // o valor negativo da fracao fica so no numerador
 
    Frac (TT num_ = 0,TT den_ = 1) : num(num_), den(den_){
        TT g = __gcd(num,den);
        num/=g;
        den/=g;
        fixSig(num,den);
    }
    void fixSig(TT & num_, TT & den_){
        if((num_ < 0 && den_ < 0) || (num_ > 0 && den_ > 0)){
            num_=abs(num_);
            den_=abs(den_);
        }else if(num_ > 0){
            num_*=-1;
            den_*=-1;
        }
    }

    TT fexp(TT a, TT b){
        TT ans = 1;
        while(b){
            if(b&1) ans = ans*a;
            b>>=1;
            a = a*a;
        }
        return ans;
    }

    TT fexp(TT a, TT b, TT mod){
        TT ans = 1;
        while(b){
            if(b&1) ans = ans*a%mod;
            b>>=1;
            a = a*a%mod;
        }
        return ans; 
    }

    friend ostream &operator<<(ostream & os, const Frac & o){
        os << o.num << "/" << o.den;
        return os;
    }
 
    bool operator <(const Frac & o)const{
        if((den < 0 && o.den < 0) || (den > 0 && o.den > 0)) return num*o.den < o.num*den;
        return num*o.den > o.num*den; 
    }
 
    bool operator ==(const Frac &o){
        return num == o.num && den == o.den;
    }
    
    bool operator !=(const Frac &o){
        return num != o.num || den != o.den;
    }

    friend Frac operator -(const Frac & at){
        return Frac(-at.num,at.den);
    }

    void operator *=(const Frac & o){
        TT g1 = __gcd(num,o.den);
        TT g2 = __gcd(den,o.num);
        num = (num/g1)*(o.num/g2);
        den = (den/g2)*(o.den/g1);
        fixSig(num,den);
    }
    void operator /=(const Frac & o){
        TT g1 = __gcd(num,o.num);
        TT g2 = __gcd(den,o.den);
        num = (num/g1)*(o.den/g2);
        den = (den/g2)*(o.num/g1);
        fixSig(num,den);
    }
    void operator +=(const Frac & o){
        TT lcm = den/__gcd(den,o.den)*o.den;
        num = (lcm/den*num) + (lcm/o.den*o.num);
        den = lcm;
        TT g = __gcd(num,den);
        num /= g, den /= g;
        fixSig(num,den);
    }
    void operator -=(const Frac & o){
        TT lcm = den/__gcd(den,o.den)*o.den;
        num = (lcm/den*num) + (lcm/o.den*o.num);
        den = lcm;
        TT g = __gcd(num,den);
        num /= g, den /= g;
        fixSig(num,den);
    }

    Frac operator *(const Frac & o){
        TT g1 = __gcd(num,o.den);
        TT g2 = __gcd(den,o.num);
        return Frac((num/g1)*(o.num/g2), (den/g2)*(o.den/g1));
    }
    Frac operator /(const Frac & o){
        TT g1 = __gcd(num,o.num);
        TT g2 = __gcd(den,o.den);
        return Frac((num/g1)*(o.den/g2), (den/g2)*(o.num/g1));
    }
    Frac operator +(const Frac & o){
        TT lcm = den/__gcd(den,o.den)*o.den;
        return Frac((lcm/den*num) +(lcm/o.den*o.num),lcm);
    }
    Frac operator -(const Frac & o){
        TT lcm = den/__gcd(den,o.den)*o.den;
        return Frac((lcm/den*num) -(lcm/o.den*o.num),lcm);
    }

    // exponenciacao
    void operator ^=(TT x){
        if(num == 0) return;
        if(x < 0){
            swap(num,den);
            x*=-1;
        }
        TT aux = 1;
        num = fexp(num,x);
        den = fexp(den,x);
    }

    TT modular(TT mod){
        return num*fexp(den,mod-2,mod)%mod;
    }
};
