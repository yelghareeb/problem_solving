/*
	Live Archive 4794 - Sharing Chocolates
	Author: Youssef ElGhareeb
	Idea: Dynamic Programming
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long

short dp[105][(1 << 15) + 5], a[20];
vector<int> masks[105 * 105];
int sum [1 << 16];
int popcount [1 << 16];

int n, x, y;

bool solve(int _x, int _y, int _mask) {
	short& temp = dp[_x][_mask];
	if (temp != -1) return temp;
	bool res = false;
	if (sum[_mask] != _x * _y) {
		res = false;
	}
	else if (popcount[_mask] == 1) {
		res = true;
	}
	else {
		for (int i = 1; i < _x; i++) {
			vector<int>& options_left = masks[i * _y];
			for (int k = 0; k < options_left.size(); k++) {
				int mask_left = options_left[k];
				if (~_mask & mask_left) continue;
				int mask_right = mask_left ^ _mask;

				assert((mask_left | mask_right) == _mask);
				assert((mask_left & mask_right) == 0);
				assert(sum[mask_left] == i * _y);

				if (sum[mask_right] == (_x - i) * _y) {
					res |= solve(i, _y, mask_left) && solve(_x - i, _y, mask_right);
				}
				if (res) break;
			}
			if (res) break;
		}
		if (!res) {
			for (int i = 1; i < _y; i++) {
				vector<int>& options_left = masks[_x * i];
				for (int k = 0; k < options_left.size(); k++) {
					int mask_left = options_left[k];
					if (~_mask & mask_left) continue;
					int mask_right = mask_left ^ _mask;

					assert((mask_left | mask_right) == _mask);
					assert((mask_left & mask_right) == 0);
					assert(sum[mask_left] == _x * i);

					if (sum[mask_right] == _x * (_y - i)) {
						res |= solve(_x, i, mask_left) && solve(_x, _y - i, mask_right);
					}
					if (res) break;
				}
				if (res) break;
			}
		}
	}
	return temp = res;
}

int main() {
	int test_case = 0;
	while (cin >> n && n) {
		memset(dp, -1, sizeof(dp));
		cin >> x >> y;
		for (int i = 0; i < n; i++) {
			cin >> a[i];
		}
		for (int i = 0; i <= x * y; i++) {
			masks[i].clear();
		}
		for (int mask = 0; mask < (1 << n); mask++) {
			sum[mask] = popcount[mask] = 0;
			for (int k = 0; k < n; k++) {
				if ((mask >> k) & 1) {
					sum[mask] += a[k];
					popcount[mask]++;
				}
			}
			masks[sum[mask]].push_back(mask);
		}
		bool flag = solve(x, y, (1 << n) - 1);
		cout << "Case " << ++test_case << ": ";
		if (flag) cout << "Yes" << endl;
		else cout << "No" << endl;
	}
	return 0;
}