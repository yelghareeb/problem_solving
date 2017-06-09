/*
	PKU 3251 - Big Square
	Author: Youssef ElGhareeb
	Geometry
*/

#include <iostream>
#include <string>
#include <queue>
#include <iomanip>
#include <assert.h>
#include <cstring>
#include <assert.h>
using namespace std;

#define ll long long

const short N = 105;

int main() {
	int n;
	char s[N][N];
	scanf ("%d", &n);
	for (short i = 0; i < n; i++) {
		scanf("%s", &s[i]);
	}
	int res = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (s[i][j] != 'J') continue;
			for (int y = n - 1; y >= 0; y--) {
				for (int x = n - 1; x >= j; x--) {
					if (s[y][x] != 'J') continue;
					for (int k = -1; k <= 1; k += 2) {
						int vx = (x - j);
						int vy = (y - i);
						int area = vx * vx + vy * vy;
						if (area < res) continue;
						int pvx = -vy * k;
						int pvy = vx * k;
						int p3y = i + pvy;
						int p3x = j + pvx;
						int p4y = y + pvy;
						int p4x = x + pvx;
						if (p3x >= 0 && p3x < n && p3y >= 0 && p3y < n && p4y >=0 && p4y < n && p4x >= 0 && p4x < n) {
							if (s[p3y][p3x] == 'J' && s[p4y][p4x] == 'J') {
								res = max(res, area);
							}
							else if (s[p3y][p3x] == 'J' && s[p4y][p4x] == '*') {
								res = max(res, area);
							}
							else if (s[p3y][p3x] == '*' && s[p4y][p4x] == 'J') {
								res = max(res, area);
							}
						}
					}
				}
			}
		}
	}
	printf ("%d\n", res);
	return 0;
}