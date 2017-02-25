/*
	UVA 10859
	Author: Youssef ElGhareeb
	
	Idea: DP
	The graph is a set of trees (forest)
	for each tree, consider the following 2 cases:
		- setting the root node's light to 0
			- In this case, all the children of the root should be lighted
		- setting the root node's light to 1
			- There are 2 cases for each child in this situation:
				1. Light the child. This option will increase the number of roads lit by 2 lampposts by 1
				2. Don't light the child
*/

#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define vi vector<int>
#define pb push_back
#define loop(i,n) for(int i=0; i<n; i++)
#define pii pair<int, int>

const int MXN = 1e3 + 5;
const int INF = 1e9 + 7;

int n, m;
vector<int>g[MXN];
int vis[MXN];
pii dp[MXN][2];

pii solve(int u, int pa, int f) {
    if (dp[u][f].first != -1) return dp[u][f];
    vis[u] = 1;
    pii res = make_pair(0, 0);
    loop(j, g[u].size()) {
        int v = g[u][j];
        if (v == pa) continue;
        pii child0 = solve(v, u, 0);
        pii child1 = solve(v, u, 1);
        if (f == 0) {
            res.first += child1.first;
            res.second += child1.second;
        }
        else {
            res.first += min(child0.first, child1.first);
            if (child0.first == child1.first) res.second += max(child0.second, child1.second + 1);
            else if (child0.first < child1.first) res.second += child0.second;
            else res.second += child1.second + 1;
        }
    }
    if (f == 1) res.first++;
    return dp[u][f] = res;
}

int main () {
    ios_base::sync_with_stdio(false);
    int tests;
    cin>>tests;
    loop(test, tests) {
        memset(vis, 0, sizeof(vis));
        loop(i, MXN) loop(j, 2) dp[i][j] = make_pair(-1, -1);
        loop(i, MXN) g[i].clear();
        cin>>n>>m;
        loop(i, m) {
            int u, v;
            cin>>u>>v;
            g[u].pb(v);
            g[v].pb(u);
        }
        int ml = 0;
        int mr = 0;
        loop(i, n) {
            if (vis[i]) continue;
            pii p1 = solve(i, -1, 0);
            pii p2 = solve(i, -1, 1);
            if (p1.first < p2.first) {
                ml += p1.first;
                mr += p1.second;
            }
            else if (p1.first == p2.first) {
                ml += p1.first;
                mr += max(p1.second, p2.second);
            }
            else {
                ml += p2.first;
                mr += p2.second;
            }
        }
        cout<<ml<<" "<<mr<<" "<<m - mr<<endl;
    }
    return 0;
}