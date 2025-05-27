vector<int> kmp(string & s){
    vector<int> p(s.size());
    vector<vector<int>> aut(s.size(),vector<int>(30)); // colocar o tamanho do alfabeto
    p[0] = 0;
    for(int i=1; i<s.size(); i++){
        int j = p[i-1];
        while(j != 0 && s[i] != s[j]) j = p[j-1];
        if(s[i] == s[j]) j++;
        p[i] = j;
    }
    // aqui o i representa que eu ainda to processando o i-esimo caracter, quando eu processo ele que eu transito
    for(int i=0; i<n; i++){
        for(int j=0; j<30; j++){
            if(i == 0) aut[i][j] = (s[i] == j + 'a');
            else if(s[i] == j+'a') aut[i][j] = i+1;
            else aut[i][j] = aut[p[i-1]][j]; // o caracter atual nao deu, transito pro p do anterior (proximo do anterior)
        }
    }
    return p;
}
