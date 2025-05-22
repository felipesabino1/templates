vector<int> Zfunction(string & s){
    vector<int> z(s.size());
    z[0] = 0;
    int l = -1, r = -1;
    for(int i=1; i<s.size(); i++){
        int qt = 0;
        if(r >= i) qt = min(r-i,z[i-l]);
        while(i+qt < s.size() && s[qt] == s[i+qt]) qt++;
        z[i] = qt;
        if(r < i+qt-1) l = i, r = i+qt-1;
    }
    return z;
}
