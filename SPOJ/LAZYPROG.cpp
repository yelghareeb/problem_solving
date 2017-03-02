#include <bits/stdc++.h>
using namespace std;

#define loop(i,n) for(int i=0; i<n; i++)
#define pii pair<int, int>
#define ll long long

int main() {
	int tests;
	scanf("%d", &tests);
	loop(test, tests) {
		int n;
		scanf("%d", &n);
		long double res = 0;
		vector<pair<int, pii> > v(n);
		loop(i, n) {
			ll a, b, d;
			scanf("%lld%lld%lld", &a, &b, &d);
			v[i] = make_pair(d, make_pair(a, b));
		}
		sort(v.begin(), v.end()); // sort according to deadlines
		priority_queue<pair<int, int> > pq;
		ll current_time = 0;
		loop(i, n) {
			ll a, b, d;
			d = v[i].first;
			a = v[i].second.first;
			b = v[i].second.second;
			pq.push(make_pair(a, b));
			ll slack = d - current_time; // Available time
			if (b <= slack) {
				current_time += b;
			}
			else {
				current_time = d;
				ll spare = b - slack; // We need to save "spare" minutes
				while (true) {
					pair<int, int> front = pq.top();
					pq.pop();
					a = front.first;
					ll rem = front.second;
					if (rem >= spare) {
						res += (double) spare / a;
						if (rem > spare) pq.push(make_pair(a, rem - spare));
						break;
					}
					else {
						res += (double) rem / a;
					}
					spare -= rem;
				}
			}
		}
		printf("%.2Lf\n", res);
	}
	return 0;
}