/*
	UVA 820 - Internet Bandwidth
	https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=761
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
      }
      vis = vector<int>(residual.size(), 0);
      path.clear();
    }
    return max_flow;
  }
};

int main () {
  freopen("in.txt", "r", stdin);
  int n, s, t, c;
  vector<vi> network;
  int cnt = 0;
  while (cin >> n && n) {
    cin >> s >> t >> c;
    network = vector<vi>(n);
    for (int i = 0; i < n; i++) network[i] = vi(n, 0);
    for(int j = 0; j < c; j++) {
      int u, v, w;
      cin >> u >> v >> w;
      network[u - 1][v - 1] += w;
      network[v - 1][u - 1] += w;
    }
    Ford_Fulkerson ford(network);
    int ans = ford.get_max_flow(s - 1, t - 1);
    cout << "Network " << cnt + 1 << endl;
    cout << "The bandwidth is " << ans << "." << endl << endl;
    cnt++;
  }
  return 0;
}
