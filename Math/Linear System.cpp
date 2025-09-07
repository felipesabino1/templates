// if using modular gauss, change THAT PART and use mint
namespace Gauss{
    using vi = vector<int>;
    const double eps = 1e-12;

    template <class TT>
    void show(vector<vector<TT>>& A, vector<TT>& b){
        int n = A.size(), m = b.size();
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++) cout << A[i][j] << ' ';
            cout << "= " << b[i] << '\n';
        }
    }

    template <class T>
    int solveLinear(vector<vector<T>>& A, vector<T>& b, vector<T>& x) {
        int n = A.size(), m = x.size(), rank = 0, br, bc;
        if (n) assert(A[0].size() == m);
        vi col(m); iota(col.begin(),col.end(), 0); // fills the range with increasing values starting with value 0

        for(int i = 0; i < n; i++){
            T v, bv = 0;

            for(int r = i; r < n; r++) for(int c = i; c < m; c++)
                if((v = A[r][c]) > bv)
                    br = r, bc = c, bv = v;
            if(bv <= eps){
                for(int j = i; j < n; j++) if(fabs(b[j]) > eps) return -1;
                break;
            }

            // THAT PART
            // for(int r = i; r < n; r++) for(int c = i; c < m; c++)
            //     if ((v = fabs(A[r][c])) > bv)
            //         br = r, bc = c, bv = v;
            // if(bv) {
            //     for(int j = i; j < n; j++) if(b[j]) return -1;
            //     break;
            // }
            
            // put in the diagonal
            swap(A[i], A[br]);
            swap(b[i], b[br]); 
            swap(col[i], col[bc]);
            for(int j = 0; j < n; j++) swap(A[j][i], A[j][bc]);
            
            bv = 1/A[i][i]; 
            // faster, dont update useless values
            for(int j = i+1; j < n; j++){
                // A[i][i]*(1/A[i][i] * A[j][i]) = A[i][i]*fac (zero the column)
                T fac = A[j][i] * bv; 
                b[j] -= fac * b[i];
                for(int k = i+1; k < m; k++) A[j][k] -= fac*A[i][k];
            }
            // slower, turn lines to zero

            // zero the column
            rank++;
        }

        // variable values
        x.assign(m, 0);
        for (int i = rank; i--;) {
            b[i] /= A[i][i];
            x[col[i]] = b[i];
            for(int j = 0; j < i; j++) b[j] -= A[j][i] * b[i]; // o valor da variavel x_i eu descobri agora eu desconto o valor dela nas equacoes acima
        }
        return rank; // (multiple solutions if rank < m)
    }
}
using namespace Gauss;
