/*
	UVA 1419
	Author: Youssef ElGhareeb
*/

#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define vi vector<int>
#define pb push_back
#define loop(i,n) for(int i=0; i<n; i++)
#define pii pair<int, int>
#define mp make_pair

const int MXN = 105;
string g[MXN];
int c1[26][MXN], c2[26][MXN];
int av[26];
int n, m;

int main() {
    ios_base::sync_with_stdio(false);
    while (cin>>n>>m) {
        if (!n && !m) break;
        memset(c1, 0, sizeof(c1));
        memset(c2, 0, sizeof(c2));
        memset(av, 0, sizeof(av));
        loop(i, n) {
            string s;
            cin>>s;
            g[i] = s;
            loop(j, s.length()) {
                if(s[j] == '.') continue;
                c1[s[j]-'A'][i]++;
                c2[s[j]-'A'][j]++;
                av[s[j]-'A'] = 1;
            }
        }
        loop(k, 26) {
            if (!av[k]) continue;
            bool flag = true;
            int min_y = 0, max_y = n-1;
            while(!c1[k][min_y]) min_y++;
            while(!c1[k][max_y]) max_y--;
            if (max_y - min_y < 2) continue;
            for (int i=min_y + 1; i<max_y; i++) {
                if (c1[k][i] != 2) flag = false;
            }
            if (!flag || c1[k][min_y] != c1[k][max_y]) continue;
            int min_x = 0, max_x = m - 1;
            while(!c2[k][min_x]) min_x++;
            while(!c2[k][max_x]) max_x--;
            if(max_x - min_x < 2) continue;
            for (int i=min_x + 1; i<max_x; i++) {
                if (c2[k][i] != 2) flag = false;
            }
            if (!flag || c2[k][min_x] != c2[k][max_x]) continue;
            if (c1[k][min_y] != max_x - min_x + 1) continue;
            if (c2[k][min_x] != max_y - min_y + 1) continue;
            for (int i=min_y + 1; i<max_y; i++) {
                for (int j=min_x + 1; j < max_x; j++) {
                    if (g[i][j] != '.') flag = false;
                }
            }
            if (!flag) continue;
            char approved = 'A' + k;
            cout<<approved;
        }
        cout<<endl;
    }
    return 0;
}   