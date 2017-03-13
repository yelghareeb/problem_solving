/*
	Author: Youssef ElGhareeb
	Idea: DP
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <cstring>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <map>
#include <assert.h>
 
using namespace std;
 
#define ll long long
#define vi vector<int>
#define pb push_back
#define loop(i,n) for(int i=0; i<n; i++)
#define pii pair<int, int>
#define mp make_pair
#define ABS(i) i<0?-i:i

const double EPS = 0.00000000001;
const int MXN = 55;
int n, m, a[MXN];
double dp[MXN][MXN][MXN][2];
int vis[MXN][MXN][MXN][2];
double FRAC[MXN][MXN][MXN];
ll NCR[MXN][MXN];

void init () {
	NCR[0][0] = 1;
	NCR[1][1] = NCR[1][0] = 1;
	for (int i=2; i<MXN; i++) {
		NCR[i][0] = 1;
		for (int j = 1; j<MXN; j++) {
			NCR[i][j] = NCR[i-1][j] + NCR[i-1][j-1];
		}
	}
	
	for (int num=1; num<MXN; num++) { 
		for (int den = num; den < MXN; den++) {
			FRAC[num][den][0] = 1;
			for(int pwr = 1; pwr < MXN; pwr++) {
				FRAC[num][den][pwr] = FRAC[num][den][pwr - 1] * num * 1.0 / den;
			}
		}
	}
	
}

double calc(int ind, int rem, int mx, int fl) {
	if(ind == m) {
		/* Terminating condition */
		if (fl && !rem) {
			return 1.0;
		}
		return 0;
	}
	if(vis[ind][rem][mx][fl]) return dp[ind][rem][mx][fl];
	vis[ind][rem][mx][fl] = 1;
	double& res = dp[ind][rem][mx][fl];
	res = 0;
	
	loop(i, rem + 1) {
		int cur_cnt = i % a[ind] == 0? i / a[ind]: i / a[ind] + 1;
		if(cur_cnt > mx) break;
		double val = 1.0;
		if(cur_cnt == mx) val *= calc(ind + 1, rem - i, mx, 1);
		else val *= calc(ind + 1, rem - i, mx, fl);
		val *= NCR[rem][i];
		if (i > 0) val *= FRAC[1][m - ind][i];
		if (rem - i > 0) val *= FRAC[m - ind - 1][m-ind][rem - i];
		res += val;	
	}
	return dp[ind][rem][mx][fl] = res;
}

int main() {
	init();
	cin>>n>>m;
	loop(i, m) cin>>a[i];
	memset(dp, -1, sizeof(dp));
	double ans = 0;
	for(int i=1; i<=n; i++) {
		ans += (double) i * calc(0, n, i, 0);
	}
	printf("%.17f\n", ans);
	return 0;
}