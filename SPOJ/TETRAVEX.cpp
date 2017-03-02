#include <bits/stdc++.h>
using namespace std;

#define loop(i,n) for(int i=0; i<n; i++)
#define pii pair<int, int>
#define ll long long

int a[9][4];

bool check(const vector<int>& v) {
	if (a[v[0]][1] != a[v[1]][3]) return false;
	if (a[v[1]][1] != a[v[2]][3]) return false;

	if (a[v[3]][1] != a[v[4]][3]) return false;
	if (a[v[4]][1] != a[v[5]][3]) return false;

	if (a[v[6]][1] != a[v[7]][3]) return false;
	if (a[v[7]][1] != a[v[8]][3]) return false;

	if (a[v[0]][2] != a[v[3]][0]) return false;
	if (a[v[3]][2] != a[v[6]][0]) return false;

	if (a[v[1]][2] != a[v[4]][0]) return false;
	if (a[v[4]][2] != a[v[7]][0]) return false;

	if (a[v[2]][2] != a[v[5]][0]) return false;
	if (a[v[5]][2] != a[v[8]][0]) return false;

	return true;
}

int main() {
	int tests;
	cin>>tests;
	loop(test, tests) {
		loop(i, 9) 
			loop (j, 4)
				cin>>a[i][j];
		vector<int> v(9);
		loop(i, 9) v[i] = i;
		bool flag = false;
		do {
			if (check(v)) {
				flag = true;
				break;
			}
		} while (next_permutation(v.begin(), v.end()));
		cout<<"Case "<<test + 1<<": ";
		if (flag) cout<<"YES\n";
		else cout<<"NO\n";
	}
	return 0;
}