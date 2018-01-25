/*
	UVA 11022 - String Factoring
	https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1963
	Idea: Strings - DP
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

const int N = 100;
const LL INF = 1e13;

string s;
int dp[N][N];

int solve(int b, int e) {
  if (b == e) return 1;
  int& res = dp[b][e];
  if (res != -1) return res;
  res = e - b + 1;
  int len = res;
  for (int exp = 2; exp <= len; exp++) {
    if (len % exp == 0) {
      int one_len = len / exp;
      bool ok = true;
      for (int j = 0; j < one_len && ok; j++) {
        for (int k = 0; k < exp; k++) {
          if (s[b + j + k * one_len] != s[b + j]) {
            ok = false;
            break;
          }
        }
      }
      if (ok) res = min(res, solve(b, b + one_len - 1));
    }
  }
  for (int j = b; j < e; j++) {
    res = min(res, solve(b, j) + solve(j + 1, e));
  }
  return res;
}

int main () {
  while (cin >> s) {
    if (s == "*") break;
    memset(dp, -1, sizeof(dp));
    cout << solve(0, s.length() - 1) << endl;
  }
  return 0;
}
