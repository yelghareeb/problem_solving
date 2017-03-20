/*
	UVA 10765
	Author: Youssef ElGhareeb
	
	Idea:
	Use the standard Tarjan's algorithm to find the articulation points in the graph, 
	just add the following tweak: whenever you detect an articulation point, increment a count for the current vertex. 
	The answer for each vertex is its count + the number of components in the graph. 

*/

#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define vi vector<int>
#define pb push_back
#define loop(i,n) for(int i=0; i<n; i++)
#define pii pair<int, int>
#define mp make_pair

const int MXN = 1e4 + 5;
int n, m;
vector<int> g[MXN];

int dfs_number_counter = 0;
int dfs_num[MXN], dfs_low[MXN], dfs_parent[MXN], cnt_comps[MXN];

int root_children = 0, dfs_root = 0;

void articulation_point(int u) {
    dfs_num[u] = dfs_low[u] = dfs_number_counter++;
    loop(j, g[u].size()) {
        int v = g[u][j];
        if (dfs_num[v] == -1) { // If this node is unvisited
            dfs_parent[v] = u;
            if (u == dfs_root) root_children++;
            articulation_point(v);
            
            if (dfs_low[v] >= dfs_num[u]) cnt_comps[u]++;
            
            dfs_low[u] = min(dfs_low[u], dfs_low[v]);
        }
        else if (v != dfs_parent[u]) {
            dfs_low[u] = min(dfs_low[u], dfs_num[v]);
        }
    }
}

bool compare (pii& p1, pii& p2) {
    if (p1.second == p2.second) return p1.first < p2.first;
    return p1.second > p2.second;
}

int main() {
    ios_base::sync_with_stdio(false);
    while (cin>>n>>m && (n || m)) {
        dfs_number_counter = 0;
        loop(i, n) g[i].clear();
        while(true) {
            int x, y;
            cin>>x>>y;
            if (x == -1 && y == -1) break;
            g[x].push_back(y);
            g[y].push_back(x);
        }
        memset(dfs_num, -1, sizeof(dfs_num));
        memset(cnt_comps, 0, sizeof(cnt_comps));
        int num_components = 0;
        for (int i=0; i<n; i++) {
            if (dfs_num[i] == -1) { // Unvisited node
                dfs_root = i;
                root_children = 0;
                articulation_point(i);
                cnt_comps[i] = root_children - 1;
                num_components++;
            }
        }
        vector<pair<int, int> > v(n);
        for (int i=0; i<n; i++) v[i] = make_pair(i, cnt_comps[i] + num_components);
        sort(v.begin(), v.end(), compare);
        for (int i=0; i<m; i++) cout<<v[i].first<<" "<<v[i].second<<endl;
        cout<<endl;
    }
    return 0;
}   