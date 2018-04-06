/*
	O(n log n) suffix arrays construction
	Reference: Competitive programming 3 
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
};

int main() {
#ifdef DEBUG
    freopen("in.txt", "r", stdin);
#endif
    string s = "GATAGACA";
    SuffixArray SA('$');
    vector<int> suffixArray = SA.getSA(s);
    for (int pos : suffixArray) {
        cout << s.substr(pos, s.length() - pos) << endl;
    }
    return 0;
}