/*
	Live Archive 3476
	Author: Youssef ElGhareeb
	
	Idea:
		- We will solve this problem using backtracking
		- At each free cell, we have 2 options:
			1. Put a lamp in this cell. In this case we need to mark all cells in its row and column as covered.
			   We also need to keep track of those cells to free them.
			2. Leave the cell
		- Continue backtracking until finishing all the cells.
		- After finishing, check for consistency:
			1. There shouldn't be any free cells
			2. Numbered block cells should contain exactly that number of lamps adjacent to them
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

using namespace std;

#define ll long long
#define vi vector<int>
#define pb push_back
#define loop(i,n) for(int i=0; i<n; i++)
#define pii pair<int, int>
#define pdd pair<double, double>

const int INF = 1e4;
int n, m, b;
int res = INF;
int g[10][10];

/* Values conventions for the grid cells 
	0 - Free
	1 - Covered
	2 - Contains a lamp
	3 - Unnumbered block
	4~8 - Numbered block
*/
inline bool is_free (pii loc) {
	return g[loc.first][loc.second] == 0;
}

inline bool is_covered(pii loc) {
	return g[loc.first][loc.second] == 1;
}

inline bool is_block(pii loc) {
	return g[loc.first][loc.second] >= 3;
}

inline bool is_end (pair<int, int>& loc) {
	return loc.first > n;
}

/* Check that the grid is consistent, with 2 conditions:
	1. No cells should be free
	2. Any numbered block cell should exactly contain that number of lamps adjacent to it
*/
inline bool check_consistency() {
	int num_lamps = 0;
	for (int i=1; i<=n; i++) {
		for (int j=1; j<=m; j++) {
			if (g[i][j] == 2) num_lamps++;
			else if (g[i][j] == 0) return false;
			else if (g[i][j] >= 4) {
				int adj = g[i][j] - 4;
				int cnt_adj = 0;
				if (i > 1 && g[i-1][j] == 2) cnt_adj++;
				if (i < n && g[i+1][j] == 2) cnt_adj++;
				if (j > 1 && g[i][j-1] == 2) cnt_adj++;
				if (j < m && g[i][j+1] == 2) cnt_adj++;
				if (cnt_adj != adj) return false;
			}
		}
	}
	res = min(res, num_lamps);
	return true;
}

inline void get_next (pair<int, int> &loc) {
	loc.second++;
	if (loc.second > m) {
		loc.second = 1;
		loc.first++;
	}
}

inline vector<pii> mark_positions(pii& loc) {
	vector<pii> pos;
	g[loc.first][loc.second] = 2; // Contains a lamp
	pos.push_back(make_pair(loc.first, loc.second));
	for (int j = loc.second + 1; j <= m && !is_block(make_pair(loc.first, j)); j++) {
		if (is_covered(make_pair(loc.first, j))) continue;
		g[loc.first][j] = 1; // Covered
		pos.push_back(make_pair(loc.first, j));
	}
	for (int j = loc.second - 1; j > 0 && !is_block(make_pair(loc.first, j)); j--) {
		if (is_covered(make_pair(loc.first, j))) continue;
		g[loc.first][j] = 1; // Covered
		pos.push_back(make_pair(loc.first, j));
	}
	for (int i = loc.first + 1; i <= n && !is_block(make_pair(i, loc.second)); i++) {
		if (is_covered(make_pair(i, loc.second))) continue;
		g[i][loc.second] = 1; // Covered
		pos.push_back(make_pair(i, loc.second));
	}
	for (int i = loc.first - 1; i > 0 && !is_block(make_pair(i, loc.second)); i--) {
		if (is_covered(make_pair(i, loc.second))) continue;
		g[i][loc.second] = 1; // Covered
		pos.push_back(make_pair(i, loc.second));
	}
	return pos;
}

inline void free_positions(vector<pii>& positions) {
	for (int i=0; i<positions.size(); i++) {
		int r = positions[i].first;
		int c = positions[i].second;
		g[r][c] = 0;
	}
}

void solve (pair<int, int> loc) {
	while (!is_end(loc)) {
		if (is_free(loc)) {
			vector<pii> positions = mark_positions(loc);
			pii current_loc = loc;
			get_next(current_loc);
			solve(current_loc);
			free_positions(positions);
		}
		get_next(loc);
	}
	check_consistency();
}

int main() {
	ios_base::sync_with_stdio(false);
	while (cin>>n>>m) {
		if (!n && !m) break;
		memset(g, 0, sizeof(g));
		res = INF;
		cin>>b;
		for (int i =0; i<b; i++) {
			int r, c, type;
			cin>>r>>c>>type;
			g[r][c] = type + 4;
		}
		solve(pair<int, int>(1, 1));
		if (res == INF) cout<<"No solution\n";
		else cout<<res<<endl;
	}
	return 0;
}