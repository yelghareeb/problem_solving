/*
	UVA 1362 - Exploring pyramids
	Author: Youssef ElGhareeb
*/

#include <bits/stdc++.h>
using namespace std;

#define mp make_pair
#define loop(i,n) for(int i=0; i<n; i++)
#define pii pair<int,int>
#define ll long long
#define ld long double

string s;
ll dp[305][305];
const int MOD = 1e9;

ll solve(int start, int end) {
	if (s[start] != s[end]) return 0;
	if (start == end) return 1;
	if (end - start == 2) return 1;
	if (end - start < 2) return 0;
	if (dp[start][end] != -1) return dp[start][end];
	ll res = 0;
	for (int i=start+1; i < end; i++) {
		if (s[i] == s[start]) {
			res += (solve(start + 1, i - 1) * solve(i, end));
			res %= MOD;
		}
	}
	res += solve(start + 1, end - 1);
	res %= MOD;
	return dp[start][end] = res;
}

int main () {
	ios_base::sync_with_stdio(false);
	while (cin>>s) {
		memset(dp, -1, sizeof(dp));
		int ans = solve(0, s.length() - 1);
		cout<<ans<<endl;
	}
	return 0;
}