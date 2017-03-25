/*
	Live Archive 3569
	Author: Youssef ElGhareeb
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

#define ll long long
#define vi vector<int>
#define pb push_back
#define loop(i,n) for(int i=0; i<n; i++)
#define pii pair<int, int>
#define pdd pair<double, double>

const int MXN = 55;
int n, m;
vi g[MXN];

inline int bfs (int start) {
	int res = 0, cnt_visited = 0;
	queue<pii> q;
	q.push(make_pair(start, 0));
	int vis[MXN];
	memset(vis, 0, sizeof(vis));
	vis[start] = 1;
	while (!q.empty()) {
		pii fr = q.front();
		q.pop();
		int v = fr.first;
		int stps = fr.second;
		res = max(res, stps);
		cnt_visited++;
		for (int j=0; j<g[v].size(); j++) {
			if (vis[g[v][j]]) continue;
			vis[g[v][j]] = 1;
			q.push(make_pair(g[v][j], stps + 1));
		}
	}
	if (cnt_visited < n) return -1;
	else return res;
}

int main () {
	ios_base::sync_with_stdio(false);
	int test = 1;
	while (cin>>n>>m) {
		if (!n && !m) break;
		for (int i=0; i<MXN; i++) g[i].clear();
		map<string, int> nm;
		int cntr = 0;
		for (int i=0; i<m; i++) {
			string s1, s2;
			cin>>s1>>s2;
			int i1, i2;
			if (nm.find(s1) == nm.end()) nm[s1] = cntr++;
			if (nm.find(s2) == nm.end()) nm[s2] = cntr++;
			i1 = nm[s1];
			i2 = nm[s2];
			g[i1].push_back(i2);
			g[i2].push_back(i1);
		}
		bool flag = true;
		int res = 0;
		for (int i=0; i<n; i++) {
			int v = bfs(i);
			if (v == -1) {
				flag = false;
				break;
			}
			else {
				res = max(res, v);
			}
		}
		cout<<"Network "<<test<<": ";
		if (!flag) cout<<"DISCONNECTED\n";
		else cout<<res<<endl;
		++test;
		cout<<endl;
	}
	return 0;
}