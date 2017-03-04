/*
	UVA 11695
	Author: Youssef ElGhareeb

	Idea: The removed edge should occur on the diameter of the original tree
	Try all edges on the diameter. The removal of the edge will result in 2 subtrees
	The combined diameter of the 2 subtrees can be calculated as
		max(diam1, diam2, ceil(diam1/2.0) + ceil(diam2/2.0) + 1)
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

const int MXN = 3000;
vector<int> g[MXN];
int vis[MXN];
int n;

pair<int, int> get_furthest(int u, int pa) {
	pii res = make_pair(u, 1);
	loop(j, g[u].size()) {
		int v = g[u][j];
		if (v == pa) continue;
		pii cur = get_furthest(v, u);
		if (cur.second > res.second) res = cur;
	}
	res.second++;
	return res;
}

int get_furthest(int u) {
	return get_furthest(u, -1).first;
}

bool get_path(int u1, int u2, vector<int>& path) {
	if (u1 == u2) {
		path.pb(u1);
		return true;
	}
	if (vis[u1]) return false;
	vis[u1] = 1;
	path.pb(u1);
	loop(j, g[u1].size()) {
		int v = g[u1][j];
		bool flag = get_path(v, u2, path);
		if(flag) return true;
	}
	path.pop_back();
	return false;
}

vector<int> get_diameter(int start_node) {
	int u1 = get_furthest(start_node);
	int u2 = get_furthest(u1);
	vector<int> diam;
	memset(vis, 0, sizeof(vis));
	get_path(u1, u2, diam);
	return diam;
}

int main() {
	ios_base::sync_with_stdio(false);
	int tests;
	cin>>tests;
	loop(test, tests) {
		cin>>n;
		loop(i, n) g[i].clear();
		loop(i, n-1) {
			int a, b;
			cin>>a>>b;
			a--;
			b--;
			g[a].pb(b);
			g[b].pb(a);
		}
		int best_diam = MXN;
		int de1 = 0, de2 = 0; // deleted edges
		int ae1 = 0, ae2 = 0; // added edges
		vector<int> diam = get_diameter(0);
		for (int i=0; i<diam.size() - 1; i++) {
			int u = diam[i];
			int v = diam[i+1];

			// Remove the edge u, v
			loop(i, g[u].size()) {
				if (g[u][i] == v) {
					g[u].erase(g[u].begin() + i);
					break;
				}
			}
			loop(i, g[v].size()) {
				if (g[v][i] == u) {
					g[v].erase(g[v].begin() + i);
					break;
				}
			}

			// Getting the diameters of the 2 subtrees
			vector<int> diam1 = get_diameter(u);
			vector<int> diam2 = get_diameter(v);

			int val = ceil((diam1.size() - 1)/2.0) + ceil((diam2.size() - 1)/2.0) + 1;
			val = max(val, (int)diam1.size() - 1);
			val = max(val, (int)diam2.size() - 1);
			if (val < best_diam) {
				best_diam = val;
				de1 = u;
				de2 = v;
				ae1 = diam1[diam1.size() / 2];
				ae2 = diam2[diam2.size() / 2];
			}

			// Adding back the removed edge
			g[u].push_back(v);
			g[v].push_back(u);
		}
		de1++; de2++;
		ae1++; ae2++;
		cout<<best_diam<<endl;
		cout<<min(de1, de2)<<" "<<max(de1, de2)<<endl;
		cout<<min(ae1, ae2)<<" "<<max(ae1, ae2)<<endl;
	}
	return 0;
}