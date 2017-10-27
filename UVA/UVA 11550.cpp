/*
	UVA 11550 - Demanding Dilemma
	Author: Youssef ElGhareeb
*/

#include <bits/stdc++.h>
using namespace std;

#define mp make_pair
#define loop(i,n) for(int i=0; i<n; i++)
#define pii pair<int,int>
#define ll long long
#define ld long double

const int MXN = 1005;

int main () {
	ios_base::sync_with_stdio(false);
	int tests;
	cin>>tests;
	for (int test=1; test<=tests; test++) {
		int n, m;
		cin>>n>>m;
		int M[10][100];
		for (int i=0; i<n; i++) {
			for (int j=0; j<m; j++) {
				cin>>M[i][j];
			}
		}
		bool flag = true;
		int connected[10][10];
		memset(connected, 0, sizeof(connected));
		for (int j=0; j<m && flag; j++) {
			int cnt = 0;
			int con1 = -1, con2 = -1;
			for (int i=0; i<n; i++) {
				if (M[i][j] == 1) {
					if (con1 == -1) con1 = i;
					else con2 = i;
					cnt++;
				}
			}
			if (cnt != 2) flag = false;
			else {
				if (connected[con1][con2]) flag = false;
				connected[con1][con2] = connected[con2][con1] = 1;
			}
		}
		if (flag) cout<<"Yes\n";
		else cout<<"No\n";
	}
	return 0;
}