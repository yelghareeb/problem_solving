/*
	UVA 10891 - Game of Sum
	https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1832
	Idea: Dynamic Programming
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

const int N = 100 + 50;
const int INF = 1e9;

int n, a[N], dp[N][N];

int solve(int l, int r) {
  if (l > r) return 0;
  if (l == r) return a[l];
  int& res = dp[l][r];
  if (res != -INF) return res;
  int s = 0;
  for(int i = l; i <= r; i++) {
    s += a[i];
    res = max(res, s - solve(i + 1, r));
  }
  s = 0;
  for (int i = r; i >= l; i--) {
    s += a[i];
    res = max(res, s - solve(l, i - 1));
  }
  return res;
}

int main () {
  while(cin >> n && n) {
    loop(i, n) cin >> a[i];
    loop(i, n) loop(j, n) dp[i][j] = -INF;
    cout << solve(0, n - 1) << endl;
  }
  return 0;
}