/*  
 * UVA 10518 - How Many Calls?
 * https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1459
 * Idea: Matrix exponenetiation
 * 
 * Author: Youssef Elghareeb
 */

#include <bits/stdc++.h>
using namespace std;

#define loop(i,n) for(int i = 0; i < n; i++)
#define pii pair<int, int>
#define all(v) v.begin(),v.end()
#define S second
#define F first
#define vi vector<int>
#define pb push_back

typedef long long LL;

const LL INF = 1e18 + 5;
const int mod = 1e9 + 7;

#define vpii vector<pii>

int md;

namespace FIB {
    struct Matrix {
        LL a[3][3];

        Matrix() {
            memset(a, 0, sizeof(a));
        }
        Matrix operator* (const Matrix& M2) {
            Matrix result;
            loop(i, 3) loop(j, 3) loop(k, 3) {
                result.a[i][j] += (this->a[i][k] * M2.a[k][j]) % md;
                result.a[i][j] %= md;
            }
            return result;
        }
        Matrix eye() {
            Matrix res;
            loop(i, 3) res.a[i][i] = 1;
            return res;
        }
        Matrix exp(LL pw, int md) {
            if (pw == 0) return eye();
            if (pw == 1) return *this;
            Matrix half = this->exp(pw / 2, md);
            if (pw % 2) return half * half * (*this);
            return half * half;
        }
    };
    
    vi mul(Matrix base, vi V, int md) {
        assert(V.size() == 3);
        vi res(3, 0);
        loop(i, 3) loop(j, 3) {
            res[i] = (res[i] + base.a[i][j] * V[j]) % md;
        }
        return res;
    }
}

FIB::Matrix getMatrix() {
    FIB::Matrix base;
    int dx[] = {0, 0, 0, 1, 2};
    int dy[] = {0, 1, 2, 0, 2};
    loop(i, 5) base.a[dx[i]][dy[i]] = 1;
    return base;
}

int main() {
#ifdef DEBUG
    freopen("in.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);    
    LL n, b;
    FIB::Matrix base = getMatrix();
    int test = 1;
    while (true) {
        cin >> n >> b;
        if (n == 0 && b == 0) break;
        md = b;
        LL ans = 0;
        if (n == 0) ans = 1;
        else if (n == 1) ans = 1;
        else if (n == 2) ans = 3;
        else {
            FIB::Matrix exp = base.exp(n - 2, b);
            vi v(3);
            v[0] = 3; v[1] = 1; v[2] = 1;
            ans = (FIB::mul(exp, v, b)[0]) % b;
        }
        ans %= b;
        cout << "Case " << test << ": " << n << " " << b << " " << ans << endl;
        test += 1;
    }
    return 0;
}