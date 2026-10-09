// Li-Chao Tree
// - O(log(n)) por insercao global e O(log^2(n)) por insercao em range
// - O(log(n)) por query
struct LCT{
    #define lef(x) ((x)<<1)
    #define rig(x) (lef(x)|1)
    struct func{
        ll a,b;
        #warning cuidado com overflow
        ll operator()(ll x){return a*x + b;}
    };
    #warning se for de minimo inverter
    ll bst(ll a, ll b){return max(a,b);}
    const ll inf = 1e18;
    const func off = {0,bst(-inf,inf) == inf ? -inf : inf};
    int n;
    vc<func> seg;
    LCT(int nn = 0) : n(nn), seg(nn<<2){build(1,0,n-1);}
    void build(int u,int tl,int tr){
        if(tl == tr) return void(seg[u] = off);
        int tmid = tl + tr; tmid >>= 1;
        build(lef(u),tl,tmid),build(rig(u),tmid+1,tr);
        seg[u] = off;
    }
    void add(int u,int tl,int tr, func f){
        int tmid = tl + tr; tmid >>= 1;
        if(bst(f(tmid),seg[u](tmid)) == f(tmid)) seg[u] = f;
        if(tl == tr) return;
        if(bst(f(tl),seg[u](tl)) == f(tl)) add(lef(u),tl,tmid,f);
        else add(rig(u),tmid+1,tr,f);
    }
    void add(int u,int tl,int tr,int l,int r,func f){
        if(l > r) return;
        if(tl == l && tr == r) return add(u,tl,tr,f);
        int tmid = tl + tr; tmid >>= 1;
        add(lef(u),tl,tmid,l,min(tmid,r),f), add(rig(u),tmid+1,tr,max(tmid+1,l),r,f);
    }
    void add(ll a, ll b){add(1,0,n-1,{a,b});}
    void add(int l,int r, ll a, ll b){assert(0 <= l && l <= r && r < n); add(1,0,n-1,l,r,{a,b});}
    ll query(int u,int tl,int tr,int x){
        if(tl == tr) return seg[u](x);
        int tmid = tl + tr; tmid >>= 1;
        ll ret = (tmid >= x ? query(lef(u),tl,tmid,x) : query(rig(u),tmid+1,tr,x));
        return max(ret,seg[u](x));
    }
    ll query(int x){assert(0 <= x && x < n); return query(1,0,n-1,x);}
    #undef lef
    #undef rig
};
