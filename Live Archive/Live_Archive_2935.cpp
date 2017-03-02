#include <bits/stdc++.h>
using namespace std;

#define loop(i,n) for(int i=0; i<n; i++)

string solve(string& s, int& ind) {
	if (s[ind] == '1') {
		ind++;
		return "0";
	}
	string res = "";
	vector<string> v;
	int child_cnt = 0;
	while (s[ind] == '0') {
		++ind;
		string cur = solve(s, ind);
		v.push_back(cur);
		child_cnt++;
	}
	++ind;
	sort(v.begin(), v.end());
	ostringstream os;
	os<<child_cnt;
	res = os.str();
	loop(i, v.size()) res += v[i];
	return res;
}

int main() {
	ios_base::sync_with_stdio(false);
	int tests;
	cin>>tests;
	loop(test, tests) {
		string s1, s2;
		cin>>s1>>s2;
		int pos = 0;
		string h1 = solve(s1, pos);
		pos = 0;
		string h2 = solve(s2, pos);
		if (h1 == h2) cout<<"same\n";
		else cout<<"different\n";
	}
	return 0;
}