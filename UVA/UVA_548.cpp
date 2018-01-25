/*
	UVA 548 - Tree
	https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=489
	
	Idea: construct a tree from inorder/postorder traversals
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
#include <sstream>

using namespace std;

typedef long long LL;
typedef vector<int> vi;
#define loop(i,n) for(int i = 0; i < n; i++)

const int N = 1e4 + 10;
const LL INF = 1e13;

vi in, post;
vector<vi> g;
int idx[N];
LL ans, node;

void add_edge(int u, int v) {
  g[u].push_back(v);
  g[v].push_back(u);
}

int solve(int s1, int e1, int s2, int e2) {
  if (s1 > e1) return -1;
  int root = post[e2];
  if (s1 == e1) return root;
  int pos = idx[root];
  int left = solve(s1, pos - 1, s2, s2 + pos - 1 - s1);
  int right = solve(pos + 1, e1, s2 + pos - s1, e2 - 1);
  if (left != -1) add_edge(root, left);
  if (right != -1) add_edge(root, right);
  return root;
}

void dfs(int u, int pa, LL s) {
  if (g[u].empty() || (g[u].size() == 1 && g[u][0] == pa)) {
    if (s + u < ans) {
      ans = s + u;
      node = u;
    }
    else if (s + u == ans) {
      node = min((int)node, u);
    }
    return;
  }
  for(int j = 0; j < g[u].size(); j++) {
    int v = g[u][j];
    if (v == pa) continue;
    dfs(v, u, s + u);
  }
}

int main () {
  freopen("in.txt", "r", stdin);
  string line;
  while (getline(cin, line)) {
    in.clear();
    post.clear();
    istringstream is;
    is.str(line);
    int val, cntr = 0;
    while (is >> val) {
      in.push_back(val);
      idx[val] = cntr++;
    }
    getline(cin, line);
    is = istringstream(line);
    while (is >> val) post.push_back(val);
    g = vector<vi>(N);
    int root = solve(0, in.size() - 1, 0, in.size() - 1);
    ans = INF;
    node = 1000005;
    dfs(root, -1, 0);
    cout << node << endl;
  }
  return 0;
}
