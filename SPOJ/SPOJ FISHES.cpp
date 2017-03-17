/*
	SPOJ FISHES
	Author: Youssef ElGhareeb
	
	Idea:
	- The first simplification is in the summation formula as follows
		  SUM { Xi * (V . Vi) } 
		= SUM {V . Xi Vi} 
		= V . SUM {Xi Vi}
	- As you can observe, Xi Vi is constant, so we can precalculate this vector by multiplying each vector by its Xi and adding them all,
	  let's name this vector "Combined vector"
	- Now the problem is reduced to the following: we need to find a subrectangle, where the dot product of its V with the combined vector is maximum
	- The second observation is that the dot product is equivalent to the sum of the same subrectangle with transformed values, where each value
	  is replaced with its corresponding value in the combined vector (try this on paper)
	- Now the problem is reduced to a standard max subrectangle sum, than can be solved in O(n ^ 4) using precalculations
*/

#include <iostream>
#include <cmath>
#include <string>
#include <assert.h>
#include <sstream>
#include <map>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

#define ll long long
#define vi vector<int>
#define pb push_back
#define loop(i,n) for(int i=0; i<n; i++)
#define pii pair<int, int>
#define mp make_pair

const int INF = 1e9 + 7;
const int MX_N = 105;

int r, c, h, k, t;
int mat[MX_N][MX_N];
ll presums[MX_N][MX_N];
int V[MX_N * 5];

void precalc() {
	for (int i=0; i<r; i++) {
		for (int j=0; j<c; j++) {
			presums[i][j] = mat[i][j];
			if (i > 0) presums[i][j] += presums[i-1][j];
			if (j > 0) presums[i][j] += presums[i][j-1];
			if (i > 0 && j > 0) presums[i][j] -= presums[i-1][j-1];
		}
	}
}

ll get_sum(int i1, int j1, int i2, int j2) {
	ll res = presums[i2][j2];
	if (i1 > 0) res -= presums[i1-1][j2];
	if (j1 > 0) res -= presums[i2][j1 - 1];
	if (i1 > 0 && j1 > 0) res += presums[i1 - 1][j1 - 1];
	return res;
}

ll max_subrect_sum() {
	ll res = -INF;
	precalc();
	for (int i1=0; i1<r; i1++) {
		for (int j1=0; j1<c; j1++) {
			for (int i2=i1; i2<r; i2++) {
				for (int j2=j1; j2<c; j2++) {
					res = max(res, get_sum(i1, j1, i2, j2));
				}
			}
		}
	}
	return res;
}

void reset() {
	memset(V, 0, sizeof(V));
	memset(presums, 0, sizeof(presums));
}

int main() {
	freopen("in.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
	int tests;
	cin>>tests;
	for (int test=0; test<tests; test++) {
		reset();
		cin>>r>>c>>h>>k>>t;
		for (int i=0; i<r; i++) {
			for (int j=0; j<c; j++) {
				cin>>mat[i][j];
			}
		}

		/* Read the vector */
		for (int i=0; i<t; i++) {
			int x;
			cin>>x;
			for (int j=1; j<=k; j++) {
				int val;
				cin>>val;
				V[j] += val * x;
			}
		}

		/* Transform the matrix */
		for (int i=0; i<r; i++) {
			for (int j=0; j<c; j++) {
				mat[i][j] = V[mat[i][j]];
			}
		}

		/* Calculate the max subrectangle sum */
		cout<<"Case #"<<test + 1<<":"<<endl;
		ll ans = max_subrect_sum() + h;
		cout<<ans<<endl;
	}
    return 0;
}   