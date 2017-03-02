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

const int MXN = 2 * 1e6 + 5;
const int INF = 1e9 + 7;

int a[MXN], n;

int main() {
	ios_base::sync_with_stdio(false);
	while (cin>>n && n) {
		loop(i, n) cin>>a[i];
		loop(i, n) a[i + n] = a[i];
		ll s = 0;
		int ans = 0;
		for (int i=2*n - 1; i>=0; i--) {
			s += a[i];
			if (s >= 0) {
				if (i < n) ans++;
				s = 0;
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}