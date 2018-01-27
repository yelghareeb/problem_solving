/*
	UVA 1211 - Atomic Car Race
	https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3652
	Idea: DP
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
#include <unordered_map>
#include <iomanip>

using namespace std;

typedef long long LL;
typedef vector<LL> vi;
typedef pair<int, int> pii;
#define mp make_pair
#define pb push_back
#define loop(i,n) for(int i = 0; i < n; i++)
#define itr iterator

const int N = 2 * 1e4 + 50;
const double INF = 1e12;

int main () {
  int n, a[105], r;
  double v, e, b, f, dist[N], dp[105];
  while (cin >> n) {
    if (!n) break;
    loop(i, n) cin >> a[i];
    cin >> b >> r >> v >> e >> f;
    if(r == 0) dist[1] = 1.0 / (v + e * r);
    else dist[1] = 1.0 / (v - f * r);
    for(int i = 2; i < N; i++) {
      dist[i] = dist[i - 1];
      if (i - 1 >= r) dist[i] += 1.0 / (v - e * (i - 1 - r));
      else dist[i] += 1.0 / (v - f * (r - i + 1));
    }
    dp[0] = dist[a[0]] + b;
    for (int i = 1; i < n; i++) {
      dp[i] = dist[a[i]];
      loop(j, i) dp[i] = min(dp[i], dp[j] + dist[a[i] - a[j]]);
      dp[i] += b;
    }
    printf("%.4f\n", dp[n - 1] - b);
  }
  return 0;
}