/*
	UVA 10361
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

int main () {
	int n;
	cin>>n;
	string s;
	getline(cin, s); // Dummy read
	for (int i=0; i<n; i++) {
		string s1, s2;
		getline(cin, s1);
		getline(cin, s2);
		s = "";
		vector<string> v1;
		for (int i=0; i<s1.length(); i++) {
			if (s1[i] == '<') {
				v1.push_back(s);
				s = "";
			}
			else if (s1[i] == '>') {
				v1.push_back(s);
				s = "";
			}
			else {
				s += s1[i];
			}
		}
		v1.push_back(s);
		cout<<v1[0]<<v1[1]<<v1[2]<<v1[3]<<v1[4]<<endl;
		if (s2[s2.length() - 1] == '\r') s2 = s2.substr(0, s2.length() - 1);
		s2 = s2.substr(0, s2.length() - 3); // remove the 3 dots
		s2 += v1[3] + v1[2] + v1[1] + v1[4];
		cout<<s2<<endl;
	}
	return 0;
}