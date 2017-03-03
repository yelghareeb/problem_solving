/*
	Author: Youssef ElGhareeb
	
	Idea: 
		- This problem has a cool simplification, by making benefit of the linearity of the expectation

		- Let X[i] be a random variable that can take values [0, 1], 
		  where 0 denotes that road X[i] is not full, and 1 denotes that road X[i] is full.
		  We need to calculate the expectation of the sum of all X[i]s
			Required: E(SUM(X[i]))
		  This can be simplified by calculating the SUM(E(X[i]))
	
		- To calculate the expectation of X[i] (the average that X[i] is used by all families),
		  Just multiply the probabilities that each family will use the ith road
*/

#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstring>

using namespace std;

#define loop(i,n) for(int i=0;i<n;i++)
#define pb push_back

const int MXN = 55;
int dist[MXN][MXN];
int vis[MXN];

class FoxAndTouristFamilies {
private:
	vector<int> g[55];
public:
	double expectedLength(vector <int>, vector <int>, vector <int>);
	void calc_dist(int orig, int u, int pa, int stps);
	int compute(int u, int v, int cur);
};

void FoxAndTouristFamilies::calc_dist(int orig, int u, int pa, int stps = 0) {
	dist[orig][u] = stps;
	loop(j, g[u].size()) {
		int v = g[u][j];
		if (v==pa) continue;
		calc_dist(orig, v, u, stps+1);
	}
}

int FoxAndTouristFamilies::compute(int u, int v, int cur) {
	if (vis[cur]) return 0;
	vis[cur] = 1;
	int res = 1;
	loop(j, g[cur].size()) {
		int next = g[cur][j];
		if (min(u, v) == min(next, cur) && max(u, v) == max(next, cur)) continue;
		res += compute(u, v, next);
	}
	return res;
}

double FoxAndTouristFamilies::expectedLength(vector <int> A, vector <int> B, vector <int> f) {
	int n = A.size() + 1;
	int m = f.size();
	loop(i, n - 1) { // Loop on edges
		int u = A[i];
		int v = B[i];
		g[u].pb(v);
		g[v].pb(u);
	}
	double res = 0;
	loop(i, n) calc_dist(i, i, -1); // Calculate the distance from node i to all other nodes
	loop(i, n-1) { // Loop on edges 
		int u = A[i];
		int v = B[i];
		memset(vis, 0, sizeof(vis));
		int left = compute(u, v, u); // Calculate the number of nodes on the left of u	
		int right = compute(u, v, v); // Calculate the number of nodes on the right of v
		double val = 1;
		loop(j, m) { // Aggregate the probabilities of each family using current road (u, v)
			int h = f[j];
			if (dist[h][u] < dist[h][v]) val *= right / (n-1.0); // Probability that jth family uses the road
			else val *= left / (n-1.0); // Probability that jth family uses the road
		}
		res += val;
	}
	return res;
}