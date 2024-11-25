struct info{
    pair<int,int> x;
    int t;
    int id;

    info(pair<int,int> x, int t,int id) : x(x),t(t),id(id){}

    bool operator <(const info & o){
        int xx,y;
        int x2,y2;
        xx = (t ? x.second : x.first);
        x2 = (t ? x.first : x.second);
        y = (o.t ? o.x.second : o.x.first);
        y2 = (o.t ? o.x.first : o.x.second);
        if(xx == y && t == o.t) return x2 > y2;
        if(xx == y) return t < o.t;
        return xx < y;
    };
};
