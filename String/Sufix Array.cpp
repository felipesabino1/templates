/*
    O(n * log(n))
*/
vector<int> SA(const string & s){
    string str = s + '$';
    int n = str.size();
    vector<int> ord(n),c(n);
    vector<int> nord(n),nc(n);
    vector<int> cnt(max(256,n),0);
    // ordena pela primeira metade
    auto radix = [&](int k) -> void{
        for(int i=0; i<n; i++) cnt[c[i]]++;
        for(int i=1; i<cnt.size(); i++) cnt[i] += cnt[i-1];
        for(int i=n-1; i>=0; i--) nord[--cnt[c[ord[i]]]] = ord[i];
        fill(cnt.begin(),cnt.end(),0);

        nc[nord[0]] = 0;
        for(int i=1; i<n; i++){
            int esq = c[nord[i]], dir = (k == -1 ? c[nord[i]] : c[(nord[i] + (1<<k)) % n]);
            int ote = c[nord[i-1]], otd = (k == -1 ? c[nord[i-1]] : c[(nord[i-1] + (1<<k)) % n]);
            nc[nord[i]] = nc[nord[i-1]] + (esq == ote && dir == otd ? 0 : 1);
        }
        swap(c,nc), swap(ord,nord);
    };
    for(int i=0; i<n; i++) ord[i] = i;
    for(int i=0; i<n; i++) c[i] = str[i];
    radix(-1);

    // na transicao, os caras ja estao ordenados pela segunda metade, ai transito todos os caras pra primeira metade
    for(int k=0; (1<<k) < n; k++){
        for(int i=0; i<n; i++) ord[i] = (ord[i] - (1<<k) + n)%n;
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
