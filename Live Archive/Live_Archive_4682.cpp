/*
	Live Archive 4682
	https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2683
	
	Author: Youssef El Ghareeb
*/

#include <bits/stdc++.h>
#include <streambuf>
using namespace std;

#define loop(i,n) for(int i = 0; i < n; i++)
#define pii pair<int, int>
typedef unsigned long long LL;

const int INF = 1e9 + 7;
const int mod = 1e9 + 7;
const int MX = 1e5 + 5;

int a[MX];

struct Trie {
    Trie *ch[2];
    Trie() {
        ch[0] = ch[1] = NULL;
    }
    void insert(int val, int lev = 31) {
        if (lev < 0) return;
        int d = (val >> lev) & 1;
        if (!ch[d]) ch[d] = new Trie();
        ch[d]->insert(val, lev - 1);
    }
    int query(int val, int lev = 31) {
        if (lev < 0) return 0;
        int d = (val >> lev) & 1;
        if (d == 0) {
            if (ch[1]) return (1 << lev) + ch[1]->query(val, lev - 1);
            else return ch[0]->query(val, lev - 1);
        }
        else {
            if (ch[0]) return (1 << lev) + ch[0]->query(val, lev - 1);
            else return ch[1]->query(val, lev - 1);
        }
    }
};

int main()
{
#ifdef DEBUG
    freopen("in.txt", "r", stdin);
#endif
    int tests;
    scanf("%d", &tests);
    while (tests--) {
        int n;
        scanf("%d", &n);
        Trie trie;
        int xr = 0, ans = 0;
        trie.insert(xr);
        loop(i, n) {
            scanf("%d", &a[i]);
            xr ^= a[i];
            ans = max(ans, trie.query(xr));
            trie.insert(xr);
        }
        printf("%d\n", ans);
    }
    return 0;
}