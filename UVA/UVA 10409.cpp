/*
	UVA 10409
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
#include <algorithm>
#include <time.h>
#include <cstring>
#include <queue>
#include <set>
#include <sstream>

using namespace std;

#define ll long long
#define vi vector<int>
#define pb push_back
#define loop(i,n) for(int i=0; i<n; i++)
#define pii pair<int, int>
#define pdd pair<double, double>

void conv(int faces[], int flag) {
	int tmp[6];
	if (flag == 0) { // North
		tmp[0] = faces[4];
		tmp[1] = faces[0];
		tmp[2] = faces[2];
		tmp[3] = faces[3];
		tmp[4] = faces[5];
		tmp[5] = faces[1];
	}
	else if (flag == 1) { // South
		tmp[0] = faces[1];
		tmp[1] = faces[5];
		tmp[2] = faces[2];
		tmp[3] = faces[3];
		tmp[4] = faces[0];
		tmp[5] = faces[4];
	}
	else if (flag == 2) { // East
		tmp[0] = faces[2];
		tmp[1] = faces[1];
		tmp[2] = faces[5];
		tmp[3] = faces[0];
		tmp[4] = faces[4];
		tmp[5] = faces[3];
	}
	else if (flag == 3) { // West
		tmp[0] = faces[3];
		tmp[1] = faces[1];
		tmp[2] = faces[0];
		tmp[3] = faces[5];
		tmp[4] = faces[4];
		tmp[5] = faces[2];
	}
	for(int i=0; i<6; i++) faces[i] = tmp[i];
}

int main () {
	ios_base::sync_with_stdio(false);
	int n;
	while (cin>>n && n) {
		int top = 1;
		int faces[] = {1, 2, 3, 4, 5, 6};
		for (int i=0; i<n; i++) {
			string s;
			cin>>s;
			if (s == "north") conv(faces, 0);
			if (s == "south") conv(faces, 1);
			if (s == "east") conv(faces, 2);
			if (s == "west") conv(faces, 3);
		}
		cout<<faces[0]<<endl;
	}
	return 0;
}	