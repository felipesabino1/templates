/*
    Indexado de 0. O(N)
    
    Calcula a qtd de palindromos usando da propriedade que pal(i,j) = pal(i+1,j-1) + (s[i] == s[j])
    Retorna man[i] = x tal que x eh o tam da metade de um palindromo em que o i eh o meio, se for tamanho par, o i eh meio da esquerda, aba, no b eu conto 2
    man[0] = palindromos pares, man[1] = palindromos impares
*/
vector<vector<int>> manacher(string & s){
    vector<vector<int>> man(2,vector<int>(s.size(),-1));
    int n = s.size();
    // even
    int l = -1, r = -1;
    for(int i=0; i<s.size(); i++){
        int qt = 0;
        if(r >= i+1) qt = min(r - (i+1)+1, man[0][l + (r-(i+1))]);
        while(i - qt >= 0 && i+1 + qt < n && s[i-qt] == s[i+1+qt]) qt++;
        man[0][i] = qt;
        if(r < i+1 + qt - 1){
            l = i - qt + 1;
            r = i+1 + qt - 1;
        }
    }
    // odd
    l = r = -1;
    for(int i=0; i<s.size(); i++){
        int qt = 0;
        if(r >= i) qt = min(r-i,man[1][l + (r-i)]);
        while(i-qt >= 0 && i+qt < n && s[i-qt] == s[i+qt]) qt++;
        man[1][i] = qt;
        if(r < i + qt - 1){
            l = i - qt + 1;
            r = i + qt - 1;
        }
    }
    return man;
}
