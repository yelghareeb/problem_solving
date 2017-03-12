/* 
	SPOJ PWORDS
	Author: Youssef ElGhareeb
	
	Idea: 
		- This problem is solvable via dp
		- For each string, the dp state is defined as {Set of used characters so far, remaining distance}
		- Given distance x, we brute force on all possible values we can get: i from s1, and x - i from s2
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <cstring>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <map>
#include <assert.h>
 
using namespace std;
 
#define ll long long
#define vi vector<int>
#define pb push_back
#define loop(i,n) for(int i=0; i<n; i++)
#define pii pair<int, int>
#define mp make_pair
#define ABS(i) i<0?-i:i

ll dp[(1<<10) + 10][605][2][2];

ll calc (string& s, int ind, int mask, int rem, int change, int str, int used, int n) {
	if (rem < 0) return 0;
	if (ind == n) { 
		/* Terminating condition */
		if (!change && !rem) return 1;
		return 0;
	}
	ll& res = dp[mask][rem][change][str];
	if(res != -1) return res;
	
	res = 0;
	int letters = 0;
	loop(i, n) {
		if ((mask>>i) & 1) continue; // We have matched the ith character before
		if ((letters >> (s[i] - 'a')) & 1) continue; // Don't use the same letter twice in this position
		letters |= (1 << (s[i] - 'a'));
		res += calc(s, ind + 1, mask | (1<<i), rem - abs(s[ind] - s[i]), change, str, used | (1<<(s[i] - 'a')), n);
		if(change) {
			if (((used>> (s[i] - 1 - 'a')) & 1) == 0)
				res += calc(s, ind + 1, mask | (1<<i), rem - abs(s[ind] - (s[i] - 1)), 0, str, used | (1<<(s[i] - 1 - 'a')), n);
			if (((used>> (s[i] + 1 - 'a')) & 1) == 0)
				res += calc(s, ind + 1, mask | (1<<i), rem - abs(s[ind] - (s[i] + 1)), 0, str, used | (1<<(s[i] + 1 - 'a')), n);
		}
	}
	return res;
}

ll get_ans(string s1, string s2, int x) {
	if (x > 600) return 0;
	memset(dp, -1, sizeof(dp));
	ll res = 0;
	loop(i, x + 1) {
		res += calc(s1, 0, 0, i, 0, 0, 0, s1.length()) * calc(s2, 0, 0, x - i, 1, 1, 0, s2.length());
		res += calc(s1, 0, 0, i, 1, 0, 0, s1.length()) * calc(s2, 0, 0, x - i, 0, 1, 0, s2.length());
	}
	return res;
}

int main() {
	freopen("in.txt", "r", stdin);
	int tests;
	cin>>tests;
	loop(test, tests) {
		string s1, s2;
		int x;
		cin>>s1>>s2>>x;
		ll ans = get_ans(s1, s2, x);
		cout<<"Case "<<test + 1<<": "<<ans<<endl;
	}
	return 0;
}