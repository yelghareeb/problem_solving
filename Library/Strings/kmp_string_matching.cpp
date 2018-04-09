/*
	KMP for string matching 
	Author: Youssef Elghareeb
*/

#include <bits/stdc++.h>

using namespace std;

typedef long long LL;
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef vector<double> vd;
#define pb push_back
#define loop(i,n) for(int i = 0; i < n; i++)

const int N = 1e5 + 5;
const int inf = 1e9 + 7;

vi getPrefixArray(const string& s) {
    int i = 1, j = 0;
    vector<int> PA(s.length());
    while (i < s.length()) {
        if (s[i] == s[j]) {
            PA[i] = ++j;
        }
        else {
            while (j > 0) {
                j = PA[j - 1];
                if (s[i] == s[j]) {
                    PA[i] = ++j;
                    break;
                }
            }
        }
        i++;
    }
    return PA;
}

vi kmp(const string& text, const string& pattern) {
    vi prefixArray = getPrefixArray(pattern);
    vi matchingPositions;
    int j = 0;
    for (int i = 0; i < text.length(); ++i) {
        if (text[i] == pattern[j]) {
            ++j;
            if (j == pattern.length()) {
                matchingPositions.push_back(i - pattern.length() + 1);
                j = prefixArray[j - 1];
            }
        }
        else {
            if (j > 0) {
                j = prefixArray[j - 1];
                i--;
            }
        }
    }
    return matchingPositions;
}

int main() {
#ifdef DEBUG
    freopen("in.txt", "r", stdin);
#endif
    string text = "gatagacagagaca";
    string pattern = "aga";
    vi matchingPositions = kmp(text, pattern);
    for (int v : matchingPositions) cout << v << " ";
    cout << endl;
    return 0;
}