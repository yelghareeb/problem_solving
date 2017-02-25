/*
	UVA 10174
	Author: Youssef ElGhareeb
	
	Idea:
		- Range queries: any number that has a remainder of 2 when divided by 4 is a bachelor number
		- Single elements queries: 
			Try to find 2 divisors where their difference is even
			a^2 - b^2 can be written as (a - b) * (a + b)
	http://cstheory.stackexchange.com/questions/12850/matching-on-bipartite-graph-multiple-edges
*/

#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define vi vector<int>
#define pb push_back
#define loop(i,n) for(int i=0; i<n; i++)
#define pii pair<int, int>

ll n, a, b;

bool get_input() {
    string s;
    if (!getline(cin, s, '\n')) return false;
    istringstream is(s);
    is>>a;
    if (!(is>>b)) {
        b = -1;
        n = a;
    }
    return true;
}

void get_range() {
    ll orig_range = b - a + 1;
    while (a % 4 != 2) a++;
    if (a > b) cout<<0<<endl;
    else cout<<((b - a) / 4 + 1)<<endl;
}

void get_answer() {
    if (n == 0) {
        cout<<0<<" "<<0<<endl;
        return;
    }
    int sgn = 0;
    if (n < 0) sgn = 1;
    n = abs(n);
    for (ll i=1; i * i <= n; i++) {
        if (n % i == 0) {
            if (i % 2 == (n / i) % 2) {
                ll n1 = i;
                ll n2 = n / i;
                ll mid = n1 + (n2 - n1) / 2;
                ll diff = mid - n1;
                if (sgn == 0) cout<<max(mid, diff) <<" "<<min(mid, diff)<<endl;
                else cout<<min(mid, diff)<<" "<<max(mid, diff)<<endl;
                return;
            }
        }
    }
}

int main () {
    ios_base::sync_with_stdio(false);
    while (get_input()) {
        if (b != -1) get_range();
        else {
            if (abs(n) % 4 == 2) {
                cout<<"Bachelor Number.\n";
            }
            else {
                get_answer();
            }
        }
    }
    return 0;
}