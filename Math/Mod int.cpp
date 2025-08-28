struct mi {
    int v;
    explicit operator int() const { return v; }
    mi() { v = 0; }
    mi(long long _v) : v(_v % mod) { v += (v < 0) * mod; }
    mi operator+(mi b){return v+b.v - (v+b.v >= mod ? mod : 0);}
    mi operator-(mi b){return v-b.v + (v-b.v < 0 ? mod : 0);}
    mi operator*(mi b){return 1ll*v*b.v%mod;}
    friend mi fexp(mi a, ll b){
        mi ans = 1;
        while(b){
            if(b&1) ans = ans * a;
            b >>= 1;
            a = a * a;
        }
        return ans;
    }
    mi inv(mi a){return fexp(a,mod-2);}
    mi operator/(mi b){return a * inv(b);}
    void operator+=(mi b){if((v += b.v) >= mod) v -= mod;}
    void operator-=(mi b){if((v -= b.v) < 0) v += mod;}
    void operator *=(mi b){v = 1ll*v*b.v%mod;}
    void operator /=(mi b){v = v*inv(b);}
    friend ostream& operator<<(ostream& out, mi at){return out << at.v;}
};
