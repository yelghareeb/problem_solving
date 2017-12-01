/*
	Suffix Automaton
	The suffix automaton is a state machine that is used to identify all the suffixes of a string 
	and has quite many applications
	
	Taken from the following tutorial: http://codeforces.com/blog/entry/20861 
	Author: Youssef Elghareeb
*/

#include <bits/stdc++.h>
using namespace std;

#define loop(i,n) for(int i = 0; i < n; i++)
#define pii pair<int, int>
#define per(i,n) for (int i = n; i >= 0; i--)

typedef long long LL;

struct SuffixAutomaton {
    vector<map<char, int> > edges;
    vector<int> link; // link[i] is the parent of i
    vector<int> length; // length[i] is the length of the longest string in the ith class
    set<int> terminals;
    int last;
    
    SuffixAutomaton(string s) {
        // Add the initial node
        edges.push_back(map<char, int>());
        link.push_back(-1);
        length.push_back(0);
        last = 0;
        
        for (int i = 0; i < s.length(); i++) {
            // construct r
            edges.push_back(map<char, int>());
            length.push_back(i + 1);
            link.push_back(0);
            int r = edges.size() - 1;
            
            // Add edges to r
            int p = last;
            while (p >= 0 && edges[p].find(s[i]) == edges[p].end()) {
                edges[p][s[i]] = r;
                p = link[p];
            }
            if (p != -1) {
                int q = edges[p][s[i]];
                if (length[p] + 1 == length[q]) {
                    // We do not have to split q, just set the correct suffix link
                    link[r] = q;
                }
                else {
                    // we have to split, add q'
                    edges.push_back(edges[q]); // copy edges of q
                    length.push_back(length[p] + 1);
                    link.push_back(link[q]);
                    int qq = edges.size() - 1;
                    link[q] = qq;
                    link[r] = qq;
                    while (p >= 0 && edges[p][s[i]] == q) {
                        edges[p][s[i]] = qq;
                        p = link[p];
                    }
                }
            }
            last = r;
        }
        int p = last;
        while (p > 0) {
            terminals.insert(p);
            p = link[p];
        }
    }
};

void is_substring(string text, string pattern) {
    cout << "     -> Testing if '" << pattern << "' is a substring of '" << text << "'";
    SuffixAutomaton automaton(text);
    bool fail = false;
    int n = 0;
    for (int i = 0; i < pattern.length(); i++) {
        if (automaton.edges[n].find(pattern[i]) == automaton.edges[n].end()) {
            fail = true;
            break;
        }
        n = automaton.edges[n][pattern[i]];
    }
    cout << " .. ";
    if (fail)  cout << "NO" << endl;
    else cout << "YES" << endl;
}

void is_suffix(string text, string pattern) {
    cout << "     -> Testing if '" << pattern << "' is a suffix of '" << text << "'";
    SuffixAutomaton automaton(text);
    bool fail = false;
    int n = 0;
    for (int i = 0; i < pattern.length(); i++) {
        if (automaton.edges[n].find(pattern[i]) == automaton.edges[n].end()) {
            fail = true;
            break;
        }
        n = automaton.edges[n][pattern[i]];
    }
    cout << " .. ";
    if (fail || automaton.terminals.find(n) == automaton.terminals.end())  cout << "NO" << endl;
    else cout << "YES" << endl;
}

int main()
{
#ifdef DEBUG
    freopen("in.txt", "r", stdin);
#endif
    cout << "Testing the suffix automaton" << endl;
   
    cout << "  1. Substrings" << endl;
    is_substring("abacbac", "acb");
    is_substring("alchewaewqtr", "ewaewqt");
    is_substring("dfhsldsa", "abc");
    
    cout << "  2. Suffixes" << endl;
    is_suffix("amnop", "nop");
    is_suffix("amnop", "mno");
    is_suffix("amnop", "abc");
    return 0;
}