/*  
 * String Hashing
 * With O(n) preprocessing, you can get the hash of any substring in the string in O(1)
 * For a detailed explanation, please review https://cp-algorithms.com/string/string-hashing.html
 * Implementation taken from V--o_o--V https://codeforces.com/contest/1056/submission/46214876
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

const int N = 1e6 + 5;

template<LL MOD>
LL norm(LL x) {
    x %= MOD;
    if (x < 0) {
        x += MOD;
    }

    return x;
}

constexpr LL M1 = static_cast<LL>(1000002637);
constexpr LL M2 = static_cast<LL>(1000002649);

struct Hash {
    LL l;
    LL r;

    Hash(LL cl, LL cr)
        : l(norm<M1>(cl)), r(norm<M2>(cr))
    {
    }

    Hash(LL x = 0)
        : l(x), r(x)
    { 
    }

    Hash operator + (const Hash& rhs) const {
        return { l + rhs.l, r + rhs.r };
    }

    Hash operator * (const Hash& rhs) const {
        return { l * rhs.l, r * rhs.r };
    }

    Hash operator - (const Hash& rhs) const {
        return { l - rhs.l, r - rhs.r };
    }

    bool operator != (const Hash& rhs) const {
        return l != rhs.l || r != rhs.r;
    }
    
    bool operator == (const Hash& rhs) const {
        return l == rhs.l && r == rhs.r;
    }
};

namespace StringHash {
    Hash h[N];
    Hash pw[N];

    Hash HSH = 239;
    
    void initString(const string& s) {
        int m = s.length();
        pw[0] = 1;
        for (int i = 1; i <= m; ++i) {
            pw[i] = pw[i - 1] * HSH;
        }
        for (int i = 0; i < m; ++i) {
            h[i + 1] = h[i] + pw[m - i] * (s[i] - 'a');
        }
    }
    
    Hash getHash(int l, int r) {
        return pw[l] * (h[r + 1] - h[l]);
    }
}

int main() {
#ifdef DEBUG
    freopen("in.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin >> s >> t;
    string s1 = "abncnabnfb";
    StringHash::initString(s1);
    assert(StringHash::getHash(0, 1) == StringHash::getHash(5, 6));
    assert(StringHash::getHash(0, 2) == StringHash::getHash(5, 7));
    assert(StringHash::getHash(0, 3) != StringHash::getHash(5, 6));
    return 0;
}