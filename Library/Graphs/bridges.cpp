/* Implementation of Tarjan's algorithm for finding 
   articulation points and bridges in an undirected graph
   
   Author: Youssef Elghareeb
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
#define loop(i,n) for(int i = 0; i < n; i++)
#define pii pair<LL, int>
#define vi vector<int> 
#define pb push_back

const int MX = 3 * 1e5 + 5;
const int INF = 2 * 1e9 + 5;

class UGraphBridgesAP {
    #define UNVISITED -1

    int dfs_cntr;
    vector<int> dfs_num;
    vector<int> dfs_low;
    vector<int> dfs_parent;
    vector<int> articulation_point;
    vector<vector<int> > g;
    int n; // number of nodes
    int dfs_root;
    int root_children;
    set<pair<int, int> > bridges;
    
    void recurse(int u) {
        dfs_low[u] = dfs_num[u] = dfs_cntr++;
        for (int v: g[u]) {
            if (dfs_num[v] == UNVISITED) {
                dfs_parent[v] = u;
                if (u == dfs_root) root_children++;
                recurse(v);
                if (dfs_low[v] >= dfs_num[u]) articulation_point[u] = 1;
                if (dfs_low[v] > dfs_num[u]) bridges.insert({min(u, v), max(u, v)});
                dfs_low[u] = min(dfs_low[u], dfs_low[v]);
            }
            else if (v != dfs_parent[u]) dfs_low[u] = min(dfs_low[u], dfs_num[v]);
        }
    }
    
public:
    UGraphBridgesAP (vector<vector<int> > _g) {
        g = _g;
        n = g.size();
        dfs_cntr = 0;
        dfs_num.assign(n + 5, UNVISITED);
        dfs_low.assign(n + 5, 0);
        dfs_parent.assign(n + 5, 0);
        articulation_point.assign(n + 5, 0);
    }
    
    void process() {
        for (int i = 0; i < n; i++) {
            if (dfs_num[i] == UNVISITED) {
                dfs_root = i;
                root_children = 0;
                recurse(i);
                articulation_point[dfs_root] = (root_children > 1); 
            }
        }
    }
    
    bool is_bridge(int u, int v) {
        if (u > v) swap(u, v);
        return (bridges.find({u, v}) != bridges.end());
    }
    
    bool is_articulation_point(int u) {
        return articulation_point[u];
    }
};