#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <sstream>
#include <queue>
#include <cstring>
using namespace std;

#define loop(i,n) for(int i=0; i<n; i++)
#define ll long long
#define pii pair<int, int>
#define pb push_back

const int MXN = 50;
const int INF = 1e9 + 7;
int t1, t2;
int n, m[MXN];
int c[2][MXN][MXN];
int dp[305][305][MXN];
int best[305][MXN];

int get_best1(int rem1, int rem2, int pos) {
	if (rem1 < 0 || rem2 < 0) return INF;
	if (dp[rem1][rem2][pos] != -1) return dp[rem1][rem2][pos];
	if(pos == n) {
		if (rem1 == 0 && rem2 == 0) return 0;
		return INF;
	}
	int res = INF;
	loop(k, m[pos] + 1) {
		int q1 = k;
		int q2 = m[pos] - k;
		int val = c[0][pos][q1] + c[1][pos][q2] + get_best1(rem1 - q1, rem2 - q2, pos + 1);
		if (val < res) {
			res = val;
			best[rem1][pos] = k;
		}
	}
	return dp[rem1][rem2][pos] = res;
}

int main() {
	ios_base::sync_with_stdio(false);
	while (cin>>t1>>t2) {
		if (!t1 && !t2) break;
		cin>>n;
		loop(i, n) {
			cin>>m[i];
			loop(j, m[i]) cin>>c[0][i][j + 1];
			loop(j, m[i]) cin>>c[1][i][j + 1];
		}
		memset(dp, -1, sizeof(dp));
		int val1 = get_best1(t1, t2, 0);
		cout<<val1<<endl;
		cout<<best[t1][0];
		for (int i=1; i<n; i++) {
			t1 -= best[t1][i-1];
			cout<<" "<<best[t1][i];
		}
		cout<<endl;
		cout<<endl;
	}
	return 0;
}