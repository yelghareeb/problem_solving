/*
	Union Find data structure
	Author: Youssef Elghareeb
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

const int N = 2 * 1e5 + 5;

namespace UF {
    int comp[N], sz[N];
    void init() {
        loop(i, N) {
            comp[i] = i;
            sz[i] = 1;
        }
    }
    
    int find(int u) {
        if (u == comp[u]) return u;
        return comp[u] = find(comp[u]);
    }
    
    void merge(int u, int v) {
        u = find(u);
        v = find(v);
        if (u == v) return;
        if (sz[u] > sz[v]) swap(u, v);
        comp[u] = v;
        sz[v] += sz[u];
    }
}

int main() {
#ifdef DEBUG
    freopen("in.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    UF::init();
    printf("Merging (%d, %d)\n", 1, 2);
    UF::merge(1, 2);
    for (int i = 1; i <= 4; i += 1) 
        printf("  Component[%d] = %d\n", i, UF::find(i));
    printf("Merging (%d, %d)\n", 3, 4);
    UF::merge(3, 4);
    for (int i = 1; i <= 4; i += 1) 
        printf("  Component[%d] = %d\n", i, UF::find(i));
    printf("Merging (%d, %d)\n", 1, 3);
    UF::merge(1, 3);
    for (int i = 1; i <= 4; i += 1) 
        printf("  Component[%d] = %d\n", i, UF::find(i));
    return 0;
}