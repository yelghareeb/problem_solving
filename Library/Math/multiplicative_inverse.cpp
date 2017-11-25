#include <bits/stdc++.h>
using namespace std;

#define loop(i,n) for(int i = 0; i < n; i++)
typedef long long LL;

const int MOD = 1e9 + 7;
const int MX = 1e6 + 5;

LL mul_inv(LL a, LL b = MOD) {
    LL t1 = a, t2 = b, t3;
    LL v1 = 1, v2 = 0, v3;
    while (t2 != 1) {
        LL x = t1 / t2;
        t3 = t1 - x*t2;
        v3 = v1 - x*v2;
        t1 = t2, t2 = t3;
        v1 = v2, v2 = v3;
    }
    return (v2 + b) % b;
}

int main()
{
#ifdef DEBUG
    freopen("in.txt", "r", stdin);
#endif
    for (int i = 1; i <= 100; i++)
        assert(i * mul_inv(i) % MOD == 1);
    return 0;
}