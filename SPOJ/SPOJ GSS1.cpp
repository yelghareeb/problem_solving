/* SPOJ GSS1 - Segment Tree
 * http://www.spoj.com/problems/GSS1/
 * 
 * Author: Youssef Elghareeb  
 */

#include <bits/stdc++.h>
using namespace std;

#define loop(i,n) for(int i = 0; i < n; i++)
#define pii pair<int, int>
typedef long long LL;

const LL INF = 1e14;
const int mod = 1e9 + 7;
const int MX = 2 * 1e5 + 5;

int n, m;
LL s[MX], mx[MX], a[MX], mx_prefix[MX], mx_suffix[MX];

void build(int l, int r, int id) {
    if (l == r) {
        s[id] = a[l];
        mx[id] = a[l];
        mx_prefix[id] = mx_suffix[id] = a[l];
    }
    else {
        int mid = (l + r) / 2;
        build(l, mid, id * 2);
        build(mid + 1, r, id * 2 + 1);
        s[id] = s[2 * id] + s[2 * id + 1]; // sum over the whole range
        mx_prefix[id] = max(mx_prefix[2 * id], s[2 * id] + mx_prefix[2 * id + 1]);
        mx_suffix[id] = max(mx_suffix[2 * id + 1], mx_suffix[2 * id] + s[2 * id + 1]);
        mx[id] = s[id];
        mx[id] = max(mx[id], mx[2 * id]);
        mx[id] = max(mx[id], mx[2 * id + 1]);
        mx[id] = max(mx[id], mx_prefix[id]);
        mx[id] = max(mx[id], mx_suffix[id]);
        mx[id] = max(mx[id], mx_suffix[2 * id] + mx_prefix[2 * id + 1]);
    }
}

pair<pair<LL, LL>, pair<LL, LL> > query(int x, int y, int l, int r, int id) {
    if (l >= x && r <= y) return {{mx[id], s[id]}, {mx_prefix[id], mx_suffix[id]}};
    if (y < l || x > r) return {{-INF, -INF}, {-INF, -INF}};
    int mid = (l + r) / 2;
    auto left = query(x, y, l, mid, id * 2);
    auto right = query(x, y, mid + 1, r, id * 2 + 1);
    LL m1 = max(left.second.first, left.first.second + right.second.first);
    LL m2 = max(right.second.second, left.second.second + right.first.second);
    LL best = max(left.first.first, right.first.first);
    best = max(best, max(m1, m2));
    best = max(best, left.first.first);
    best = max(best, right.first.first);
    best = max(best, left.second.second + right.second.first);
    return {{best, left.first.second + right.first.second}, {m1, m2}};
}

int main()
{
#ifdef DEBUG
    freopen("in.txt", "r", stdin);
#endif
    int n;
    scanf("%d", &n);
    loop(i, n) scanf("%lld", &a[i]);
    build(0, n - 1, 1);
    int m;
    scanf("%d", &m);
    // for (int i = 1; i <= 10; i++) cout << i << " " << mx[i] << endl;
    loop(i, m) {
        int l, r;
        scanf("%d%d", &l, &r);
        pair<pair<LL, LL>, pair<LL, LL> > val = query(l - 1, r - 1, 0, n - 1, 1);
        LL ans = val.first.first;
        printf("%lld\n", ans);
    }
    return 0;
}