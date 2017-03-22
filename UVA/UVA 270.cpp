/*
	UVA 270
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

using namespace std;

#define ll long long
#define vi vector<int>
#define pb push_back
#define loop(i,n) for(int i=0; i<n; i++)
#define pii pair<int, int>

const double EPS = 0.000001;

int gcd(int x, int y) {
    if (y == 0) return x;
    return gcd(y, x % y);
}

/* This struct represents the slope of the line only, so it doesn't uniquely identify a line */
struct Line {
    int dx, dy;

    Line(int _dx, int _dy) {
        dx = _dx;
        dy = _dy;
        int g = gcd(dx, dy);
        dx /= g;
        dy /= g;
        if (dx < 0 && dy < 0) {
            dx *= -1;
            dy *= -1;
        }
}
    
    /* Overloading the < operator ensures uniqueness when we use a map */
    bool operator < (const Line& l2) const {
		if (dy == l2.dy) return dx < l2.dx;
		return dy < l2.dy;
    }
};

inline Line get_line (pii p1, pii p2) {
    int dx = p1.first - p2.first;
    int dy = p1.second - p2.second;
    Line l (dx, dy);
    return l;
}

int main() {
    int tests;
    scanf("%d", &tests);
    string s;
    getline(cin, s); // Dummy read
    getline(cin, s); // Dummy read
    while(tests--) {
        vector<pii> v;
        int cx, cy;
        bool end_of_input = true;
        while(getline(cin, s)){
            if (s == "\r" || s == "") break;
            sscanf(s.c_str(), "%d %d", &cx, &cy);
            v.push_back(make_pair(cx, cy));
        }
        int n = v.size();
        int res = 0;
        for (int i=0; i<n; i++) { // Consider a line passing by the ith point
            map<Line, int> cnts;
            for (int j=i + 1; j<n; j++) {
                Line line = get_line(v[i], v[j]);
                cnts[line]++;
                res = max(res, cnts[line] + 1);
            }
        }
        printf("%d\n", res);
        if (tests) printf("\n");
    }
    return 0;
}