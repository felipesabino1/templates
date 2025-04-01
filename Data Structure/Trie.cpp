struct Node{
    map<char,int> prox; // se for de char eh melhor fazer um map que ai nao cria uns caracteres inuteis na trie
    bool ended = false;
    int & operator[](const char & c){return prox[c];}
};
int timer = 1;
const int TAM_TRIE = MAX * constante;
Node trie[TAM_TRIE];
void insert(string & s){
    int at = 0;
    for(int i=0; i<s.size(); i++){
        auto & it = trie[at][s[i]];
        if(it == 0) it = timer++;
        at = it;
    }
    trie[at].ended = true;
}
