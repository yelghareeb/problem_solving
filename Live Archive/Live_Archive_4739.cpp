/*
	Live Archive 4739
	Author: Youssef ElGhareeb
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

const int MXN = 250;
int mt[MXN][MXN]; // Adjacency matrix

int main() {
	ios_base::sync_with_stdio(false);
	int n, t, a, b, cs=1;
	while (cin>>n>>t) {
		if (!n && !t) break;
		memset(mt, 0, sizeof(mt));
		int r = 0;
		loop(i, t) {
			cin>>a>>b;
			if (mt[b][a] || a == b) r++;
			else if (mt[a][b]) continue; // Ignore the edge if already added. Will help in pruning to fit in time
			else {
				mt[a][b] = 1;
				for (int j=1; j<=n; j++) if(mt[b][j]) mt[a][j] = 1; // node A should go to all nodes that B go to
				for (int j=1; j<=n; j++) { // Any nodes that go to A should go to all the nodes that A goes to
					if (mt[a][j]) {
						for (int k=1; k<=n; k++) if (mt[k][a] == 1) mt[k][j] = 1;
					}
				}
			}
		}
		cout<<cs++<<". "<<r<<endl;
	}
	return 0;
}