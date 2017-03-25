/*
	UVA 350
	Author: Youssef ElGhareeb
*/

#include <iostream>
#include <stdio.h>
#include <cmath>
#include <map>
#include <vector>
#include <functional>
#include <assert.h>
#include <string>
#include <algorithm>
#include <time.h>
#include <cstring>
#include <queue>
#include <set>
#include <sstream>

using namespace std;

#define ll long long
#define vi vector<int>
#define pb push_back
#define loop(i,n) for(int i=0; i<n; i++)
#define pii pair<int, int>
#define pdd pair<double, double>

int main () {
	ios_base::sync_with_stdio(false);
	int z, i, m, l;
	int test = 1;
	while (cin>>z>>i>>m>>l) {
		if (!z && !i && !m && !l) break;
		set<int> s;
		int ind[10005];
		s.insert(l);
		ind[l] = 0;
		int cur = 1;
		while (true) {
			l = (z * l + i) % m;
			if (s.find(l) != s.end()) {
				cout<<"Case "<<test++<<": "<<cur - ind[l]<<endl;
				break;
			}
			ind[l] = cur;
			s.insert(l);
			cur++;
		}
	}
	return 0;
}