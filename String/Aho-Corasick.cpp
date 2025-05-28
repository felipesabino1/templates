/*
    Sempre chamar o build depois que inserir todas as strings pra construir o automato
*/
const int ALP = 26; // tamanho do alfabeto
struct node{
    int prox[ALP] = {0}, aut[ALP] = {0};
    int link = 0, elink = 0; // kmp like, kmp like with end of string
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
    trie[at].ids.push_back(id);
}
void build(){
    queue<int> q;
    q.push(0);
    while(!q.empty()){
        int u = q.front();
        q.pop();
        int *prox = trie[u].prox, *aut = trie[u].aut;
        int link = trie[u].link;
        for(int j=0; j<ALP; j++){
            if(prox[j] != 0){
                aut[j] = prox[j];
                q.push(prox[j]);

                trie[prox[j]].link = (u == 0 ? 0 : trie[link].aut[j]); // ja calcular o link dos prox caras
            }else if(u == 0) aut[j] = 0;
            else aut[j] = trie[link].aut[j];
        }
        if(trie[link].fim) trie[u].elink = link;
        else trie[u].elink = trie[link].elink;
    }
}
