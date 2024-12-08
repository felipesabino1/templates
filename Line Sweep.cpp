struct info{
    pair<int,int> at;
    int x,t,id;

    info(int l,int r,int t,int id) : info(make_pair(l,r),t,id){}
    info(pair<int,int> at, int t,int id) : at(at),t(t),id(id){
        if(t) x = at.second;
        else x = at.first;
    }

    bool operator <(const info & o){
        if(x == o.x) return t < o.t;
        return x < o.x;
    };
};
