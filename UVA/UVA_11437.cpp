#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <sstream>
#include <queue>
#include <cstring>
#include <cmath>
using namespace std;

#define loop(i,n) for(int i=0; i<n; i++)
#define ll long long
#define pii pair<int, int>
#define pb push_back

const double EPS = 0.000000000001;

struct Point{
	double x, y;
	Point() {}
	Point(double _x, double _y) {
		x = _x;
		y = _y;
	}
	bool operator < (Point other) {
		if(fabs(x - other.x) < EPS) {
			return x < other.x;
		}
		return y < other.y;
	}
};

struct Line {
	double a, b, c;
};

Line points_to_line(Point p1, Point p2) {
	Line l;
	if (fabs(p1.x - p2.x) < EPS) { // Vertical line
		l.a = 1.0; 
		l.b = 0.0;
		l.c = -p1.x;
	}
	else {
		l.a = -(double)(p1.y - p2.y) / (p1.x - p2.x);
		l.b = 1.0;
		l.c = -(double)(l.a * p1.x) - (l.b * p1.y);
	}
	return l;
}

Point get_intersection (Line l1, Line l2) {
	Point p;
	p.x = (l2.b * l1.c - l1.b * l2.c) / (l2.a * l1.b - l1.a * l2.b);
	if (fabs(l1.b) > EPS) { // Test for vertical line
		p.y = - (l1.a * p.x + l1.c) / l1.b; // Avoid division by zero
	}
	else {
		p.y = - (l2.a * p.x + l2.c) / l2.b;
	}
	return p;
}

int main() {
	ios_base::sync_with_stdio(false);
	int tests;
	cin>>tests;
	loop(test, tests) {
		Point a, b, c, d, e, f;
		cin>>a.x>>a.y>>b.x>>b.y>>c.x>>c.y;
		d.x = b.x + (c.x - b.x) / 3.0;
		d.y = b.y + (c.y - b.y) / 3.0;
		e.x = c.x + (a.x - c.x) / 3.0;
		e.y = c.y + (a.y - c.y) / 3.0;
		f.x = a.x + (b.x - a.x) / 3.0;
		f.y = a.y + (b.y - a.y) / 3.0;
		Line ad = points_to_line(a, d);
		Line be = points_to_line(b, e);
		Line cf = points_to_line(c, f);
		Point r = get_intersection(cf, ad);
		Point p = get_intersection(be, ad);
		Point q = get_intersection(cf, be);
		double area = ( (r.x - q.x) * (p.y - r.y) - (r.x - p.x) * (q.y - r.y)) / 2.0;
		cout<<(int)(area + 0.5)<<endl;
	}
	return 0;
}