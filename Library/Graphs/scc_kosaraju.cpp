/*
 * Kosaraju's strongly connected components
 * Please watch Tushar Roy's tutorial to understand the algorithm:
 * https://www.youtube.com/watch?v=RpgcYiky7uw
 * 
 * Author: Youssef ElGhareeb
 */

#include <bits/stdc++.h>
using namespace std;

#define loop(i,n) for(int i = 0; i < n; i++)
#define pii pair<int, int>
typedef unsigned long long LL;

class scc_kosaraju {
private:
    vector<vector<int> > g; // input graph
    int n; // number of nodes in graph
    vector<int> vis; // visited array
    stack<int> stk; // stack used by Kosaraju's algorithm
    int num_scc; // number of strongly connected components
    vector<int> component; // vector holding the component that each node belongs to
    
    void dfs(int u) {
        if (vis[u]) return;
        vis[u] = 1;
        for (int v: g[u]) dfs(v);
        stk.push(u);
    }
    
    void dfs2(int u) {
        if (vis[u]) return;
        vis[u] = 1;
        component[u] = num_scc;
        for (int v: g[u]) dfs2(v);
    }
    
    void clear() {
        stk = stack<int>();
        num_scc = 0;
        component = vector<int> (n);
    }
    
    /* Reverse the edges of the graph */
    void reverse_graph() {
        vector<vector<int> > g2(g.size());
        for (int i = 0; i < n; i++) {
            for (int v: g[i]) g2[v].push_back(i);
        }
        g = g2;
    }
    
public:
    // constructor. graph is assumed to be zero based
    scc_kosaraju(vector<vector<int> > _g) {
        g = _g;
        n = g.size();
    }
    
    /* Calculate strongly connected components */
    void calc_scc() {
        clear();
        vis = vector<int>(n, 0);
        loop(i, n) if (!vis[i]) dfs(i);
        reverse_graph();
        vis = vector<int>(n, 0);
        while (!stk.empty()) {
            int u = stk.top();
            stk.pop();
            if (!vis[u]) {
                ++num_scc;
                dfs2(u);
            }
        }
    }
    
    /* Print each node and the component it belongs to */
    void report_components() {
        printf("Number of connected components = %d\n", num_scc);
        loop(i, n) 
            printf("Node %d belongs to component %d\n", i, component[i]);
    }
};

/* Driver main function */
int main() 
{
#ifdef DEBUG
    freopen("in.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    vector<vector<int> > g(n);
    loop(i, m) {
        char u, v;
        cin >> u >> v;
        g[u - 'a'].push_back(v - 'a');
    }
    scc_kosaraju scc(g);
    scc.calc_scc();
    scc.report_components();
    return 0;
} 

/*
Try the following input
11 13
a b
b c
c a
b d
d e
e f
f d
g f
g h
h i
i j
j g
j k
 */