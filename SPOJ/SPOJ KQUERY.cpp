/* 
	SPOJ KQUERY
	http://www.spoj.com/problems/KQUERY/
	Author: Youssef ElGhareeb
	
	Idea: Segment Trees with offline queries
*/

#include <bits/stdc++.h>
using namespace std;

#define loop(i,n) for(int i = 0; i < n; i++)
#define pii pair<int, int>
typedef long long LL;

const int INF = 1e9;
const int mod = 1e9 + 7;
const int MX = 1e5 + 5;

string s;
int n, m;
pair<int, int> a[MX];
pair<pii, pii > Q[3 * MX];
int d[4 * MX], ans[4 * MX];

void build(int l, int r, int id) {
    if (l == r) {
        d[id] = 1;
    }
    else {
        int mid = (l + r) / 2;
        build(l, mid, id * 2);
        build(mid + 1, r, id * 2 + 1);
        d[id] = d[id * 2] + d[id * 2 + 1];
    }
}

void upd (int l, int r, int pos, int val, int id) {
    if (l == r) {
        d[id] = val;
    }
    else {
        int mid = (l + r) / 2;
        if (pos <= mid) upd(l, mid, pos, val, id * 2);
        else upd(mid + 1, r, pos, val, id * 2 + 1);
        d[id] = d[2 * id] + d[2 * id + 1];
    }
}

int query(int l, int r, int l1, int r1, int id) {
    if (l1 >= l && r1 <= r) return d[id];
    if (r < l1 || l > r1) return 0;
    int mid = (l1 + r1) / 2;
    return query(l, r, l1, mid, id * 2) + query (l, r, mid + 1, r1, id * 2 + 1);
}

int main()
{
#ifdef DEBUG
    freopen("in.txt", "r", stdin);
#endif
    scanf("%d", &n);
    loop(i, n) {
        int val; 
        scanf("%d", &val);
        a[i] = {val, i};
    }
    build(0, n - 1, 1);
    sort(a, a + n);
    scanf("%d", &m);
    loop(i, m) {
        int l, r, k;
        scanf("%d%d%d", &l, &r, &k);
        Q[i] = {{k, i}, {l - 1, r - 1}};
    }
    sort(Q, Q + m);
    int ptr = 0;
    loop(i, m) {
        int l = Q[i].second.first, r = Q[i].second.second;
        int k = Q[i].first.first, qind = Q[i].first.second;
        while (ptr < n && a[ptr].first <= k) { 
            upd(0, n - 1, a[ptr].second, 0, 1); 
            ptr++; 
        }
        ans[qind] = query(l, r, 0, n - 1, 1);
    }
    loop(i, m) printf("%d\n", ans[i]);
    return 0;
}