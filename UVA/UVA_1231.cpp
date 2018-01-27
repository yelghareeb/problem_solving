/*
	UVA 1231 - Acorn
	https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3672
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

const int N = 2005 + 50;
const double INF = 1e12;

int dp[N][N], ow[N][N], mx[N];

int main () {
  freopen("in.txt", "r", stdin);
  int t;
  cin >> t;
  while (t--) {
    int t, h, f;
    cin >> t >> h >> f;
    memset(dp, 0, sizeof(dp));
    memset(ow, 0, sizeof(ow));
    memset(mx, 0, sizeof(mx));
    loop(i, t) {
      int num, ch;
      cin >> num;
      loop(j, num) {
        cin >> ch;
        ow[ch][i]++;
      }
    }
    loop(i, h + 1) {
      loop(j, t) {
        if (i > 0) dp[i][j] = max(dp[i][j], dp[i - 1][j]);
        if (i >= f) dp[i][j] = max(dp[i][j], mx[i - f]);
        dp[i][j] += ow[i][j];
        mx[i] = max(mx[i], dp[i][j]);
      }
    }
    cout << mx[h] << endl;
  }
  return 0;
}