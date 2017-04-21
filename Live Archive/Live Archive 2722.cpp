/*
	Live Archive 2722
	Author: Youssef ElGhareeb
	
	Idea: Dynamic programming
		define dp[350][2][2], where dp[position][switch_state][match] is the minimum number of switches
		that need to be pressed to make all lights from pos + 1 to the end matching, and the current switch matching or not matching
*/

#include <bits/stdc++.h>

using namespace std;

#define OFF 0
#define ON 1
#define MATCH 0
#define UNMATCH 1

const int MX_LEN = 350;

void divide_by_two (string& s) {
	int next_additive = 0;
	for (int i=0; i<s.length(); i++) {
		int additive = next_additive;
		int digit = s[i] - '0';
		if (digit % 2) next_additive = 5;
		else next_additive = 0;
		digit = digit / 2 + additive;
		s[i] = digit + '0';
	}
	int i = 0;
	while (i < s.length() - 1 && s[i] == '0') i++;
	s.erase(0, i);
}

string multiply (string s1, string s2) {
	reverse(s1.begin(), s1.end());
	reverse(s2.begin(), s2.end());
	int MX = s1.length() + s2.length() + 5;
	int a[MX];
	memset(a, 0, sizeof(a));
	for (int i=0; i<s1.length(); i++) {
		for (int j=0; j<s2.length(); j++) {
			a[i + j] += (s1[i]-'0') * (s2[j] - '0');
		}
	}
	for (int i=0; i<MX - 1; i++) {
		a[i + 1] += a[i] / 10;
		a[i] %= 10;
	}
	int i = MX - 1;
	while (i > 0 && a[i] == 0) i--;
	string result = "";
	for (; i>=0; i--) result += (char) (a[i] + '0');
	return result;
}

string add (string s1, string s2) {
	if (s1.length() > s2.length()) swap(s1, s2);
	reverse(s1.begin(), s1.end());
	reverse(s2.begin(), s2.end());
	string result(s2.length(), '0');
	int carry = 0, sum;
	for (int i=0; i < s1.length(); i++) {
		sum = s1[i] + s2[i] - 2 * '0' + carry;
		carry = sum / 10;
		sum %= 10;
		result[i] = (char) (sum + '0');
	}
	for (int i=s1.length(); i < s2.length(); i++) {
		sum = s2[i] - '0' + carry;
		carry = sum / 10;
		sum %= 10;
		result[i] = (char) (sum + '0');
	}
	reverse(result.begin(), result.end());
	if (carry > 0) result.insert(result.begin(), (char) (carry + '0'));
	return result;
}

string convert_to_bin(string decimal) {
	stack<int> digits;
	string binary = "";
	while (decimal != "0") {
		int len = decimal.length();
		int last = decimal[len - 1] - '0';
		digits.push(last % 2);
		divide_by_two(decimal);
	}
	while (!digits.empty()) {
		binary += (char) (digits.top() + '0');
		digits.pop();
	}
	return binary;
}

string convert_to_dec(string binary) {
	string pow2 = "1";
	int len = binary.length();
	int beg = 0;
	while (binary[beg] == '0') beg++;
	string result = "0";
	for (int i=len-1; i>=beg; i--) {
		if (binary[i] == '1') result = add(result, pow2);
		pow2 = multiply(pow2, "2");
	}
	return result;
}

bool equal(string& orig, string& target, int pos) {
	assert(pos < orig.length() && pos < target.length());
	if (orig[pos] == target[pos]) return true;
	return false;
}

int main () {
	// freopen("in.txt", "r", stdin);
	ios_base::sync_with_stdio(false);
	string initial_dec, final_dec, orig, target;
	int test = 1;
	while (cin>>initial_dec) {
		cin>>final_dec;
		if (initial_dec == "0" && final_dec == "0") break;
		if (test > 1) cout<<endl;
		cout<<"Case Number "<<test++<<": ";
		string orig = convert_to_bin(initial_dec);
		string target = convert_to_bin(final_dec);
		int o_len = orig.length();
		int t_len = target.length();
		int diff_len = abs(o_len - t_len);
		if (orig.length() < target.length()) 
			orig.insert(0, string(diff_len, '0'));
		else 
			target.insert(0, string(diff_len, '0'));
		if (orig.length() == 1) {
			if (orig[0] == target[0]) cout<<0<<endl;
			else cout<<1<<endl;
			continue;
		}
		int len = orig.length();
		int dp[MX_LEN][2][2]; 
		pair<int, int> next[MX_LEN][2][2];
		/* Initialize */
		for (int i=0; i<MX_LEN; i++) {
			for (int j=0; j<2; j++) 
				for (int k=0; k<2; k++) 
					dp[i][j][k] = MX_LEN;
		}
		if (equal(orig, target, len - 1)) {
			dp[len - 1][OFF][MATCH] = 0; /* Switch is off, both characters equal */
			dp[len - 1][ON][UNMATCH] = 1; /* Switch is on, characters not equal */
		}
		else {
			dp[len - 1][ON][MATCH] = 1; /* Switch is on, characters are equal */
			dp[len - 1][OFF][UNMATCH] = 0; /* Switch is off, characters not equal */
		}
		for (int i=len-2; i>=0; i--) {
			if (equal(orig, target, i)) {
				dp[i][OFF][MATCH] = dp[i+1][OFF][MATCH];
				dp[i][OFF][UNMATCH] = dp[i+1][ON][MATCH];
				dp[i][ON][MATCH] = 1 + dp[i+1][ON][UNMATCH];
				dp[i][ON][UNMATCH] = 1 + dp[i+1][OFF][UNMATCH];
				next[i][OFF][MATCH] = make_pair(OFF, MATCH);
				next[i][OFF][UNMATCH] = make_pair(ON, MATCH);
				next[i][ON][MATCH] = make_pair(ON, UNMATCH);
				next[i][ON][UNMATCH] = make_pair(OFF, UNMATCH);
			}
			else {
				dp[i][OFF][MATCH] = dp[i+1][ON][MATCH];
				dp[i][OFF][UNMATCH] = dp[i+1][OFF][MATCH];
				dp[i][ON][MATCH] = 1 + dp[i+1][OFF][UNMATCH];
				dp[i][ON][UNMATCH] = 1 + dp[i+1][ON][UNMATCH];
				next[i][OFF][MATCH] = make_pair(ON, MATCH);
				next[i][OFF][UNMATCH] = make_pair(OFF, MATCH);
				next[i][ON][MATCH] = make_pair(OFF, UNMATCH);
				next[i][ON][UNMATCH] = make_pair(ON, UNMATCH);
			}
		}
		int result = min(dp[0][ON][MATCH], dp[0][OFF][MATCH]);
		if (result >= MX_LEN) cout<<"impossible\n";
		else {
			string binary_sol = "";
			int l_state, match = MATCH;
			if (dp[0][ON][MATCH] < dp[0][OFF][MATCH]) 
				l_state = ON;
			else 
				l_state = OFF;
			for (int i=0; i<len; i++) {
				binary_sol += (char) (l_state + '0');
				int new_l_state, new_match;
				new_l_state = next[i][l_state][match].first;
				new_match = next[i][l_state][match].second;
				l_state = new_l_state;
				match = new_match;
			}
			cout<<convert_to_dec(binary_sol)<<endl;
		}
	}
	return 0;
}
