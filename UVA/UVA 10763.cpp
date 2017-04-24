/*
	UVA 10763 - Foreign Exchange
	Author: Youssef ElGhareeb
*/

#include <bits/stdc++.h>
using namespace std;

#define mp make_pair
#define loop(i,n) for(int i=0; i<n; i++)
#define pii pair<int,int>
#define ll long long
#define ld long double

int main () {
	ios_base::sync_with_stdio(false);
	int n;
	while (cin>>n && n) {
		map<pii, int> M;
		for (int i=0; i<n; i++) {
			int f, t;
			cin>>f>>t;
			M[mp(f, t)]++;
		}
		bool flag = true;
		for (map<pii,int>::iterator it = M.begin(); it!=M.end() && flag; it++) {
			pii rev = mp(it->first.second, it->first.first);
			if (M[rev] != it->second) flag = false;
		}
		if (flag) cout<<"YES\n";
		else cout<<"NO\n";
	}
	return 0;
}