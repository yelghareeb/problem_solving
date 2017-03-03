/*
	UVA 10058
	Author: Youssef ElGhareeb
	
	Idea: Parse the input string and transform it to a vector string
	Then process it from left to right using a state machine according to the rules
*/

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <sstream>
#include <queue>
#include <cstring>
using namespace std;

#define loop(i,n) for(int i=0; i<n; i++)
#define ll long long
#define pii pair<int, int>
#define pb push_back

string s;
vector<string> words;

const string verbs[] = {"hate", "love", "know", "like", "hates", "loves", "knows", "likes"};
const string nouns[] = {"tom", "jerry", "goofy", "mickey", "jimmy", "dog", "cat", "mouse"};

void parse() {
	words.clear();
	string cur;
	for(int i=0; i<s.length(); i++) {
		if (s[i] == ' ') {
			if (cur != "") {
				words.push_back(cur);
				cur = "";
			}
		}
		else {
			cur += s[i];
		}
	}
	if (cur != "") words.push_back(cur);
}

bool is_article(int ind) {
	return words[ind] == "a" || words[ind] == "the";
}

bool is_noun(int& ind) {
	loop(j, sizeof(nouns) / sizeof(nouns[0])) {
		if (words[ind] == nouns[j]) {
			++ind;
			return true;
		}
	}
	return false;
}

bool get_verb(int& ind) {
	if (ind >= words.size()) return false;
	loop(j, sizeof(verbs) / sizeof(verbs[0])) {
		if (verbs[j] == words[ind]) {
			++ind;
			return true;
		}
	}
	return false;
}

bool get_active_list(int& ind) {
	while (true) {
		if (ind >= words.size()) return false;
		if (is_article(ind)) ++ind;
		if (ind >= words.size()) return false;
		if (!is_noun(ind)) return false;
		if (ind < words.size() && words[ind] == "and") {
			++ind;
		}
		else break;
	}
	return true;
}

bool check() {
	int ind = 0;
	while (true) {
		if(!get_active_list(ind)) return false;
		if(!get_verb(ind)) return false;
		if(!get_active_list(ind)) return false;
		if (ind == words.size()) break;
		if (words[ind] == ",") {
			++ind;
		}
		else return false;
	}
	return true;
}

int main() {
	ios_base::sync_with_stdio(false);
	while (getline(cin, s)) {
		parse();
		if (check()) cout<<"YES I WILL\n";
		else cout<<"NO I WON'T\n";
	}
	return 0;
}