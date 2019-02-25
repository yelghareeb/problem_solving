/*  
 * Fib sequences with Matrix multiplication
 * Given a fib sequence with initial numbers (a, b)
 * We calculate
 *   1) the nth element of the sequence
 *   2) the sum of the first nth elements
 * using the following recurrences
 *   f[n] = f[n - 1] + f[n - 2]
 *   s[n] = s[n - 1] + f[n]
 * 
 * The above recurrences can be expressed with the following
 * matrix/vector multiplication:
 *  f[n]          1  1  0     f[n - 1]
 *  f[n - 1]  =   1  0  0  .  f[n - 2]
 *  s[n - 1]      1  0  1     s[n - 2]
 * 
 * Bonus problems:
 *   https://codeforces.com/problemset/problem/446/C
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

namespace FIB {
    struct Matrix {
        int a[3][3];

        Matrix() {
            memset(a, 0, sizeof(a));
        }
        Matrix operator* (const Matrix& M2) {
            Matrix result;
            loop(i, 3) loop(j, 3) loop(k, 3) result.a[i][j] += (this->a[i][k] * M2.a[k][j]);
            return result;
        }
        Matrix eye() {
            Matrix res;
            loop(i, 3) res.a[i][i] = 1;
            return res;
        }
        Matrix exp(int pw) {
            if (pw == 0) return eye();
            if (pw == 1) return *this;
            Matrix half = this->exp(pw / 2);
            if (pw % 2) return half * half * (*this);
            return half * half;
        }
    };
    Matrix initMat() {
        Matrix res;
        int dx[] = {0, 0, 1, 2, 2};
        int dy[] = {0, 1, 0, 0, 2};
        loop(i, 5) res.a[dx[i]][dy[i]] = 1;
        return res;
    }
    vi mul(Matrix base, vi V) {
        assert(V.size() == 3);
        vi res(3, 0);
        loop(i, 3) loop(j, 3) res[i] += base.a[i][j] * V[j];
        return res;
    }
    vi fib(int a, int b, int n) {
        Matrix base = initMat();
        base = base.exp(n - 1);
        int B[] = {b, a, a};
        vi V(B, B + 3);
        vi res = mul(base, V);
        return res;
    }
}

int main() {
#ifdef DEBUG
    freopen("in.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);    
    for (int i = 1; i < 10; i += 1) cout << FIB::fib(1, 1, i)[1] << " ";
    cout << endl;
    for (int i = 1; i < 10; i += 1) cout << FIB::fib(1, 1, i)[2] << " ";
    cout << endl;
    return 0;
}