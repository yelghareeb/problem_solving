/*
	UVA 344
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

int a[5];

void handle_second(int i) {
	if (i <= 3) a[0] += i;
	else if (i == 4) {
		a[1]++;	a[0]++;
	}
	else if (i == 5) a[1]++;
	else if (i < 9) {
		a[0] += i - 5;
		a[1]++;
	}
	else if (i == 9) {
		a[2]++;
		a[0]++;
	}
}

void handle_first (int i) {
	if (i <= 3) a[2] += i;
	else if (i == 4) {
		a[2]++;
		a[3]++;
	}
	else if (i < 9) {
		a[3]++;
		a[2] += i - 5;
	}
	else {
		a[4]++;
		a[2]++;
	}
}

int main () {
	ios_base::sync_with_stdio(false);
	int n;
	while(cin>>n && n) {
		memset(a, 0, sizeof(a));
		for (int i=1; i<=n; i++) {
			int fn = i / 10;
			int sn = i % 10;
			
			handle_second(sn);
			if (fn > 0) handle_first(fn);
		}
		cout<<n<<": ";
		char syms [] = {'i', 'v', 'x', 'l', 'c'};
		cout<<a[0]<<" "<<syms[0];
		for (int j=1; j<5; j++) {
			cout<<", "<<a[j]<<" "<<syms[j];
		}
		cout<<endl;
	}
	return 0;
}