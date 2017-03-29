/*
	Live Archive 2721
	Author: Youssef ElGhareeb
	
	Idea:
	  1. Do a flood fill to identify the connected components. Store them in g1
	  2. From g1, build another graph g2 having n+1 rows and m+1 columns. The vertices corresponds to the corners of each cell
	  3. Use g2 to get the distances between components. This can be done by scanning each row and each column of g2 in linear time
	  4. Get the minimum spanning forests from the graph generated at the previous step
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

#define pii pair<int, int>
#define mp make_pair
#define loop(i,n) for(int i=0; i<n; i++) 

const int MXN = 105;
const int dx[] = {1, -1, 0, 0, 1, 1, -1, -1};
const int dy[] = {0, 0, 1, -1, 1, -1, 1, -1};

int vis1[MXN][MXN], labs1[MXN][MXN], g2[MXN][MXN], pa[MXN * MXN], sz[MXN * MXN];
int n, m, c_cntr1;
string g1[MXN];

void reset() {
	c_cntr1 = 0;
	memset(vis1, 0, sizeof(vis1));
	memset(labs1, 0, sizeof(labs1));
	memset(g2, 0, sizeof(g2));
	loop(i, MXN * MXN) pa[i] = i;
	loop(i, MXN * MXN) sz[i] = 1;
}

int find (int u) {
	if (pa[u] == u) return u;
	return pa[u] = find(pa[u]);
}

void merge(int u, int v) {
	int c1 = find(u);
	int c2 = find(v);
	if (c1 == c2) return;
	if (sz[c1] > sz[c2]) swap(c1, c2);
	pa[c1] = c2;
	sz[c2] += sz[c1];
}

void fill (int r, int c, int v) {
	if (r < 0 || c < 0 || r >= n || c >=m) return;
	if (g1[r][c] == '.') return;
	if (vis1[r][c]) return;
	vis1[r][c] = 1;
	labs1[r][c] = v;
	for (int i=0; i<8; i++) {
		fill(r + dx[i], c + dy[i], v);
	}
}

void eval(int i, int j, int& lst_v, int& lst_p, map<pii, int>& d3, int ds, int av) {
	if (g2[i][j] == 0) return;
	if (lst_v != 0 && g2[i][j] != lst_v) {
		int c1 = lst_v;
		int c2 = g2[i][j];
		if (c1 > c2) swap(c1, c2);
		pii pr = mp(c1, c2);
		if (d3.count(pr) == 0) d3[pr] = ds;
		else d3[pr] = min(d3[pr], ds);
	}
	lst_p = av;
	lst_v = g2[i][j];
}

int main() {
	freopen("in.txt", "r", stdin);
	ios_base::sync_with_stdio(false);
	int test_case = 1;
	bool first_case = true;
	while (cin>>n>>m) {
		if (!n && !m) break;
		if (!first_case) cout<<endl;
		first_case = false;
		cout<<"City "<<test_case++<<endl;
		for (int i=0; i<n; i++) cin>>g1[i];
		reset();
		for (int i=0; i<n; i++) {
			for (int j=0; j<m; j++) {
				if (!vis1[i][j] && g1[i][j] == '#') fill(i, j, ++c_cntr1);
			}
		}
		if (c_cntr1 == 0) {
			cout<<"No bridges are needed."<<endl;
			continue;
		}
		if (c_cntr1 == 1) {
			cout<<"No bridges are needed."<<endl;
			continue;
		}
		for (int i=0; i<n; i++) {
			for (int j=0; j<m; j++) {
				if (labs1[i][j] > 0) {
					g2[i][j] = g2[i+1][j] = g2[i][j+1] = g2[i+1][j+1] = labs1[i][j];
				}
			}
		}
		
		/* Build the edges between the nodes */
		map<pii, int> d3;
		for (int i=0; i<=n; i++) { // Scanning the ith row
			int lst_v = g2[i][0], lst_p = 0;
			for (int j=1; j<=m; j++) {
				eval(i, j, lst_v, lst_p, d3, j - lst_p, j);
			}
		}
		for (int j=0; j<=m; j++) { // Scanning the jth column
			int lst_v = g2[0][j], lst_p = 0;
			for (int i=1; i<=n; i++) {
				eval(i, j, lst_v, lst_p, d3, i - lst_p, i);
			}
		}

		/* Calculate the minimum spanning tree */
		/* 1. Get the sorted edges according to their weights */
		int e_cnt = 0;
		vector<pair<int, pii> > wei(d3.size());
		for (map<pii, int>::iterator it = d3.begin(); it != d3.end(); it++) {
			wei[e_cnt++] = mp(it->second, it->first);
		}
		sort(wei.begin(), wei.end());
		int cnt_edges = 0, best_dist = 0;
		for (int i=0; i<wei.size(); i++) {
			int w = wei[i].first;
			int u = wei[i].second.first;
			int v = wei[i].second.second;
			if(find(u) == find(v)) continue;
			merge(u, v);
			cnt_edges++;
			best_dist += w;
		}
		set<int> cmps2;
		for (int i=0; i<=n; i++) {
			for (int j=0; j<=m; j++) {
				if (g2[i][j] != 0) cmps2.insert(find(g2[i][j]));
			}
		}
		if (cnt_edges == 0) cout<<"No bridges are possible."<<endl;
		else {
			if (cnt_edges == 1) cout<<cnt_edges<<" bridge of total length "<<best_dist<<endl;
			else cout<<cnt_edges<<" bridges of total length "<<best_dist<<endl;
		}
		if (cmps2.size() > 1) cout<<cmps2.size()<<" disconnected groups"<<endl;
	}
	return 0;
}