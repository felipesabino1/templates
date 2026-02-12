// Resolve sistema linear
// Se for usar double ou modint eh so mudar o TT
// Retorna uma solucao, caso exista, e outros vetores para vc alterar a solucao base
// O Rank vai ser o tamanho do vetor de retorno -1
// O(N^2 * M)
namespace Gauss{
    const double eps = 1e-9;
    using TT = double; // modint

    void show(vvc<TT>& a, vc<TT>& b){
        if(a.size() == 0) return;
        int n = a.size(), m = a[0].size();
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++) cout << a[i][j] << ' ';
            cout << "= " << b[i] << '\n';
        }
    }
    bool zero(TT x){ // x == 0?
        return fabs(x) < eps;
        // return !int(x.v);
    }

    vvc<TT> solveLinear(vvc<TT> a, vc<TT> b){
        if(a.empty() || a[0].empty()) return {};
        int n = a.size(), m = a[0].size(), r = 0;
        assert(int(b.size()) == n);
        vc<bool> used(m,false); vc<int> idcol;
        for(int j = 0; j < m; j++){
            int lin = -1;
            for(int i = r ; i < n; i++) if(!zero(a[i][j])){
                lin = i;
                break;
            }
            if(lin == -1) continue; // so tem zero na coluna, motivo de existir idcol
            if(r != lin) swap(a[r],a[lin]); // arrumar a diagonal
            swap(b[r],b[lin]);
            TT ival = 1/a[r][j];
            for(int i = r+1; i < n; i++){
                if(zero(a[i][j])) continue;
                auto freq = a[i][j] * ival;
                for(int k = j; k < m; k++) a[i][k] -= freq * a[r][k];
                b[i] -= freq * b[r];
            }
            r++, used[j] = true, idcol.push_back(j);
            if(r == n) break;
        }
        // r eh o rank da matriz
        for(int i = r; i < n; i++) if(!zero(b[i])) return {};
        // return r; se quiser retornar o rank da matriz

        // X0 = solucao aleatoria
        // V_i = Vetor_i
        // C = sum(V_i * c_i), C eh uma combinacao linear qualquer de V
        // Solucao_qualquer = X0 + C
        // sols = {X0,V1,V2,V3,...,V_r}
        vvc<TT> sols;
        // solution X0
        {
            vc<TT> v(m,0);
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
            vc<TT> v(m,0);
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
