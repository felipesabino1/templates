// a^x === b (mod m)
ll lgd(ll a, ll b, ll m){
    a%=m;
    b%=m;
    if(a == 0 && b != 0) return -1;
    ll k=1,add=0,g;
    while((g = __gcd(a,m)) > 1LL){
        if(b == k) return add;
        if(b%g) return -1;
        b/=g;
        m/=g;
        add++;
        k = k*(a/g)%m;
    }
    ll n = sqrt(m)+1;
    
    ll fat=1;
    for(int i=0; i<n; i++) fat=fat*a%m;
    
    vector<pair<ll,ll>> big;
    ll aux=1;
    for(int i=0; i<n+10; i++){
        aux=aux*fat%m;
        big.push_back({aux*k%m,i+1});
    }
    // os caras que sao k*a^(p*n)
    sort(big.begin(),big.end(),[&](pair<ll,ll> x, pair<ll,ll> y){
        return x.first < y.first;
    });

    aux=1;
    vector<pair<ll,ll>> small;
    for(int i=0; i<=n; i++){
        small.push_back({b*aux%m,i});
        aux=aux*a%m;
    }
    // os caras que sao b*a^q
    sort(small.begin(),small.end(), [&] (pair<ll,ll> x, pair<ll,ll> y){
        return x.first < y.first;
    });

    // se ele quiser que a resposta tenha alguma propriedade
    ll ans=-1;
    int i=0,j=0;
    while(i < big.size() && j < small.size()){
        if(big[i].first == small[j].first) {
            if(ans == -1) ans=big[i].second*n-small[j].second+add;
            else ans=big[i].second*n-small[j].second+add;  
            i++,j++;
        }else if(big[i].first < small[j].first) i++;
        else j++;
    }
    return ans;
}
