struct node{
    map<char,int> prox; // se for de char eh melhor fazer um map que ai nao cria uns caracteres inuteis na trie
    bool fim = false;
    int& operator[](int x){return prox[x];}
};
vc<node> trie(1);
void insert(string & s){
    int at = 0;
    for(int i=0; i<s.size(); i++){
        if(!trie[at][s[i]]){
            trie[at][s[i]] = trie.size();
            trie.emplace_back();
        }
        at = trie[at][s[i]];
    }
    trie[at].fim = true;
}
