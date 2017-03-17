/*
	UVA 11488
	Author: Youssef ElGhareeb
*/

#include <iostream>
#include <cmath>
#include <string>
#include <assert.h>
#include <sstream>
#include <map>
#include <algorithm>
#include <vector>

using namespace std;

#define ll unsigned long long
#define vi vector<int>
#define pb push_back
#define loop(i,n) for(int i=0; i<n; i++)
#define pii pair<int, int>
#define mp make_pair

const int MXS = 5 * 1e4 + 5;
const int MX_LEN = 205;

int n; // Number of strings
int res;
string s[MXS];

void solve(int ind, vector<int>& v) {
	if (v.size() == 1) {
		res = max(res, (int)s[v[0]].length());
		return;
	}

	vector<int> v_0, v_1;
	for (int i=0; i<v.size(); i++) {
		int string_ind = v[i];
		if (ind >= s[string_ind].size()) continue;
		if (s[string_ind][ind] == '0') v_0.push_back(string_ind);
		else v_1.push_back(string_ind);
	}
	res = max(res, (ind + 1) * (int)max(v_0.size(), v_1.size()));
	if(!v_0.empty()) solve(ind + 1, v_0);
	if(!v_1.empty()) solve(ind + 1, v_1);
}

int main() {
	ios_base::sync_with_stdio(false);
	int tests;
	cin>>tests;
	for (int t=0; t<tests; t++) {
		cin>>n;
		for (int i=0; i<n; i++) cin>>s[i];
		vector<int> v(n);
		for(int i=0; i<n; i++) v[i] = i;
		res = 0;
		solve(0, v);
		cout<<res<<endl;
	}
    return 0;
}   