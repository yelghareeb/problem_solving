/*
	Live Archive 4445
	Author: Youssef ElGhareeb
*/

#include <bits/stdc++.h>
using namespace std;

pair<double, double> v[10];
int n;
const double EPS = 0.000000001;

bool can(double mid) {
	bool flag = true;
	double latest = v[0].first;
	for (int i = 1; i < n; i++) {
		if (v[i].second - latest < mid) {
			flag = false;
			break;
		}
		latest = max(latest + mid, v[i].first);
	}
	return flag;
}

int main () {
	ios_base::sync_with_stdio(false);
	int test_case = 0;
	while (cin >> n && n) {
		for (int i = 0; i < n; i++) {
			cin >> v[i].first >> v[i].second;
			v[i].first *= 60;
			v[i].second *= 60;
		}
		sort (v, v + n);
		double res = 0;
		do {
			double lo = 0, hi = 1500 * 60, mid;
			while (hi - lo > EPS) {
				mid = (lo + hi) / 2;
				bool flag = can(mid);
				if (flag) lo = mid;
				else hi = mid;
			}
			res = max(res, hi);
		} while (next_permutation(v, v + n));
		cout << "Case " << ++test_case << ": " << (int)(res + 0.5) / 60 << ":" << std::setw(2) << std::setfill('0') << (int)(res + 0.5) % 60 << endl;
	}
	return 0;
}