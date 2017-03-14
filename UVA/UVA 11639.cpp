/*
	UVA 11639
	Author: Youssef ElGhareeb
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <cstring>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <map>
#include <assert.h>
 
using namespace std;
 
#define ll long long
#define vi vector<int>
#define pb push_back
#define loop(i,n) for(int i=0; i<n; i++)
#define pii pair<int, int>
#define mp make_pair
#define ABS(i) i<0?-i:i

struct Rectangle{
	int x1, y1, x2, y2;
	Rectangle(int _x1, int _y1, int _x2, int _y2) {
		x1 = _x1;
		y1 = _y1;
		x2 = _x2;
		y2 = _y2;
	}
};

int main () {
	freopen("in.txt", "r", stdin);
	int tests;
	cin>>tests;
	loop(test, tests) {
		int x1, y1, x2, y2;
		cin>>x1>>y1>>x2>>y2;
		Rectangle rect1(x1, y1, x2, y2);
		cin>>x1>>y1>>x2>>y2;
		Rectangle rect2(x1, y1, x2, y2);
		int area1 = (rect1.x2 - rect1.x1) * (rect1.y2 - rect1.y1);
		int area2 = (rect2.x2 - rect2.x1) * (rect2.y2 - rect2.y1);
		int x_intersec = max(0, min(rect1.x2, rect2.x2) - max(rect1.x1, rect2.x1));
		int y_intersec = max(0, min(rect1.y2, rect2.y2) - max(rect1.y1, rect2.y1));
		int strong = x_intersec * y_intersec;
		int weak = area1 + area2 - 2 * strong;
		int unsecured = 100 * 100 - (weak + strong);
		cout<<"Night "<<test + 1<<": ";
		cout<<strong<<" "<<weak<<" "<<unsecured<<endl;
	}
	return 0;
}