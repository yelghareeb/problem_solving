/*
	UVA 737
	Author: Youssef ElGhareeb
	
	Idea: Assume that we have 2 cubes, their x-intersection will be bounded by the maximum x1, and minimum x2.
	For n cubes in general, the x-intersection is bounded by max xi1 and min xi2
	The same applies for the y and z intersections (they are independent)
*/

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <sstream>
#include <queue>
#include <cstring>
using namespace std;

#define loop(i,n) for(int i=0; i<n; i++)
#define ll long long
#define pii pair<int, int>
#define pb push_back

const int INF = 1e9 + 7;

int main() {
	ios_base::sync_with_stdio(false);
	int n;
	while (cin>>n && n) {
		int x, y, z, d;
		int min_x = INF, min_y = INF, min_z = INF;
		int max_x = -INF, max_y = -INF, max_z = -INF;
		loop(i, n) {
			cin>>x>>y>>z>>d;
			min_x = min(min_x, x + d);
			min_y = min(min_y, y + d);
			min_z = min(min_z, z + d);
			max_x = max(max_x, x);
			max_y = max(max_y, y);
			max_z = max(max_z, z);
		}
		cout<<max(0, min_x - max_x) * max(0, min_y - max_y) * max(0, min_z - max_z)<<endl;
	}
	return 0;
}