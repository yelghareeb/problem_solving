/* Segment Trees with lazy propagation 
 * Increase updates, querying for maximum
 * 
 * Author: Youssef Elghareeb
 */

#include <bits/stdc++.h>
using namespace std;

#define loop(i,n) for(int i = 0; i < n; i++)
#define pii pair<int, int>
typedef long long LL;

const int INF = 1e9;
const int mod = 1e9 + 7;
const int MX = 1e5 + 5;

int n, m;
int s[MX], lazy[MX], a[MX];

void build(int l, int r, int id) {
    if (l == r) {
        s[id] = a[l];
    }
    else {
        int mid = (l + r) / 2;
        build(l, mid, id * 2);
        build(mid + 1, r, id * 2 + 1);
        s[id] = max(s[id * 2], s[id * 2 + 1]);
    }
}

void upd(int id, int l, int r, int val) {
    lazy[id] += val;
    s[id] += val;
}

void shift(int id, int l, int r) {
    int mid = (l + r) / 2;
    upd(id * 2, l, mid, lazy[id]);
    upd(id * 2 + 1, mid + 1, r, lazy[id]);
    lazy[id] = 0;
}

/* Increase range [x, y] by val */
void update(int x, int y, int l, int r, int id, int val) {
    if (l >= x && r <= y) {
        upd(id, l, r, val);
        return;
    }
    if (y < l || x > r) return;
    shift(id, l, r); // pass lazy updates to children
    int mid = (l + r) / 2;
    update(x, y, l, mid, id * 2, val);
    update(x, y, mid + 1, r, id * 2 + 1, val);
    s[id] = max(s[id * 2], s[id * 2 + 1]);
}

int query(int x, int y, int l, int r, int id) {
    if (l >= x && r <= y) {
        return s[id];
    }
    if (y < l || x > r) return -INF;
    shift(id, l, r);
    int mid = (l + r) / 2;
    return max(query(x, y, l, mid, id * 2), query(x, y, mid + 1, r, id * 2 + 1));
}

int main()
{
#ifdef DEBUG
    freopen("in.txt", "r", stdin);
#endif
    int n;
    int arr[] = {2, 1, 5, 7, 3, 6, 1, 10};
    loop(i, 10) a[i] = arr[i];
    n = 10;
    build(0, n - 1, 1);
    int val = query(0, 2, 0, n - 1, 1); // query max from [0, 2]
    assert(val == 5);
    update(0, n - 1, 0, n - 1, 1, 1); // increase the whole array by 1
    val = query(4, 5, 0, n - 1, 1); // query max from [4, 5]
    assert(val == 7);
    update(0, n - 1, 0, n - 1, 1, 3); // increase the whole array by 3
    val = query(7, 8, 0, n - 1, 1);
    assert(val == 14);
    return 0;
}