/*
    Template pra fazer conta no mundo modular

    Alteracoes:
    1. Mudar o off(termo que indica erro em conta - equacao sem solucao por exemplo).
*/
template <class TT = ll>
struct MD{
    const TT off = -1;

    TT gcd(TT a, TT b){
        if(a < 0) a*=-1;
        if(b < 0) b*=-1;
        if(a > b) swap(a,b);
        TT aux;
        while(a != 0){
            aux = b%a;
            b = a;
            a = aux;
        }
        return b;
    }
    // acha os coeficientes de a*x + b*y = gcd(a,b)
    pair<TT,TT> extended_euclides(TT a, TT b){
        bool trocou = 0, nega = 0, negb = 0;
        if(a < 0) nega=1,a*=-1;
        if(b < 0) negb=1,b*=-1;
        if(a > b) swap(a,b),trocou = 1;
        vector<pair<TT,TT>> st;
        TT aux,g;
        TT s,t;
        while(a != 0){
            st.push_back(make_pair(a,b));
            aux = b%a;
            b = a;
            a = aux;
        }
        g = b;
        s = 0;
        t = 1;
        while(!st.empty()){
            a = st.back().first, b = st.back().second;
            t = s;
            s = (g-t*b)/a;
            st.pop_back();  
        }
        if(nega) t*=-1,s*=-1;
        if(trocou) return make_pair(t,s);
        else return make_pair(s,t);
    }

    // calcula o inverso de a modulo m
    TT inv(TT a, TT m){
        a%=m;
        if(a < 0) a = m+a;
        if(gcd(a,m) != 1) return off; // nao existe inverso modular
        pair<TT,TT> coef = extended_euclides(a,m);
        return coef.first%m;
    }

    // resolve equacoes do tipo a*x = b (mod m)
    TT linear(TT a, TT b, TT m){
        a%=m;
        if(a < 0) a = m+a;
        b%=m;
        if(b < 0) b = m+b;
        TT g;
        while((g = gcd(a,m)) != 1){
            if(b%g != 0) return off; // nao eh uma relacao possivel
            a/=g, b/=g, m/=g;
        }
        a%=m;
        b%=m;
        pair<TT,TT> coef = extended_euclides(a,m);
        b = b*(coef.first%m)%m;
        return b;
    }
    // resolve equacoes do tipo a^x = b (mod m)
    TT lgd(TT a, TT b, TT m){
        a%=m;
        if(a < 0) a = m-a;
        b%=m;
        if(b < 0) b = m-b;
        if(a == 0 && b != 0) return -1;
        TT k=1,add=0,g;
        while((g = gcd(a,m)) > 1){
            if(b == k) return add;
            if(b%g) return -1;
            b/=g;
            m/=g;
            add++;
            k = k*(a/g)%m;
        }
        TT n = sqrt(m)+1;
        
        TT fat=1;
        for(int i=0; i<n; i++) fat=fat*a%m;
        
        vector<pair<TT,TT>> big;
        TT aux=1;
        for(int i=0; i<n+10; i++){
            aux=aux*fat%m;
            big.push_back({aux*k%m,i+1});
        }
        // os caras que sao k*a^(p*n)
        sort(big.begin(),big.end(),[&](pair<TT,TT> x, pair<TT,TT> y){
            return x.first < y.first;
        });

        aux=1;
        vector<pair<TT,TT>> small;
        for(int i=0; i<=n; i++){
            small.push_back({b*aux%m,i});
            aux=aux*a%m;
        }
        // os caras que sao b*a^q
        sort(small.begin(),small.end(), [&] (pair<TT,TT> x, pair<TT,TT> y){
            return x.first < y.first;
        });

        // se ele quiser que a resposta tenha alguma propriedade
        TT ans=-1;
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
};
