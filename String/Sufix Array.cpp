// Computa o Suffix Array indexado de 0
// A primeira posicao do SA eh o end() da string
// O(N * log(N))
vc<int> SA(string s){
    s.push_back('$'); int n = s.size();
    auto prox = [&](int id, int k) -> int {
        return (k == -1 ? id : (id + (1<<k)) % n);
    };
    vc<int> c(n),nc(n),ord(n),nord(n);
    vc<int> cnt(max(256,n),0); // tamanho do alfabeto
    for(int i=0; i<n; i++) c[i] = s[i], ord[i] = i;
    // ordena pela primeira metade
    auto radix = [&](int k) -> void {
        for(int i=0; i<n; i++) cnt[c[i]]++;
        for(int i=1; i<cnt.size(); i++) cnt[i] += cnt[i-1];
        for(int i=n-1; i>=0; i--) nord[--cnt[c[ord[i]]]] = ord[i];
        fill(cnt.begin(),cnt.end(),0);
        nc[nord[0]] = 0;
        for(int i=1; i<n; i++)
            nc[nord[i]] = nc[nord[i-1]] + (c[nord[i]] != c[nord[i-1]] || c[prox(nord[i],k)] != c[prox(nord[i-1],k)]);
        swap(c,nc),swap(ord,nord);
    };
    radix(-1);
    for(int k=0; (1<<k)<n; k++){
        // ordena os caras pela segunda metade
        for(int i=0; i<n; i++) ord[i] = (ord[i] - (1<<k) + n) % n;
        radix(k);
    }
    return ord;
}
// Calcula o LCP entre os sufixos ordenados
// O(N)
vc<int> LCP(string& s, vc<int>& sa){    
    int n = s.size();
    vc<int> lcp(n),pos(n+1);
    for(int i=0; i<=n; i++) pos[sa[i]] = i;
    for(int tam=0,at=0,ot; at<=n; at++){
        if(pos[at] == n){
            tam = 0;
            continue;
        }
        ot = sa[pos[at]+1];
        while(at+tam<n && ot+tam<n && s[at+tam] == s[ot+tam]) tam++;
        lcp[pos[at]] = tam;
        if(tam) tam--;
    }
    return lcp;
}
// Struct do Suffix array, query de LCP entre sufixos
struct SA{
    struct RMQ{
        vc<int> v;
        int n; static const int b = 30;
        vc<int> mask, t;
        
        int op(int x,int y){return v[x] <= v[y] ? x : y;}
        int msb(int x){return 31-__builtin_clz(x);}
        int small(int r, int sz = b){return r-msb(mask[r]&((1<<sz)-1));}
        void init(const vc<int>& vv){
            v = vv, n = vv.size(); mask.resize(n), t.resize(n);
            for (int i = 0, at = 0; i < n; mask[i++] = at |= 1) {
                at = (at<<1)&((1<<b)-1);
                while (at && op(i-msb(at&-at), i) == i) at ^= at&-at;
            }
            for (int i = 0; i < n/b; i++) t[i] = small(b*i+b-1);
            for (int j = 1; (1<<j) <= n/b; j++) for (int i = 0; i+(1<<j) <= n/b; i++)
                t[n/b*j+i] = op(t[n/b*(j-1)+i], t[n/b*(j-1)+i+(1<<(j-1))]);
        }
        int index_query(int l, int r) {
            if (r-l+1 <= b) return small(r, r-l+1);
            int x = l/b+1, y = r/b-1;
            if (x > y) return op(small(l+b-1), small(r));
            int j = msb(y-x+1);
            int ans = op(small(l+b-1), op(t[n/b*j+x], t[n/b*j+y-(1<<j)+1]));
            return op(ans, small(r));
        }
        int query(int l, int r) {return v[index_query(l, r)]; }
    };
    string s; int n;
    vc<int> sa,pos,lcp;
    RMQ rmq;
    SA(string& ss) : s(ss), n(ss.size()), sa(n+1),pos(n+1),lcp(n){
        SFA(); LCP();
        rmq.init(lcp);
    }
    void SFA(){
        s.push_back(char(1)), n++;
        #define prox(id,k) (k == -1 ? id : (id + (1<<k)) % n)
        vc<int> c(n),nc(n),ord(n),nord(n);
        vc<int> cnt(max(256,n),0); // tamanho do alfabeto
        for(int i=0; i<n; i++) c[i] = s[i], ord[i] = i;
        auto radix = [&](int k) -> void {
            for(int i=0; i<n; i++) cnt[c[i]]++;
            for(int i=1; i<cnt.size(); i++) cnt[i] += cnt[i-1];
            for(int i=n-1; i>=0; i--) nord[--cnt[c[ord[i]]]] = ord[i];
            fill(cnt.begin(),cnt.end(),0);
            nc[nord[0]] = 0;
            for(int i=1; i<n; i++)
                nc[nord[i]] = nc[nord[i-1]] + (c[nord[i]] != c[nord[i-1]] || c[prox(nord[i],k)] != c[prox(nord[i-1],k)]);
            swap(c,nc),swap(ord,nord);
        };
        radix(-1);
        for(int k=0; (1<<k)<n; k++){
            for(int i=0; i<n; i++) ord[i] = (ord[i] - (1<<k) + n) % n;
            radix(k);
        }
        sa = ord;
        #undef prox
        s.pop_back(), n--;
    }
    void LCP(){
        for(int i=0; i<=n; i++) pos[sa[i]] = i;
        for(int tam=0,at=0,ot; at<=n; at++){
            if(pos[at] == n){
                tam = 0;
                continue;
            }
            ot = sa[pos[at]+1];
            while(at+tam<n && ot+tam<n && s[at+tam] == s[ot+tam]) tam++;
            lcp[pos[at]] = tam;
            if(tam) tam--;
        }
    }
    // LCP dos sufixos [i...n-1],[j...n-1] em O(1)
    int get_lcp(int i,int j){  
        if(min(i,j) < 0 || max(i,j) >= n) return 0;  
        if(pos[i] > pos[j]) swap(i,j);
        return (i == j ? n-i : rmq.query(pos[i],pos[j]-1));
    }
};
