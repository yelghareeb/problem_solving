/*
	Copying Books
	Idea: Binary Search
	https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=655
	
	Author: Youssef Elghareeb
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
#define loop(i,n) for(int i = 0; i < n; i++)
#define pii pair<LL, int>
#define vi vector<int> 
#define pb push_back

const int MX = 1e5 + 5;

int m, k;
int p[505];
vector<vector<int> > tv, ans;

void fix() {
    while (tv.size() < k) {
        for (int i = 0; i < tv.size(); i++) {
            if (tv[i].size() > 1) {
                vector<int> tmp;
                tmp.push_back(tv[i][0]);
                tv[i].erase(tv[i].begin());
                tv.insert(tv.begin() + i, tmp);
                break;
            }
        }
    }
}

bool can (LL mid) {
    tv.clear();
    LL cur = 0;
    vector<int> v;
    int itr = 1;
    for (int i = m - 1; i >= 0; i--) {
        if (p[i] > mid) return false;
        if (cur + p[i] > mid) {
            tv.push_back(v);
            v.clear();
            cur = 0;
            itr++;
        }
        cur += p[i];
        v.push_back(p[i]);
    }
    if (itr > k) return false;
    if (!v.empty()) tv.push_back(v);
    reverse(tv.begin(), tv.end());
    loop(i, tv.size()) reverse(tv[i].begin(), tv[i].end());
    if (itr < k) fix();
    return true;
}

int main () {
#ifdef DEBUG
    freopen("in.txt", "r", stdin);
#endif
    int tests;
    scanf("%d", &tests);
    for (int test = 0; test < tests; test++) {
        scanf("%d%d", &m, &k);
        loop(i, m) scanf("%d", &p[i]);
        LL lo = 1, hi = 1e12, mid;
        while (lo < hi - 1) {
            mid = (lo + hi) / 2;
            if (can(mid)) {
                ans = tv;
                hi = mid;
            } 
            else {
                lo = mid + 1;
            }
        }
        if (can(hi)) { ans = tv; }
        else { can(lo); ans = tv; }
        for (int i = 0; i < ans.size(); i++) {
            if (i) printf(" / ");
            printf("%d", ans[i][0]);
            for (int j = 1; j < ans[i].size(); j++) {
                printf(" %d", ans[i][j]);
            }    
        }
        printf("\n");
    }
    return 0; 
}