/*
	UVA 10635 - Prince and Princess
	https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1576
	Idea - Longest common subsequence in O(nlogn) using segment tree
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

const int N = 300 * 300;
const LL INF = 1e13;

vi v1, v2, c;
int tree[1000010];

void modify(int l, int r, int pos, int id, int val) {
  if (l == r) {
    tree[id] = val;
    return;
  }
  int mid = (l + r) / 2;
  if (pos <= mid) modify(l, mid, pos, id * 2, val);
  else modify(mid + 1, r, pos, id * 2 + 1, val);
  tree[id] = max(tree[id * 2], tree[id * 2 + 1]);
}

int query(int x, int y, int l, int r, int id) {
  if (l >= x && r <= y) return tree[id];
  if (y < l || x > r) return 0;
  int mid = (l + r) / 2;
  return max(query(x, y, l, mid, id * 2), query(x, y, mid + 1, r, id * 2 + 1));
}

int main () {
  int t;
  cin >> t;
  for (int test = 1; test <= t; test++) {
    int n, p, q;
    cin >> n >> p >> q;
    v1 = vi(p + 1);
    v2 = vi(q + 1);
    map<int, int> pos;
    for (int i = 0; i < p + 1; i++) {
      cin >> v1[i];
      pos[v1[i]] = i;
    }
    c.clear();
    for (int i = 0; i < q + 1; i++) {
      cin >> v2[i];
      if (pos.count(v2[i])) {
        c.push_back(pos[v2[i]]);
      }
    }
    memset(tree, 0, sizeof(tree));
    int ans = 0;
    for (int i = 0; i < c.size(); i++) {
      int best = query(0, c[i] - 1, 0, N, 1);
      ans = max(ans, 1 + best);
      modify(0, N, c[i], 1, 1 + best);
    }
    cout << "Case " << test << ": " << ans << endl;
  }
  return 0;
}
