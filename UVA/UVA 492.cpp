/*
	UVA 492
	Author: Youssef ElGhareeb
*/

#include <iostream>
#include <stdio.h>
#include <cmath>
#include <map>
#include <vector>
#include <functional>
#include <assert.h>
#include <string>
#include <algorithm>
#include <time.h>
#include <cstring>
#include <queue>
#include <set>
#include <sstream>

using namespace std;

#define ll long long
#define vi vector<int>
#define pb push_back
#define loop(i,n) for(int i=0; i<n; i++)
#define pii pair<int, int>
#define pdd pair<double, double>

string process (string s) {
	char vowels[] = {'a', 'o', 'i', 'e', 'u'};
	bool beg_with_vowel = false;
	for (int j=0; j<5; j++) {
		if (s[0] == vowels[j] || s[0] == toupper(vowels[j])) {
			beg_with_vowel = true;
			break;
		}
	}
	if (beg_with_vowel) {
		return s + "ay";
	}
	else {
		s += s[0];
		s += "ay";
		return s.substr(1, s.length() - 1);
	}
}

int main () {
	ios_base::sync_with_stdio(false);
	string s1;
	while (getline(cin, s1, '\r')) {
		string s = "";
		for (int i=0; i<s1.length(); i++) {
			if (!isalpha(s1[i])) {
				if (!s.empty()) {
					s = process(s);
					cout<<s;
				}
				cout<<s1[i];
				s = "";
			}
			else {
				s += s1[i];
			}
		}
		cout<<endl;
	}
	return 0;
}