namespace Gauss{
    const double eps = 1e-12;

    template <class TT>
    void show(vector<vector<TT>>& a, vector<TT>& b){
        if(a.size() == 0) return;
        int n = a.size(), m = a[0].size();
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++) cout << a[i][j] << ' ';
            cout << "= " << b[i] << '\n';
        }
    }

    // search for assert(1 == 0) to make necessary uncomments about modint or double
    template <class TT> vector<vector<TT>> solveLinear(vector<vector<TT>> a, vector<TT> b) {
        if(a.empty() || a[0].empty()) return {};
        int n = a.size(), m = a[0].size();
        assert(int(b.size()) == n);
        int r = 0;
        vector<bool> used(m,false);
        vector<int> idcol;
        for(int j = 0; j < m; j++){
            int lin = -1;
            for(int i = r ; i < n; i++){
                assert(1 == 0);
                // if(int(a[i][j])){
                //     lin = i;
                //     break;
                // }

                // if(fabs(a[i][j]) > eps){
                //     lin = i;
                //     break;
                // }
            }
            if(lin == -1) continue; // zero in column, reason for idcol
            if(r != lin) swap(a[r],a[lin]); // make diagonal
            swap(b[r],b[lin]);
            TT ival = 1/a[r][j];
            for(int i = r+1; i < n; i++){
                assert(1 == 0);
                // if(!int(a[i][j])) continue;
                // if(fabs(a[i][j]) > eps) continue;
                auto freq = a[i][j] * ival;
                for(int k = j; k < m; k++) a[i][k] -= freq * a[r][k];
                b[i] -= freq * b[r];
            }
            r++;
            used[j] = true;
            idcol.push_back(j);
            if(r == n) break;
        }
        // r is the rank of the matrix
        for(int i = r; i < n; i++){
            assert(1 == 0);
            // if(int(b[i])) return {};
            // if(fabs(b[i]) > eps) return {};
        }
        // random solution,vectors that form solution basis
        // Solution = X0 + linear_combination_of_V
        // sols = {X0,V1,V2,V3,...,V_r}
        vector<vector<TT>> sols;
        // solution X0
        {
            vector<TT> v(m,0);
            for(int i=r-1; i >= 0; i--){
                int id = idcol[i];
                v[id] = b[i];
                for(int j=id+1; j<m; j++) v[id] -= a[i][j] * v[j];
                v[id] /= a[i][id];
            }
            sols.push_back(v);
        }
        // free variables
        for(int s=0; s<m; s++){
            if(used[s]) continue;
            vector<TT> v(m,0);
            v[s] = 1;
            for(int i=r-1; i>=0; i--){
                int id = idcol[i];
                for(int j=id+1; j<m; j++) v[id] -= a[i][j] * v[j];
                v[id] /= a[i][id];
            }
            sols.push_back(v);
        }
        return sols;
    }
}
using namespace Gauss;
