/*
	SPOJ PATULJCI
	Author: Youssef ElGhareeb
	
	Idea:
	 For each value, keep an array of indices where it occurred. 
	 Then for each query [l, r], pick a random index between l and r, 
	 and count the number of occurrences of the value at the random index 
	 using upper/lower bound of its index array, and check if the count is > n / 2. 
	 
	 You can repeat this random experiment to a limit of 30 iterations, 
	 as after this the probability of not getting the element tends to zero.
	 
	 This idea is based on the fact that a majority element is highly probable to get chosen at random
	 in the given range
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
#include <time.h>       /* time */

using namespace std;

#define ll long long
#define vi vector<int>
#define pb push_back
#define loop(i,n) for(int i=0; i<n; i++)
#define pii pair<int, int>
#define pdd pair<double, double>

const int MXN = 3 * 1e5 + 5;
int n, c, q;
int a[MXN];
vector<int> pos[MXN];
const int limit = 30;

int main() {
	ios_base::sync_with_stdio(false);
	srand (time(NULL));
	cin>>n>>c;
	for (int i=0; i<n; i++) {
		cin>>a[i];
		pos[a[i]].push_back(i);
	}
	cin>>q;
	for (int i=0; i<q; i++) {
		int l, r;
		cin>>l>>r;
		l--;	r--;
		bool found = false;
		int range = r - l + 1;
		for (int j=0; j<limit; j++) {
			/* Pick a random element between l & r */
			int random_ind = l + rand() % (r - l + 1);
			int val = a[random_ind];
			int end = upper_bound(pos[val].begin(), pos[val].end(), r) - pos[val].begin();
			int start = lower_bound(pos[val].begin(), pos[val].end(), l) - pos[val].begin();
			int freq = end - start;
			if (freq > range / 2) {
				found = true;
				cout<<"yes"<<" "<<val<<endl;
				break;
			}
		}
		if (!found) cout<<"no"<<endl;
	}
	return 0;
}