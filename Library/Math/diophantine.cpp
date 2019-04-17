/*  
 * Solving Diophantine equation
 * Tutorial: https://www.techiedelight.com/find-general-solution-linear-diophantine-equation/
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

const double INF = 1e9;
const int MOD = 1e9 + 7;

#define vpii vector<pii>

struct DioSolution {
    int ans;
    int xStart, xStep;
    int yStart, yStep;
};

tuple<int, int> extended_gcd(int a, int b) {
    if (a == 0) {
        return make_tuple(0, 1);
    }

    auto it = extended_gcd(b % a, a);
    int x = get<0>(it);
    int y = get<1>(it);

    return make_tuple((y - (b / a) * x), x);
}

DioSolution solveDiophantine(int a, int b, int n) {
    DioSolution res;
    int d = __gcd(a, b);
    if (!(d % n == 0)) {
        int a1 = a / d;
        int b1 = b / d;
        int c1 = n / d;
        printf("Original Equation: %dx + %dy = %d\n", a, b, n);
        printf("Reduced Equation: %dx + %dy = 1\n", a1, b1);
        auto it = extended_gcd(a1, b1);
        int s = get<0>(it);
        int t = get<1>(it);
        
        int x0 = (n / d) * s;
        int y0 = (n / d) * t;

        printf("General solution - \n");
        printf("x = %d + %dk for any integer k\n", x0, b / d);
        printf("y = %d - %dk for any integer k\n", y0, a / d);
        
        res.xStart = x0;
        res.xStep = b / d;
        res.yStart = y0;
        res.yStep = a / d;
    }
    else {
        printf("The given equation has no solution.\n");
        res.ans = -1;
    }
    return res;
}

int main() {
#ifdef DEBUG
    freopen("in.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    DioSolution sol = solveDiophantine(21, 14, 35);
    solveDiophantine(19, 13, 20);
    return 0;
}