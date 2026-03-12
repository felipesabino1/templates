// Dado uma string S computa o suffix automaton de S
// Suffix automaton eh um automato que so aceita sufixos de S
// Cada path do automato corresponde a uma substring de S
// O(N), 2*N estados e no maximo 3*N-4 transicoes
struct SAM{
    struct node{
        // int prox[ALP] = {0};
        map<char,int> prox; 
        int len,p; bool suf = false;
        node(){}
        int& operator[](int x){return prox[x];}
        bool operator()(int x){return prox.count(x);}
    };
    // node trie[MAX<<1]; int timer = 0;
    vc<node> trie; int lst;
    vc<int> cnt; // endpos de cada estado
    SAM(string& s){
        trie.emplace_back(); cnt.push_back(0);
        trie[0].len=0, trie[0].p=-1, lst=0;
        for(char c : s) add(c);
        for(int u=lst; u != -1; u = trie[u].p) trie[u].suf = true;
        // contar endpos
        vc<int> in(trie.size(),0); for(int i=1; i<trie.size(); i++) in[trie[i].p]++;
        queue<int> q; for(int i=0; i<trie.size(); i++) if(!in[i]) q.push(i);
        while(!q.empty()){
            int u = q.front(); q.pop();
            if(!u) continue;
            cnt[trie[u].p] += cnt[u];
            in[trie[u].p]--; if(!in[trie[u].p]) q.push(trie[u].p);
        }
    }
    void add(int c){
        int cur = trie.size(); cnt.push_back(1);
        trie.emplace_back(); trie[cur].len = trie[lst].len+1;
        int p = lst,q;
        for(; p != -1 && !trie[p](c); p = trie[p].p) trie[p][c] = cur;
        if(p == -1 || (trie[q = trie[p][c]].len) == trie[p].len+1) trie[cur].p = (p == -1 ? 0 : q);
        else{
            int clone = trie.size(); cnt.push_back(0);
            trie.emplace_back(); trie[clone] = trie[q]; 
            trie[clone].len = trie[p].len+1; trie[q].p = trie[cur].p = clone;
            for(; p != -1 && trie[p][c] == q; p = trie[p].p) trie[p][c] = clone;
            
        }
        lst = cur;
    }
};
