/*
	UVA 697
	Author: Youssef ElGhareeb
*/

#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>
#define mp make_pair
#define loop(i,n) for (int i=0; i<n; i++)
#define pb push_back
#define ll long long
#define vi vector<int>

const double PI = acos(0) * 2;
const double EPS = 0.000000001;

int main () {
	ios_base::sync_with_stdio(false);
	double up, d, l, b, p, down, v, d2, l2, p2, vv;
	int test_number = 1;
	while (cin>>up) {
		/*
			b = capacity of the bucket
			d = diameter of the well
			acceleration = 32.2 feet / sec^2
			p = time to lift the bucket
		*/
		if (cin>>d) cin>>l>>b>>p>>down>>v;
		else break;
		d2 = d;
		l2 = l;
		p2 = p;
		vv = v; 
		d /= 12; /* Convert to feet */
		l /= 12; /* Convert to feet */
		p /= 12; /* Convert to feet per second */
		if (test_number > 1) printf ("\n");
		double res = 0;
		while (v > EPS) {
			res += up + down;
			res += sqrt((l * 2) / 32.2); /* Time to drop the bucket */
			res += l / p; /* Time to lift the bucket */
			l += b / (PI * d * d / 4.0);
			v -= b;
		}
		printf ("Scenario %d:\n", test_number);
		printf ("     up hill         %10.2f sec\n", up);
		printf ("     well diameter   %10.2f in\n", d2);
		printf ("     water level     %10.2f in\n", l2);
		printf ("     bucket volume   %10.2f cu ft\n", b);
		printf ("     bucket ascent rate%8.2f in/sec\n", p2);
		printf ("     down hill       %10.2f sec\n", down);
		printf ("     required volume %10.2f cu ft\n", vv);
		printf ("     TIME REQUIRED   %10.2f sec\n", res);
		test_number++;
	}	
	return 0;
}