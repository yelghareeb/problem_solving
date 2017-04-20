/*
	Topcoder SRM 446 - D2 1000
	Author: Youssef ElGhareeb
	
	Idea: Use the meet in the middle technique to solve the problem.
		Start from the initial state and do a BFS with a MAX distance constraint.
		If you didn't reach the goal state within this distance, memorize the middle states
		and start from the goal state and do a backwards BFS, searching for the middle states
		Note that the max distance should be greater than the max possible answer / 2
*/

#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <queue>
#include <cstdlib>
#include <ctime>

using namespace std;

class HanoiTower {
public:
	int moves(string, string, string);
};

const int MX_ITERATIONS = 10;

struct Step {
	string a, b, c;
	Step(string _a, string _b, string _c) {
		a = _a;
		b = _b;
		c = _c;
	}
	bool is_goal() {
		for (int i=0; i<a.length(); i++) if (a[i] != 'A') return false;
		for (int i=0; i<b.length(); i++) if (b[i] != 'B') return false;
		for (int i=0; i<c.length(); i++) if (c[i] != 'C') return false;
		return true;
	}
	bool operator < (const Step& step2) const {
		if (a == step2.a) {
			if (b == step2.b) {
				if (c < step2.c) return true;
				return false;
			}
			if (b < step2.b) return true;
			return false;
		}
		if (a < step2.a) return true;
		return false;
	}
};

map<Step, int> vis, middle;

void enqueue_children(queue<pair<Step, int> >& q, Step step, int dist) {
	string a, b, c;
	a = step.a;
	b = step.b;
	c = step.c;
	if (!a.empty()) {
		Step st1 = Step(a.substr(0, a.length() - 1), b + a[a.length() - 1], c);
		Step st2 = Step(a.substr(0, a.length() - 1), b, c + a[a.length() - 1]);
		if (vis.count(st1) == 0) {
			vis[st1] = dist + 1;
			q.push(make_pair(st1, dist + 1));
		}
		if (vis.count(st2) == 0) {
			vis[st2] = dist + 1;
			q.push(make_pair(st2, dist + 1));
		}
	}
	if (!b.empty()) {
		int blen = b.length();
		Step st1 = Step(a + b[blen - 1], b.substr(0, b.length() - 1), c);
		Step st2 = Step(a, b.substr(0, b.length() - 1), c + b[blen - 1]);
		if (vis.count(st1) == 0) {
			vis[st1] = dist + 1;
			q.push(make_pair(st1, dist + 1));
		}
		if (vis.count(st2) == 0) {
			vis[st2] = dist + 1;
			q.push(make_pair(st2, dist + 1));
		}
	}
	if (!c.empty()) {
		int clen = c.length();
		Step st1 = Step(a + c[clen - 1], b, c.substr(0, clen - 1));
		Step st2 = Step(a, b + c[clen - 1], c.substr(0, clen - 1));
		if (vis.count(st1) == 0) {
			vis[st1] = dist + 1;
			q.push(make_pair(st1, dist + 1));
		}
		if (vis.count(st2) == 0) {
			vis[st2] = dist + 1;
			q.push(make_pair(st2, dist + 1));
		}
	}
}

int HanoiTower::moves(string pegA, string pegB, string pegC) {
	int cnta = 0, cntb = 0, cntc = 0;
	string pegs[] = {pegA, pegB, pegC};
	for (int i=0; i<3; i++) {
		for (int j=0; j<pegs[i].length(); j++) {
			if (pegs[i][j] == 'A') cnta++;
			else if (pegs[i][j] == 'B') cntb++;
			else cntc++;
		}
	}
	/* Start from the initial state and go forward */
	Step orig(pegA, pegB, pegC);
	queue<pair<Step, int> > q;
	q.push(make_pair(orig, 0));
	while (!q.empty()) {
		pair<Step, int> front = q.front();
		q.pop();
		Step& step = front.first;
		int distance = front.second;
		if (distance > MX_ITERATIONS) break;
		if (step.is_goal()) return distance;
		if (distance == MX_ITERATIONS) middle[step] = distance;
		vis[step] = distance;
		enqueue_children(q, step, distance);	
	}
	
	/* Start from the goal state and go backward */
	vis.clear();
	queue<pair<Step, int> > q2;
	Step goal = Step(string(cnta, 'A'), string(cntb, 'B'), string(cntc, 'C'));
	q2.push(make_pair(goal, 0));
	while (!q2.empty()) {
		pair<Step, int> front = q2.front();
		q2.pop();
		Step& step = front.first;
		int distance = front.second;
		if (middle.count(step) > 0) return distance + middle[step];
		vis[step] = 1;
		enqueue_children(q2, step, distance);
	}
	return -1;
}


//Powered by [KawigiEdit] 2.0!