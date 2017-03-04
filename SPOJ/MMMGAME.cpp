/*
	SPOJ MMMGAME
	Author: Youssef ElGhareeb
	
	Idea: Misère Nim
*/

#include <iostream>
#include <stdio.h>
#include <vector>
#include <cstring>
#include <cmath>
using namespace std;

#define loop(i,n) for(int i=0; i<n; i++) 
#define pb push_back
#define pii pair<int, int>

int main() {
	ios_base::sync_with_stdio(false);
	int tests;
	cin>>tests;
	loop(test, tests) {
		int n;
		cin>>n;
		int nim_sum = 0, mx = 0;
		loop(i, n) {
			int a;
			cin>>a;
			nim_sum ^= a;
			mx = max(mx, a);
		}
		if (mx == 1) {
			if(n % 2) cout<<"Brother\n";
			else cout<<"John\n";
		}
		else {
			if (nim_sum == 0) cout<<"Brother\n";
			else cout<<"John\n";
		}
	}
	return 0;
}