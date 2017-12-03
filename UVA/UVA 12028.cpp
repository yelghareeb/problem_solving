/*
	A gift from the setter
	Idea: ad hoc, dp
	https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3179
	
	Author: Youssef Elghareeb
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
#define loop(i,n) for(int i = 0; i < n; i++)
#define pii pair<LL, int>
#define vi vector<int> 
#define pb push_back

const int MX = 1e5 + 5;
const int mod = 1e6 + 7;
int a[MX + 5];
int mp[mod + 5];

int main () {
#ifdef DEBUG
    freopen("in.txt", "r", stdin);
#endif
    int tests;
    scanf("%d", &tests);
    for (int test = 0; test < tests; test++) {
        int k, c, n, a0;
        memset(mp, 0, sizeof(mp));
        scanf("%d%d%d%d", &k, &c, &n, &a0);
        a[0] = a0;
        mp[a0]++;
        for(int i = 1; i < n; i++) {
            a[i] = ((LL) k * a[i - 1] + c) % mod;
            mp[a[i]]++;
        }
        LL res = 0;
        LL prev = 0;
        int cnt = 0;
        for (int i = 0; i < mod; i++) {
            prev += cnt;
            res += prev * mp[i];
            cnt += mp[i];
        }
        printf("Case %d: %lld\n", test + 1, res);
    }
    return 0; 
}