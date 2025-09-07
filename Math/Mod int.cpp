const ll mod = 998244353;
struct mi {
    int v;
    explicit operator int() const { return v; }
    mi() { v = 0; }
    mi(long long _v) : v(_v % mod) { v += (v < 0) * mod; }
    friend mi& operator+=(mi& a,mi b){if((a.v += b.v) >= mod) a.v -= mod; return a;}
    friend mi& operator-=(mi& a,mi b){if((a.v -= b.v) < 0) a.v += mod; return a;}
    friend mi& operator*=(mi& a,mi b){a.v = 1ll*a.v*b.v%mod; return a;}
    friend mi& operator/=(mi& a,mi b){a = a*inv(b); return a;}
    friend mi operator+(mi a,mi b){return a += b;}
    friend mi operator-(mi a,mi b){return a -= b;}
    friend mi operator*(mi a,mi b){return a *= b;}
    friend mi operator/(mi a,mi b){return a /= b;}
    friend mi fexp(mi a, ll b){
        mi ans = 1;
        while(b){
            if(b&1) ans = ans * a;
            b >>= 1;
            a = a * a;
        }
        return ans;
    }
    friend mi inv(mi a){return fexp(a,mod-2);}
    friend ostream& operator<<(ostream& out, mi at){return out << at.v;}
    friend istream& operator>>(istream& in, mi &at){ll x; in >> x; at = x; return in;}
};
