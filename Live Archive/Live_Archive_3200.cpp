/*
	Live Archive 3200
	Author: Youssef ElGhareeb
	
	Idea:
		- Simple DFS from the start node to the end node
		- Keep all the found paths in a vector and sort them
*/

#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define vi vector<int>
#define pb push_back
#define loop(i,n) for(int i=0; i<n; i++)
#define pii pair<int, int>
#define mp make_pair

const int MXN = 25;
int nv, nr; // number of villages, number of roads
int sv, dv; // start village, destination village
int max_dist;
int vis[MXN];
vector<pii> g[MXN];
vector<vi> pathes;

void recurse(int cur, int dist, vector<int> path) {
    if(vis[cur]) return;
    vis[cur] = 1;
    path.push_back(cur);
    if(cur == dv) { // Terminating condition
        path.insert(path.begin(), dist);
        pathes.push_back(path);
    }
    else {
        loop(j, g[cur].size()) {
            int v = g[cur][j].first;
            int d = g[cur][j].second;
            recurse(v, dist + d, path);
        }
    }
    vis[cur] = 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    int test = 0;
    while (cin>>nv && nv != -1) {
        if (test > 0) cout<<"\n";
        cin>>nr;
        loop(i, MXN) g[i].clear();
        pathes.clear();
        memset(vis, 0, sizeof(vis));
        loop(i, nr) {
            int c1, c2, dist;
            cin>>c1>>c2>>dist;
            g[c1].push_back(mp(c2, dist));
            g[c2].push_back(mp(c1, dist));
        }
        cin>>sv>>dv;
        cin>>max_dist;
        recurse(sv, 0, vector<int> ());
        sort(pathes.begin(), pathes.end());
        cout<<"Case "<<++test<<":\n";
        if (pathes.empty()) {
            cout<<" NO ACCEPTABLE TOURS\n";
        }
        else {
            bool printed = false;
            for (int i=0; i<pathes.size(); i++) {
                if(pathes[i][0] <= max_dist) {
                    printed = true;
                    cout<<" "<<pathes[i][0]<<":";
                    loop(j, pathes[i].size() - 1) cout<<" "<<pathes[i][j + 1];
                    cout<<" "<<endl;
                }
            }
            if (!printed) cout<<" NO ACCEPTABLE TOURS\n";
        }
    }
    return 0;
}   