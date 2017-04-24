/*
	UVA 12124 - Assemble
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
const ll INF = 1e12;

map<string, int> type_map;
vector<pair<ll, ll> > v[MXN];
int n, num_types = 0;
ll budget, min_q = INF, max_q = 0;

void reset() {
	type_map.clear();
	num_types = 0;
	for (int i=0; i<MXN; i++) v[i].clear();
}

bool can(int mid) {
	ll tot_price = 0;
	for (int i=0; i<num_types; i++) {
		ll min_price = INF;
		for (int j=0; j<v[i].size(); j++) {
			if (v[i][j].second >= mid) min_price = min(min_price, v[i][j].first);
		}
		tot_price += min_price;
	}
	return tot_price <= budget;
}

int main () {
	ios_base::sync_with_stdio(false);
	int tests;
	cin>>tests;
	for (int test=1; test<=tests; test++) {
		reset();
		cin>>n>>budget;
		for (int i=0; i<n; i++) {
			string type, name;
			ll price, quality;
			cin>>type>>name>>price>>quality;
			if (type_map.count(type) == 0) type_map[type] = num_types++;
			int ty = type_map[type];
			v[ty].push_back(make_pair(price, quality));
			min_q = min(quality, min_q);
			max_q = max(quality, max_q);
		}
		int lo = min_q, hi = max_q, mid;
		while (lo < hi - 1) {
			mid = (lo + hi) / 2;
			if (can(mid)) lo = mid;
			else hi = mid - 1;
		}
		if (can(hi)) cout<<hi<<endl;
		else cout<<lo<<endl;
	}
	return 0;
}