/*
	UVA 10092 - The Problem with the Problem Setter
	https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1033
	
	Network Flows
	Author: Youssef Elghareeb
*/

#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <map>
#include <queue>
#include <stack>
#include <assert.h>
#include <cstring>
#include <algorithm>
#include <climits>

using namespace std;

typedef long long LL;
typedef vector<int> vi;
const int N = 2 * 1e2 + 10;
const int INF = 1e9;

class Ford_Fulkerson {
  // Pass an adjacency matrix to this class
  vector<vi> residual;
  vector<vi> network;
  vi path, vis;
  set<pair<int, int> > edges;
  int get_path(int src, int sink, int min_cost = INT_MAX) {
    path.push_back(src);
    if (src == sink) {
      return min_cost;
    }
    int res = 0;
    vis[src] = 1;
    for (int j = 0; j < residual.size(); j++) {
      if (vis[j] || residual[src][j] <= 0) continue;
      res = get_path(j, sink, min(min_cost, residual[src][j]));
      if (res) break;
      else path.pop_back();
    }
    return res;
  }
public:
  Ford_Fulkerson(vector<vi> network) {
    this->network = network;
  }
  int get_max_flow(int src, int sink) {
    residual = network;
    int max_flow = 0, cur_flow;
    vis = vector<int>(residual.size(), 0);
    while ((cur_flow = get_path(src, sink))) {
      max_flow += cur_flow;
      for (int i = 0; i < path.size() - 1; i++) {
        int u = path[i];
        int v = path[i + 1];
        residual[u][v] -= cur_flow;
        residual[v][u] += cur_flow;
        edges.insert(make_pair(u, v));
        edges.erase(make_pair(v, u));
      }
      vis = vector<int>(residual.size(), 0);
      path.clear();
    }
    return max_flow;
  }
  vi get_rel(int node) {
    vi res;
    for (int j = 0; j < network.size(); j++) {
      if (edges.count(make_pair(j, node))) res.push_back(j);
    }
    return res;
  }
};

int main () {
  freopen("in.txt", "r", stdin);
  int nk, np;
  while (cin >> nk >> np) {
    if (!nk && !np) break;
    int tot_req = 0, all = nk + np + 2;
    vector<vi> network(all);
    for (int i = 0; i < nk + np + 2; i++) network[i] = vi(all, 0);
    for (int i = 0; i < nk; i++) {
      int val;
      cin >> val;
      tot_req += val;
      network[1 + np + i][all - 1] = val;
    }
    for (int i = 0; i < np; i++) {
      int cnt;
      cin >> cnt;
      for (int j = 0; j < cnt; j++) {
        int cat;
        cin >> cat;
        network[i + 1][1 + np + cat - 1] = 1;
      }
    }
    for(int i = 1; i <= np; i++) network[0][i] = 1;
    Ford_Fulkerson ford(network);
    int flow = ford.get_max_flow(0, all - 1);
    if (flow == tot_req) {
      cout << 1 << endl;
      for (int i = 0; i < nk; i++) {
        vi problems = ford.get_rel(i + 1 + np);
        if (!problems.empty()) cout << problems[0];
        for (int j = 1; j < problems.size(); j++) cout << " " << problems[j];
        cout << endl;
      }
    }
    else cout << 0 << endl;
  }
  return 0;
}
