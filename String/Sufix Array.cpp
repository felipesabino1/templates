// Computa o Suffix Array indexado de 0
// A primeira posicao do SA eh o end() da string
// O(N * log(N))
vc<int> SA(string s){
    s.push_back(char(1));
    int n = s.size();
    int N = max(n,260);
    vc<int> sa(n),nsa(n),c(n),nc(n),cnt(N);
    for(int i=0; i<n; i++) sa[i] = i, c[i] = s[i];
    for(int k = 0; k < n; k ? k *= 2 : k++) { 
        fill(cnt.begin(),cnt.end(),0);
        for(int i = 0; i < n; i++) nsa[i] = (sa[i]-k+n)%n, cnt[c[i]]++;
        for(int i = 1; i < N; i++) cnt[i] += cnt[i-1];
        for(int i = n-1; i+1; i--) sa[--cnt[c[nsa[i]]]] = nsa[i];

        for(int i = 1, r = 0; i < n; i++) nc[sa[i]] = r += c[sa[i]] !=
            c[sa[i-1]] or c[(sa[i]+k)%n] != c[(sa[i-1]+k)%n];
        swap(c,nc);
        if (c[sa[n-1]] == n-1) break;
    }
    return sa;
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
        tam -= (tam != 0);
    }
    return lcp;
}
