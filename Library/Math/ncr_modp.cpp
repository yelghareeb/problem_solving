#include <bits/stdc++.h>
using namespace std;

#define loop(i,n) for(int i = 0; i < n; i++)
typedef long long LL;

const int MOD = 1e9 + 7;
const int MX = 1e6 + 200;

LL factorial[MX];

LL modPow(LL a, LL x, LL p)
{
    //calculates a^x mod p
    LL res = 1;
    while(x) {
        if (x % 2) res = (res * a) % p;
        a = (a * a) % p;
        x /= 2;
    }
    return (res % p);
}

LL modInverse(LL a, LL p)
{
    //calculates the modular multiplicative of a mod m assuming p is prime
    return modPow(a, p-2, p);
}

LL ncrmodp (LL n, LL r, LL p) {
    return (factorial[n] * modInverse((factorial[n - r] * factorial[r]) % p, p)) % p;
}

void init() {
    // Calculates factorial from 1 to MX
    factorial[0] = 1;
    for (int i = 1; i < MX; i++) {
        factorial[i] = ((LL) i * factorial[i - 1]) % MOD;
    }
}

int main()
{
#ifdef DEBUG
    freopen("in.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    init();
    assert(ncrmodp(10, 4, MOD) == 210);
    assert(ncrmodp(100, 15, MOD) == 253338471349988640ll % MOD);
    assert(ncrmodp(30, 7, MOD) == 2035800);
    assert(ncrmodp(1542, 123, MOD) == 302513227);
    return 0;
}