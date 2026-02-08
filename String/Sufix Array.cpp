// Computa o Suffix Array
// O(N * log(N))
vc<int> SA(string s){
    s.push_back('$'); int n = s.size();
    auto prox = [&](int id, int k) -> int {
        return (k == -1 ? id : (id + (1<<k)) % n);
    };
    vc<int> c(n),nc(n),ord(n),nord(n);
    vc<int> cnt(max(256,n),0);
    for(int i=0; i<n; i++) ord[i] = i;
    for(int i=0; i<n; i++) c[i] = s[i];
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
/*
    Given the suffix array, calculates the LCP from sufix array.
    O(n).
*/
vector<int> LCP(string & s, vector<int> &sa){
    string str = s + '$';
    int n = str.size();
    vector<int> pos(n);
    vector<int> lcp(n,0);
    for(int i=0; i<n; i++) pos[sa[i]] = i;
    int tam = 0;
    // tam so aumenta ate n, e diminui de 1 em 1, entao O(n)
    for(int i=0; i<n-1; i++){
        int id = pos[i];
        while(i + tam < n && sa[id-1] + tam < n && str[i+tam] == str[sa[id-1] + tam]) tam++;
        lcp[id-1] = tam;
        if(tam) tam--;
    }
    return lcp;
}
