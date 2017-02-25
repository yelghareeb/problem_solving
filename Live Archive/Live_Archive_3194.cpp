/* 
	Live Archive 3194
	Author: Youssef ElGhareeb
	
	Idea: 
		- We do a factorization of all the Mersenne numbers offline and store the answers 
*/

#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define vi vector<int>
#define pb push_back
#define loop(i,n) for(int i=0; i<n; i++)
#define pii pair<int, int>

const int MXN = 2 * 1e5 + 5;

int p[] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61};

bool is_prime (int u) {
    for (int i=2; i * i <= u; i++) if (u % i == 0) return false;
    return true;
}

vector<ll> get_factors(ll u) {
    vector<ll> powers;

    for (ll d = 1, i = 2; i * i <= u; i += d, d = 2)
        while (u % i == 0)
            powers.push_back(i), u /= i;

    if (u > 1)
	powers.push_back(u);

    return powers;
}

void calc_answer() {
    for (int i=0; i<sizeof(p)/sizeof(int); i++) {
        vector<ll> factors = get_factors((1ll<<p[i]) - 1);
        if (factors.size() > 1) {
            cout<<factors[0];
            loop(j, factors.size() - 1) {
                cout<<" * "<<factors[j + 1];
            }
            cout<<" = "<<( (1ll<<p[i]) - 1);
            cout<<" = ( 2 ^ "<<p[i]<<" ) - 1\n" << flush;
        }
    }
}

string ans[64];

int main () {
    ios_base::sync_with_stdio(false);
    // calc_answer();
    ans[11] = "23 * 89 = 2047 = ( 2 ^ 11 ) - 1";
    ans[23] = "47 * 178481 = 8388607 = ( 2 ^ 23 ) - 1";
    ans[29] = "233 * 1103 * 2089 = 536870911 = ( 2 ^ 29 ) - 1";
    ans[37] = "223 * 616318177 = 137438953471 = ( 2 ^ 37 ) - 1";
    ans[41] = "13367 * 164511353 = 2199023255551 = ( 2 ^ 41 ) - 1";
    ans[43] = "431 * 9719 * 2099863 = 8796093022207 = ( 2 ^ 43 ) - 1";
    ans[47] = "2351 * 4513 * 13264529 = 140737488355327 = ( 2 ^ 47 ) - 1";
    ans[53] = "6361 * 69431 * 20394401 = 9007199254740991 = ( 2 ^ 53 ) - 1";
    ans[59] = "179951 * 3203431780337 = 576460752303423487 = ( 2 ^ 59 ) - 1";
    int n;
    cin>>n;
    loop(i, n) {
        int k;
        cin>>k;
        loop(x, k + 1) {
            if (ans[x] != "") cout<<ans[x]<<endl;
        }
        if (i < n - 1) cout<<endl;
    }
    return 0;
}