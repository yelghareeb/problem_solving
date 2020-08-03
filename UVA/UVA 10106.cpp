/*
	UVA 10106
	Author: Youssef ElGhareeb
*/

#include <bits/stdc++.h>

using namespace std;

const int MXN = 600; // multiplying two n-digit number results in a 2n-digit number so, we instantiate an array of size 2n

int main() {
	ios_base::sync_with_stdio(false); // for fast input/output
	string s1, s2; // using strings to holds the 2-numbers, as the 2-numbers can't be held in long or int data types
	// while s1 is not empty
	while (cin>>s1) { 
		cin>>s2;
		// reversing the 2-numbers/strings as we will do the operation on the least signficant digits
		reverse(s1.begin(), s1.end());
		reverse(s2.begin(), s2.end());
		//instantiating an array with the MAN size
		int a[MXN];
		// setting all the elements of the array to zero
		memset(a, 0, sizeof(a));
		/*
		24* 153 = ?
		index  3    2    1    0
		
		                 2    4
			              *
		            1    5    3
		       -----------------
		      all elements are zeros
		              (0)    (0)    (0)    (0)  
		      indeces (-)   (0+2)  (0+1)  (0+0)
		              (-)   (5*2)  (2*3)  (4*3) 
		     	      (0)    (10)   (6)   (12) 
		      +indces (-)   (1+2)  (1+1)  (1+0) 
		             (0+0) (10+4) (6+10) (12+0)
		              (0)   (14)   (26)   (12) 
		*/
		for (int i=0; i<s1.length(); i++) {
			for (int j=0; j<s2.length(); j++) {
				a[i + j] += (s1[i]-'0') * (s2[j] - '0');
			}
		}
		// prpagating the carry
		//N.B for num = 23
		// num % 10 = 3, num / 10 = 2
		for (int i=0; i<MXN - 1; i++) {
			a[i + 1] += a[i] / 10;
			a[i] %= 10;
		}
		// searching for the first non-zero element to begin printing the numbers
		int i = MXN - 1;
		while (i > 0 && a[i] == 0) i--;
		for (; i>=0; i--) cout<<a[i];
		cout<<endl;
	}
	return 0;
}
