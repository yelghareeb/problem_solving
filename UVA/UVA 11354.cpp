/*
	UVA 11354
	Author: Youssef ElGhareeb
*/

#include <iostream>
#include <cmath>
#include <string>
#include <assert.h>
#include <sstream>
#include <map>
#include <algorithm>

using namespace std;

#define ll unsigned long long
#define vi vector<int>
#define pb push_back
#define loop(i,n) for(int i=0; i<n; i++)
#define pii pair<int, int>
#define mp make_pair

const int MX_ROADS = 1e5 + 5;
const int MX_CITIES = 5 * 1e4 + 5;
const int MX_QUERIES = 5 * 1e4 + 5;
int n; // Number of cities
int m; // Number of roads
int q; // Number of queries
pair<int, pii> roads[MX_ROADS]; // Roads description
int q_answers[MX_QUERIES]; // Query answers
map<int, int> q_comps[MX_CITIES]; // Query components

/* Union find variables */
int comps[MX_CITIES];
int szs [MX_CITIES];

void read_nm(string s) {
	istringstream is(s);
	is>>n>>m;
	return;
}

void reset() {
	for (int i=0; i<MX_CITIES; i++) {
		comps[i] = i;
		szs[i] = 1;
		q_comps[i].clear();
	}
}

int find(int u) {
	if (comps[u] == u) return u;
	return comps[u] = find(comps[u]);
}

void merge(int u, int v) {
	if (szs[u] > szs[v]) swap(u, v);
	int c_u = find(u);
	int c_v = find(v);
	if (c_u == c_v) return;
	comps[u] = v;
	szs[v] += szs[u];
}

int main() {
	freopen("in.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
	string line;
	bool first_data_set = true;
	while (true) {
		getline(cin, line, '\n');
		if (!first_data_set) cout<<endl;
		first_data_set = false;

		/* Reset the global parameters */
		reset();

		/* Read the variables n and m */
		read_nm(line);
		
		/* Read the roads info */
		for (int i=0; i<m; i++) {
			int xi, yi, di;
			cin>>xi>>yi>>di;
			if (xi > yi) swap(xi, yi);
			roads[i] = make_pair(di, make_pair(xi, yi));
		}

		/* Read the queries */
		cin>>q;
		for (int i=0; i<q; i++) {
			int si, ti;
			cin>>si>>ti;
			if (si > ti) swap(si, ti);
			q_comps[si][i] = 1;
			q_comps[ti][i] = 1;
		}

		/* Sort the edges according to their dangerousness */
		sort(roads, roads + m);

		/* Add edges to the graph one by one */
		for (int i=0; i<m; i++) {
			int& danger = roads[i].first;
			int& start = roads[i].second.first;
			int& end = roads[i].second.second;

			int c_s = find(start);
			int c_e = find(end);
			
			/* Continue if both cities are in the same component */
			if (c_s == c_e) continue;
			if (szs[c_s] > szs[c_e]) swap(c_s, c_e);

			for(map<int, int>::iterator it = q_comps[c_s].begin(); it != q_comps[c_s].end(); it++) {
				int query_number = it->first;

				if (q_comps[c_e][query_number] == 1) { // query_number exists in both start and end components
					q_answers[query_number] = danger;
				}
				else { // Merge this query into the larger component
					q_comps[c_e][query_number] = 1;
				}
			}

			/* Merge the 2 components */
			merge(c_s, c_e);

			/* Clear the queries belonging to the smaller component */
			q_comps[c_s].clear();
		}

		/* Print the answers */
		for (int i=0; i<q; i++) {
			cout<<q_answers[i]<<endl;
		}

		getline(cin, line, '\n'); // Dummy read for the current line
		if (!getline(cin, line, '\n')) break; // Read the blank line between consecutive cases
	}
    return 0;
}   