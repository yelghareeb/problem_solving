/*
	UVA 10161
	Author: Youssef ElGhareeb
	
	Idea:
		- Get the diagonal on which the query number is located, as in the following sample,
		  Diagonals contain (1, 3, 5, 7, ...) blocks. The sum of this arithmetic progression is n / 2 (2a + (n - 1) d) = n^2
			d4 d4 d4 d4
			d3 d3 d3 d4
			d2 d2 d3 d4
			d1 d2 d3 d4
		- Get the IDs of the first and last blocks on the diagonal
		- If the query number is located on an odd diagonal, then it will start from the bottom, go upward and then go left
		- Otherwise, it would start from the left, go to the right and then to the bottom
*/

#include <bits/stdc++.h>

using namespace std;

#define ll unsigned long long
#define vi vector<int>
#define pb push_back
#define loop(i,n) for(int i=0; i<n; i++)
#define pii pair<int, int>
#define mp make_pair

int main() {
    ios_base::sync_with_stdio(false);
	ll n;
	while (cin>>n && n) {
		ll cnt = ceil(sqrt(n));
		ll start = (cnt - 1) * (cnt - 1) + 1;
		ll end = cnt * cnt;
		if (cnt % 2) {
			if (n - start <= end - n) cout<<cnt<<" "<<1 + n - start<<endl;
			else cout<<end - n + 1<<" "<<cnt<<endl;
		}
		else {
			if (n - start <= end - n) cout<<1 + n - start<<" "<<cnt<<endl;
			else cout<<cnt<<" "<<end - n + 1<<endl;
		}
	}
    return 0;
}   