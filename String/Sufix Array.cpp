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
