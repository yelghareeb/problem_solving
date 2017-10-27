/*
	UVA 10432
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

const double PI = acos(0) * 2;

int main () {
	string s1;
	while (getline(cin, s1)) {
		double r, s;
		istringstream is(s1);
		is >> r >> s;
		double ang = 360.0 / s;
		printf("%.3f\n", (0.5 * r * r * sin(ang * PI / 180)) * s);
	}
	return 0;
}