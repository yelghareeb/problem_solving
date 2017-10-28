/* SPOJ KQUERYO - Segment Tree with vectors
 * http://www.spoj.com/problems/KQUERYO/
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
const int MX = 30005;

int n, q, a[MX];
vector<int> tree[MX * 4];

void build(int l, int r, int id) {
    if (l == r) {
        tree[id].push_back(a[l]);
    }
    else {
        int mid = (l + r) >> 1;
        build(l, mid, id * 2);
        build(mid + 1, r, id * 2 + 1);
        merge(  tree[2 * id].begin(), 
                tree[2 * id].end(), 
                tree[2 * id + 1].begin(), 
                tree[2 * id + 1].end(),
                back_inserter(tree[id]));
    }
}

int query(int x, int y, int l, int r, int id, int k) {
    if (l >= x && r <= y) {
        return tree[id].end() - upper_bound(tree[id].begin(), tree[id].end(), k);
    }
    if (y < l || x > r) return 0;
    int mid = (l + r) >> 1;
    return query(x, y, l, mid, id * 2, k) + query(x, y, mid + 1, r, id * 2 + 1, k);
}

int main()
{
#ifdef DEBUG
    freopen("in.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    scanf("%d", &n);
    loop(i, n) scanf("%d", &a[i]);
    scanf("%d", &q);
    int ans = 0;
    build(0, n - 1, 1);
    loop(i, q) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        int l = a ^ ans;
        int r = b ^ ans;
        int k = c ^ ans;
        ans = query(l - 1, r - 1, 0, n - 1, 1, k);
        printf("%d\n", ans);
    }
    return 0;
} 