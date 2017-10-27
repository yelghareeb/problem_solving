/*
	UVA 10136
	Author: Youssef ElGhareeb
	
	Idea:
	1. Try to center a circle at each of the given points (with diameter = 5), 
	   and calculate the max number of points inside this circle.
	2. For each pair of points, get the circle of diameter 5 where the 2 points lie on its circumference,
	   and calculate the max number of points inside this circle.
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

using namespace std;

#define ll long long
#define vi vector<int>
#define pb push_back
#define loop(i,n) for(int i=0; i<n; i++)
#define pii pair<int, int>
#define pdd pair<double, double>

const double radius = 2.5;
const double EPS = 1e-6;
vector<pair<double, double > > pts;

double get_distance (pdd p1, pdd p2) {
	return sqrt(pow(p1.first - p2.first, 2.0) + pow(p1.second - p2.second, 2.0));
}

pdd get_center (pdd p1, pdd p2, int dir) {
	/* Get the middle point of p1 & p2 */
	double mid_x = (p1.first + p2.first) / 2.0;
	double mid_y = (p1.second + p2.second) / 2.0;

	/* Get a vector from point 1 to point 2 */
	double dx = (p1.first - p2.first) / 2.0; 
	double dy = (p1.second - p2.second) / 2.0;

	/* Distance between p1 and the mid point */
	double dist = sqrt(dx * dx + dy * dy);

	/* Distance from the midpoint to the center of the circle */
	double p_dist = sqrt (radius * radius - dist * dist);

	double mdx, mdy;
	if (dir) {
		mdx = dy * p_dist / dist;
		mdy = -dx * p_dist / dist;
	}
	else {
		mdx = -dy * p_dist / dist;
		mdy = dx * p_dist / dist;
	}
	return make_pair(mid_x + mdx, mid_y + mdy);
}

int count_points_in_circle(pdd center) {
	int inside = 0;
	/* Get the number of points in this circle */
	for (int i=0; i<pts.size(); i++) {
		if (get_distance(pts[i], center) <= radius + EPS) inside++;
	}
	return inside;
}

int main() {
	freopen("in.txt", "r", stdin);
    int tests;
    scanf("%d", &tests);
    string s;
    getline(cin, s); // Dummy read
    getline(cin, s); // Dummy read
    while(tests--) {
        pts.clear();
        double cx, cy;
        bool end_of_input = true;
        while(getline(cin, s)){
            if (s == "\r" || s == "") break;
            sscanf(s.c_str(), "%lf %lf", &cx, &cy);
            pts.push_back(make_pair(cx, cy));
        }
		int res = 0;
		for (int i=0; i<pts.size(); i++) {
			/* Get the max number of points in the circle centered at pts[i] */
			res = max(res, count_points_in_circle(pts[i]));
			for (int j=i + 1; j<pts.size(); j++) {
				double dist = get_distance(pts[i], pts[j]);
				if (dist > 2 * radius) continue;
				for (int k=0; k<2; k++) {
					/* Get the center of the circle, where pts[i] and pts[j] lie on its circumference */
					pair<double, double> center = get_center(pts[i], pts[j], k);
					res = max(res, count_points_in_circle(center));
				}
			}
		}
		printf("%d\n", res);
		if(tests) printf("\n");
	}
}