#include <bits/stdc++.h>
using namespace std;

#define loop(i,n) for(int i=0; i<n; i++)

string s1, s2, s3;

void init() {
	s1 = "][poiuytrewq";
	s2 = "';lkjhgfdsa";
	s3 = "/.,mnbvcxz";
}

char get (char c) {
	if (c >= 'A' && c <= 'Z') c = tolower(c);
	loop(i, s1.length()) if (s1[i] == c) return s1[i + 2];
	loop(i, s2.length()) if (s2[i] == c) return s2[i + 2];
	loop(i, s3.length()) if (s3[i] == c) return s3[i + 2];
	return ' ';
}

int main() {
	init();
	string s;
	getline(cin, s, '\n');
	string res = "";
	loop(i, s.length()) {
		if (s[i] == ' ') res += " ";
		else res += get(s[i]);
	}
	cout<<res<<endl;
	return 0;
}