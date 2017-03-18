/*
	SPOJ PARSUMS
	Author: Youssef ElGhareeb
	
	Idea:
		concatenate the array to itself, so that the total length of the array is 2*n
		start from the rightmost index and go backward, accumulating the elements. Now we have 2 cases:
			1. If the sum is negative, and the current index is less than n, 
			   then a rotation starting at the current index is not feasible
			2. If the sum is positive, reset the sum, and increment the answer if the index is less than n
			
		Example:
			orig_array = [1 2 -3 4]
			concatenated array = [1 2 -3 4 1 2 -3 4]
			
			index 	sum_before	 sum_after 	sum_after_resetting 	Answer
			  8			 0			 4				 0				  0
			  7			 0			-3				-3				  0
			  6			-3			-1 				-1 				  0
			  5			-1			 0				 0				  0
			  
			  4			 0 			 4				 0				  1
			  3			 0			-3				-3				  1
			  2			-3			-1				-1				  1
			  1			-1			 0				 0				  2
*/

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <sstream>
#include <queue>
using namespace std;

#define loop(i,n) for(int i=0; i<n; i++)
#define ll long long
#define pii pair<int, int>
#define pb push_back

const int MXN = 2 * 1e6 + 5;
const int INF = 1e9 + 7;

int a[MXN], n;

int main() {
	ios_base::sync_with_stdio(false);
	while (cin>>n && n) {
		loop(i, n) cin>>a[i];
		loop(i, n) a[i + n] = a[i];
		ll s = 0;
		int ans = 0;
		for (int i=2*n - 1; i>=0; i--) {
			s += a[i];
			if (s >= 0) {
				if (i < n) ans++;
				s = 0;
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}