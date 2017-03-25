/*
	UVA 477
	Author: Youssef ElGhareeb
*/

#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define vi vector<int>
#define pb push_back
#define loop(i,n) for(int i=0; i<n; i++)
#define pii pair<int, int>
#define pdd pair<double, double>

const int MX_PTS = 1e6 + 5;
const double EPS = 0.000000001;
vector<int> pts[MX_PTS];

struct Rect{
	double x1, y1, x2, y2;
	int fig_num;
	Rect(double _x1, double _y1, double _x2, double _y2, int c) {
		x1 = _x1;
		y1 = _y1;
		x2 = _x2;
		y2 = _y2;
		if (x1 > x2) swap(x1, x2);
		if (y1 > y2) swap(y1, y2);
		fig_num = c;
	}
};

struct Circle {
	double x, y, r;
	int fig_num;
	Circle(double _x, double _y, double _r, int c) {
		x = _x;
		y = _y;
		r = _r;
		fig_num = c;
	}
};

double dist (Circle c, double x, double y) {
	double dx = c.x - x;
	double dy = c.y - y;
	return sqrt(dx * dx + dy * dy);
}

int main () {
	char c;
	vector<Rect> rects;
	vector<Circle> circles;
	int n = 0; //Number of figures
	while (cin>>c && c != '*') {
		if (c == 'c') {
			double x, y, r;
			cin>>x>>y>>r;
			circles.push_back(Circle(x, y, r, n + 1));
		}
		else {
			double x1, y1, x2, y2;
			cin>>x1>>y1>>x2>>y2;
			rects.push_back(Rect(x1, y1, x2, y2, n + 1));
		}
		++n;
	}
	int pnt_ctr = 1;
	while (true) {
		double x, y;
		cin>>x>>y;
		if (abs(x - 9999.9) < EPS && abs(y - 9999.9) < EPS) break;
		for (int i=0; i<rects.size(); i++) {
			if (x > rects[i].x1 && x < rects[i].x2 && y > rects[i].y1 && y < rects[i].y2) {
				pts[pnt_ctr].push_back(rects[i].fig_num);
			}
		}
		for (int i=0; i<circles.size(); i++) {
			if (dist(circles[i], x, y) < circles[i].r) {
				pts[pnt_ctr].push_back(circles[i].fig_num);
			}
		}
		++pnt_ctr;
	}
	for (int i=1; i<pnt_ctr; i++) {
		if (pts[i].empty()) {
			cout<<"Point "<<i<<" is not contained in any figure"<<endl;
		}
		else {
			sort(pts[i].begin(), pts[i].end());
			for (int j=0; j<pts[i].size(); j++) {
				cout<<"Point "<<i<<" is contained in figure "<<pts[i][j]<<endl;
			}
		}
	}
	return 0;
}