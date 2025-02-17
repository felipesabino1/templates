struct Gauss{
    typedef vector<double> vd;
    typedef vector<long long int> vl;
    typedef vector<int> vi;
    const double eps = 1e-12;

    /**
    * Author: Per Austrin, Simon Lindholm
    * Date: 2004-02-08
    * License: CC0
    * Description: Solves $A * x = b$. If there are multiple solutions, an arbitrary one is returned.
    *  Returns rank, or -1 if no solutions. Data in $A$ and $b$ is lost.
    * Time: O(n^2 m)
    * Status: tested on kattis:equationsolver, and bruteforce-tested mod 3 and 5 for n,m <= 3
    */
    int solveLinear(vector<vd>& A, vd& b, vd& x) {
        int n = A.size(), m = x.size(), rank = 0, br, bc;
        if (n) assert(A[0].size() == m);
        vi col(m); iota(col.begin(),col.end(), 0); // fills the range with increasing values starting with value 0

        for(int i = 0; i < n; i++){
            double v, bv = 0;

            // busca pelo maior elemento
            for(int r = i; r < n; r++) for(int c = i; c < m; c++)
                if ((v = fabs(A[r][c])) > bv)
                    br = r, bc = c, bv = v;
            // bv eh o maior elemento, se todos os elementos sao iguais a zero
            if (bv <= eps) {
                // se no vetor de resposta tiver um cara diferente de zero, nao existe x tal que 0*x != 0
                for(int j = i; j < n; j++) if (fabs(b[j]) > eps) return -1;
                break;
            }
            
            swap(A[i], A[br]); // trocar a linha atual pela linha que tem o maior elemento
            swap(b[i], b[br]); // trocar a linha pra ficar igual no vetor de resposta
            swap(col[i], col[bc]); // trocar no vetor de coluna
            for(int j = 0; j < n; j++) swap(A[j][i], A[j][bc]); // trocar os elementos da coluna atual pelos elementos da coluna do maior elemento
            
            bv = 1/A[i][i]; // a razao necessaria pra fazer o elemento atual da diagonal ser 1 
            // eu nao atualizo de verdade os valores de A[i][i] e b[i] nao sei pq, deve ser pq fica mais rapido nao atualizar eles de vdd
            for(int j = i+1; j < n; j++){
                double fac = A[j][i] * bv; // para zerar o elemento A[j][i] precisamos subtair dele A[i][i]*(1/A[i][i] * A[j][i]) = A[i][i]*fac
                // esse fac eh o valor que eu vou usar pra eliminar a linha j, ou seja, Linha_j <- Linha_j - Linha_i * fac, e eh isso que 
                // ta fazendo aqui embaixo
                b[j] -= fac * b[i];
                for(int k = i+1; k < m; k++) A[j][k] -= fac*A[i][k];
            }
            // se eu consegui zerar essa coluna, entao a variavel dessa coluna eh diferente de zero (eh uma equacao linearmente independente)
            rank++;
        }

        x.assign(m, 0);
        for (int i = rank; i--;) {
            // atribuo as respostas
            b[i] /= A[i][i];
            x[col[i]] = b[i];
            for(int j = 0; j < i; j++) b[j] -= A[j][i] * b[i]; // o valor da variavel x_i eu descobri agora eu desconto o valor dela nas equacoes acima
        }
        return rank; // (multiple solutions if rank < m)
    }
    // tem que passar o modulo
    template <int M> int solveLinear(vector<vl>& A, vl& b, vl& x) {
        int n = A.size(), m = x.size(), rank = 0, br, bc;
        if (n) assert(A[0].size() == m);
        vi col(m); iota(col.begin(),col.end(), 0); // fills the range with increasing values starting with value 0

        for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) A[i][j] = (A[i][j]%M + M)%M;
        for(int i = 0; i < n; i++) b[i] = (b[i]%M + M)%M;

        for(int i = 0; i < n; i++){
            ll v, bv = 0;

            // busca pelo maior elemento
            for(int r = i; r < n; r++) for(int c = i; c < m; c++)
                if ((v = A[r][c]))
                    br = r, bc = c, bv = v;
            // bv eh o maior elemento, se todos os elementos sao iguais a zero
            if (bv == 0) {
                // se no vetor de resposta tiver um cara diferente de zero, nao existe x tal que 0*x != 0
                for(int j = i; j < n; j++) if (b[j]) return -1;
                break;
            }
            
            swap(A[i], A[br]); // trocar a linha atual pela linha que tem o maior elemento
            swap(b[i], b[br]); // trocar a linha pra ficar igual no vetor de resposta
            swap(col[i], col[bc]); // trocar no vetor de coluna
            for(int j = 0; j < n; j++) swap(A[j][i], A[j][bc]); // trocar os elementos da coluna atual pelos elementos da coluna do maior elemento
            
            bv = inv(A[i][i],M); // a razao necessaria pra fazer o elemento atual da diagonal ser 1 
            // eu nao atualizo de verdade os valores de A[i][i] e b[i] nao sei pq, deve ser pq fica mais rapido nao atualizar eles de vdd
            for(int j = i+1; j < n; j++){
                ll fac = A[j][i] * bv % M; // para zerar o elemento A[j][i] precisamos subtair dele A[i][i]*(1/A[i][i] * A[j][i]) = A[i][i]*fac
                // esse fac eh o valor que eu vou usar pra eliminar a linha j, ou seja, Linha_j <- Linha_j - Linha_i * fac, e eh isso que 
                // ta fazendo aqui embaixo
                b[j] = (b[j] - fac * b[i]%M + M)%M;
                for(int k = i+1; k < m; k++) A[j][k] = (A[j][k] - fac*A[i][k]%M + M)%M;
            }
            // se eu consegui zerar essa coluna, entao a variavel dessa coluna eh diferente de zero (eh uma equacao linearmente independente)
            rank++;
        }

        x.assign(m, 0);
        for (int i = rank; i--;) {
            // atribuo as respostas
            b[i] = b[i] * inv(A[i][i],M)%M;
            x[col[i]] = b[i];
            for(int j = 0; j < i; j++) b[j] = (b[j] - A[j][i] * b[i]%M + M)%M; // o valor da variavel x_i eu descobri agora eu desconto o valor dela nas equacoes acima
        }
        return rank; // (multiple solutions if rank < m)
    }

    void show(vector<vl>& A, vl& b){
        int n = A.size(), m = b.size();
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++) cout << A[i][j] << ' ';
            cout << "= " << b[i] << '\n';
        }
    }

    ll modpow(ll b, ll e, ll mod) {
        ll ans = 1;
        for (; e; b = b * b % mod, e /= 2)
            if (e & 1) ans = ans * b % mod;
        return ans;
    }

    ll inv(ll x, ll mod){
        return modpow(x,mod-2,mod);
    }
};
