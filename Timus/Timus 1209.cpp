/*
	Timus 1209
	Author: Youssef ElGhareeb
*/

#include <bits/stdc++.h>
using namespace std;

#define mp make_pair
#define loop(i,n) for(int i=0; i<n; i++)
#define pii pair<int,int>
#define ll long long
#define ld long double

ll f[1000000];

int main () {
	ios_base::sync_with_stdio(false);
	int n;
	cin>>n;
	f[0] = 1;
	int cnt = 0;
	set<ll> S;
	S.insert(1);
	for (int i = 0; f[i] < (1ll << 31); i++, cnt++) {
		f[i+1] = (i + 1) + f[i];
		S.insert(f[i+1]);
	}
	for (int i=0; i<n; i++) {
		int v;
		cin>>v;
		if (S.find(v) != S.end()) cout<<1;
		else cout<<0;
		if (i < n-1) cout<<" ";
	}
	cout<<endl;
	return 0;
}