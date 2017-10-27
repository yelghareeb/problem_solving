/*
	UVA 10062
	Author: Youssef ElGhareeb
*/

#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define vi vector<int>
#define pb push_back
#define loop(i,n) for(int i=0; i<n; i++)
#define pii pair<int, int>
#define pdd pair<double, double>

bool comp(pii first, pii second) {
	if (first.second == second.second) {
		return first.first > second.first;
	}
	return first.second < second.second;
}

int main () {
	string s;
	bool first = true;
	while (getline(cin, s)) {
		if (!first) cout<<endl;
		first = false;
		map<int, int> mp;
		for (int i=0; i<s.length(); i++) {
			if (s[i] == '\r' || s[i] == '\n') continue;
			mp[s[i]]++;
		}
		vector<pair<int, int> > freqs;
		for (map<int, int>::iterator it = mp.begin(); it!=mp.end(); it++) {
			freqs.push_back(make_pair(it->first, it->second));
		}
		sort(freqs.begin(), freqs.end(), comp);
		for (int i=0; i<freqs.size(); i++) {
			cout<<freqs[i].first<<" "<<freqs[i].second<<endl;
		}
	}
	return 0;
}