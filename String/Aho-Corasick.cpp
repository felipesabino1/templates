/*
    Sempre chamar o build depois que inserir todas as strings pra construir o automato
*/
const int ALP = 26; // tamanho do alfabeto
struct node{
    int prox[ALP] = {0}, aut[ALP] = {0};
    int p = 0, ep = 0; // kmp like, kmp like with end of string
    bool fim = false;
    node(){}
    // vector<int> ids; // sometimes put id of each string end
};
vector<node> trie(1);
void insert(string & s, int id){
    int at = 0;
    for(char c : s){
        c -= 'a'; // int& prox = trie[at].prox[c] eh paia pq no emplace_back() o ponteiro vai dar pau
        if(trie[at].prox[c] == 0) {
            trie[at].prox[c] = int(trie.size());
            trie.emplace_back();
        }
        at = trie[at].prox[c];
    }
    trie[at].fim = true;
}
void build(){
    queue<int> q;
    q.push(0);
    while(!q.empty()){
        int u = q.front();
        q.pop();
        int *prox = trie[u].prox, *aut = trie[u].aut;
        int p = trie[u].p;
        for(int c=0; c<ALP; c++){
            if(prox[c] != 0){
                int v = prox[c];
                aut[c] = v;
                q.push(v);

                trie[v].p = (u == 0 ? 0 : trie[p].aut[c]); // ja calcular o link dos prox caras
            }else if(u == 0) aut[c] = 0;
            else aut[c] = trie[p].aut[c];
        }
        if(trie[p].fim) trie[u].ep = p;
        else trie[u].ep = trie[p].ep;
    }
}
