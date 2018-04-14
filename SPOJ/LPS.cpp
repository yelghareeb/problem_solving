/*
	SPOJ LPS
	http://www.spoj.com/problems/LPS/
	Idea: Suffix Arrays, LCP 
	Author: Youssef Elghareeb
*/

#include <bits/stdc++.h>

using namespace std;

typedef long long LL;
typedef vector<int> vi;
typedef pair<int, int> pii;
#define pb push_back
#define loop(i,n) for(int i = 0; i < n; i++)

const int N = 2 * 1e5 + 5;
const LL inf = 1e18 * 2ll;
const int MX = 5 * 1e6 + 5;

struct SuffixArray {
    string s;
    int n;
    char pad;
    vector<int> RA, SA;
    vector<int> tempRA, tempSA;
    vector<int> c;
    
    SuffixArray (char pad) {
        this->pad = pad;
    }
    
    void countingSort(int k) {
        int i, sum, maxi = max(300, n);
        c = vector<int>(2 * N, 0);
        for (i = 0; i < n; ++i) {
            if (i + k < n) c[RA[i + k]]++;
            else c[0]++;
        }
        for (i = sum = 0; i < maxi; i++) {
            int t = c[i];
            c[i] = sum;
            sum += t;
        }
        for (i = 0; i < n; i++) {
            tempSA[c[SA[i] + k < n? RA[SA[i] + k] : 0]++] = SA[i];
        }
        for (i = 0; i < n; i++) {
            SA[i] = tempSA[i];
        }
    }
    
    void init() {
        n = s.length();
        RA = vector<int>(2 * N, 0);
        SA.resize(n);
        tempRA = vector<int>(2 * N, 0);
        tempSA.resize(n);
    }
    
    vector<int> getSA (string s) {
        int i, k, r;
        vector<int> suffixArray;
        s += pad;
        this->s = s;
        init();
        for (i = 0; i < n; i++) RA[i] = s[i];
        for (i = 0; i < n; i++) SA[i] = i;
        for (k = 1; k < n; k <<= 1) {
            countingSort(k);
            countingSort(0);
            tempRA[SA[0]] = r = 0;
            for (i = 1; i < n; i++) {
                tempRA[SA[i]] = (RA[SA[i]] == RA[SA[i - 1]] && RA[SA[i] + k] == RA[SA[i - 1] + k]) ? r : ++r;
            }
            for (i = 0; i < n; i++) {
                RA[i] = tempRA[i];
            }
            if (RA[SA[n - 1]] == n - 1) break; // optimization
        }
        for (i = 1; i < n; ++i) {
            suffixArray.push_back(SA[i]);
        }
        return suffixArray;
    }
    
    vector<int> getLCP (string s) {
        vector<int> Phi(n);
        vector<int> PLCP(n);
        vector<int> LCP(n - 1, 0);
        int i, L;
        Phi[SA[0]] = -1; // default value
        for (i = 1; i < n; i++) // compute Phi in O(n)
            Phi[SA[i]] = SA[i - 1]; // remember which suffix is behind this suffix
        for (i = L = 0; i < n; i++) { // compute Permuted LCP in O(n)
            if (Phi[i] == -1) {
                PLCP[i] = 0;
                continue;
            } // special case
            while (s[i + L] == s[Phi[i] + L]) L++; // L increased max n times
            PLCP[i] = L;
            L = max(L - 1, 0); // L decreased max n times
        }
        for (i = 0; i < n - 1; i++) {// compute LCP in O(n)
            LCP[i] = PLCP[SA[i + 1]]; // put the permuted LCP to the correct position
        }
        return LCP;
    }
};

string s, orig, rev;

int main() {
#ifdef DEBUG
    freopen("in.txt", "r", stdin);
#endif
    int n;
    cin >> n >> orig;
    rev = orig;
    reverse(rev.begin(), rev.end());
    s = orig + "$" + rev;
    SuffixArray SA(' ');
    vector<int> suffixArray = SA.getSA(s);
    vector<int> LCP = SA.getLCP(s);
    int res = 0;
    for (int i = 1; i < s.length(); ++i) {
        int pos = suffixArray[i];
        int prevPos = suffixArray[i - 1];
        if ((pos < orig.length() && prevPos > orig.length()) || 
                (prevPos < orig.length() && pos > orig.length())) {
            res = max(res, LCP[i]);
        }
    }
    cout << res << endl;
    return 0;
}