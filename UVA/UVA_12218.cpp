#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <sstream>
#include <queue>
using namespace std;

#define loop(i,n) for(int i=0; i<n; i++)
#define ll long long
#define pii pair<int, int>
#define pb push_back

const int MXN = 1e7 + 5;
int primes[MXN];
map<string, int> cnt_primes;

void add_to_map(int u) {
	string s;
	while (u > 0) {
		s += '0' + (u % 10);
		u /= 10;
	}
	sort(s.begin(), s.end());
	cnt_primes[s]++;
}

void sieve() {
	loop(i, MXN) primes[i] = 1; // Everything is initially prime
	for (int i=2; i<MXN; i++) {
		if (!primes[i]) continue;
		add_to_map(i);
		for (int j = i + i; j<MXN; j+=i) primes[j] = 0;
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	sieve();
	int tests;
	cin>>tests;
	loop(test, tests) {
		string s;
		cin>>s;
		int res = 0;
		map<string, int> vis;
		loop(i, 1<<s.length()) {
			string digits;
			loop(j, s.length()) {
				if ( (i >> j) & 1) {
					digits += s[j];
				}
			}
			sort(digits.begin(), digits.end());
			if (vis.count(digits) > 0) continue;
			vis[digits] = 1;
			res += cnt_primes[digits];
		}
		cout<<res<<endl;
	}
	return 0;
}