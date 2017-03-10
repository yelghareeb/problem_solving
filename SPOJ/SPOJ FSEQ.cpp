/*
	SPOJ FSEQ
	Author: Youssef ElGhareeb
	
	Idea:
		- The sequence F given in the problem statement is a fibonacci sequence, hence you can calculate F[i] = F[i-1] + F[i-2]
		- You can detect that the sequence is repeating when you encounter (0, 1, 1) again (I found this by observation)
		- Generate 2 cycles from the sequence modulo M. The length of the generated sequence is 2*C. Let's name the generated sequence fibs
		- For each element fibs[i], i from 0 to C - 1, we need to calculate the successor of fibs[i]. We do this using a priority queue as below
		- Given the successor of each element and the terminal nodes, we can calculate the length starting at each index using dynamic programming
*/

#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <map>
#include <queue>
#include <functional>
#include <cstring>

using namespace std;

#define loop(i,n) for(int i=0; i<n; i++)
#define ll long long
#define VI vector<int>
#define pii pair<int, int>
#define pb push_back

const int MXN = 1e6 + 5;
int fibs[MXN];
int successor[MXN];
int len[MXN];
int m;

int get_len(int pos) {
	if (len[pos] != -1) return len[pos];
	if (successor[pos] == -1) return 1;
	return len[pos] = 1 + get_len(successor[pos]);
}

int main() {
	ios_base::sync_with_stdio(false);
	int tests;
	cin>>tests;
	loop(test, tests) {
		cin>>m;
		if (m == 1) cout<<"Case "<<test + 1<<": "<<1<<endl;
		else {
			// 1. Generating the fibonacci sequence modulo M for 2 cycles
			fibs[0] = 0;
			fibs[1] = 1;
			fibs[2] = 1;
			int p = 3;
			int flag = 0;
			while (true) {
				fibs[p] = (fibs[p - 1] + fibs[p - 2]) % m;
				if (fibs[p] == 1 && fibs[p - 1] == 1 && fibs[p - 2] == 0) {
					flag++;
					if (flag == 2) { // This is the second cycle
						p -= 2;
						p /= 2; // p is now the length of 1 cycle
						break;
					}
				}
				p++;
			}
			// 2. Calculating the successor of each element from 1 to p
			priority_queue<pii, vector<pii>, std::greater<pii> > pq;
			memset(successor, -1, sizeof(successor));
			memset(len, -1, sizeof(len));
			loop(i, 2 * p) {
				while (!pq.empty() && fibs[i] > pq.top().first) {
					successor[pq.top().second] = i % p;
					pq.pop();
				}
				if (i < p) pq.push(make_pair(fibs[i], i));
			}
			// 3. Getting the total length
			ll res = 0;
			loop(i, p) {
				res += get_len(i);
			}
			cout<<"Case "<<test + 1<<": "<<res<<endl;
		}
	}
	return 0;
}