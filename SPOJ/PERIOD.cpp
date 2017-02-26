/*
	SPOJ PERIOD
	Author: Youssef ElGhareeb
*/

#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define vi vector<int>
#define pb push_back
#define loop(i,n) for(int i=0; i<n; i++)
#define pii pair<int, int>

const int MXN = 1e6 + 5;
string s;
int pref[MXN];
int len;

/*
	The KMP prefix functions calculates the array 'pref'
	pref[i] holds the length of the longest prefix which is also a suffix of the substring [0:i]
*/
void kmp_prefix() {
    int i = 1, j = 0;
    while (i < s.length()) {
        if (s[i] == s[j]) {
            pref[i] = ++j;
            i++;
        }
        else {
            if (j == 0) i++;
            else j = pref[j-1];
        }
    }
}

int main () {
    ios_base::sync_with_stdio(false);
    int tests;
    cin>>tests;
    loop(test, tests) {
        cout<<"Test case #"<<test + 1<<endl;
        memset(pref, 0, sizeof(pref));
        cin>>len;
        cin>>s;
        kmp_prefix();
        for (int i=1; i<s.length(); i++) {
            if (!pref[i]) continue;
            if (((i + 1) % (i + 1 - pref[i])) == 0) {
                cout<<i + 1<<" "<<(i + 1) / (i + 1 - pref[i])<<endl;
            }
        }
        cout<<endl;
    }
    return 0;
}   