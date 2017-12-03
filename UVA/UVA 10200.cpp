/*
	Prime Time
	Idea: number theory, preprocessing, primes
	https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1141
	
	Author: Youssef Elghareeb
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
#define loop(i,n) for(int i = 0; i < n; i++)
#define pii pair<LL, int>
#define vi vector<int> 
#define pb push_back

const int MX = 1e4 + 5;

int main () {
#ifdef DEBUG
    freopen("in.txt", "r", stdin);
#endif
    int bad[MX];
    for (int i = 0; i < MX; i++) {
        int u = i * i + i + 41;
        bad[i] = 0;
        for (int j = 2; j * j <= u; j++) {
            if ((u % j) == 0) bad[i] = 1;
        }
        if (i) bad[i] += bad[i - 1];
    }
    int a, b;
    while (scanf("%d%d", &a, &b) != EOF) {
        int rng = b - a + 1;
        int num = bad[b];
        if (a) num -= bad[a - 1];
        num = rng - num;
        printf("%.2lf\n", (double) num / rng * 100.0 + 1e-6);
    }
    return 0; 
}