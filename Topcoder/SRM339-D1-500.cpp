/*
	SRM339-D1-500
	Author: Youssef ElGhareeb
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
#include <cstdlib>
#include <ctime>

using namespace std;

class TestBettingStrategy {
public:
	double winProbability(int, int, int, int);
};

double dp[55][1005][12];
int vis[55][1005][12];
double win_prob;
int mx_rounds;

/* This function calculates the probability of reaching the goal sum, given the following parameters:
	1. We are in round number "round"
	2. We currently have a sum of "cur_sum"
	3. The bet that we are going to do in this round is 2^bet
*/
double solve(int round, int cur_sum, int bet, const int& goal_sum) {
	/* If we reached the goal_sum already, then the probability is 1.0 */
	if (cur_sum >= goal_sum) return 1.0;
	
	/* If we exceeded the number of round, then the probability is 0 */
	if (round >= mx_rounds) return 0;
	
	/* If the bet we need to make in this round is greater than the amount we have, then the probability is 0 */
	if ( (1<<bet) > cur_sum) return 0;
	
	/* If this state was previously calculated, then return its probability */
	if (vis[round][cur_sum][bet]) return dp[round][cur_sum][bet];
	
	/* Mark this state as visited */
	vis[round][cur_sum][bet] = 1;
	
	/* If we win in the current state, then our amount will increase by 2^bet, and we will bet an amount of 1 in the next round */
	double p_win = win_prob * solve(round + 1, cur_sum + (1<<bet), 0, goal_sum);
	
	/* If we lose in the current state, then our amount will decrease by 2^bet, and we will bet an amount of 2^(bet + 1) in the next round */
	double p_lose = (1 - win_prob) * solve(round + 1, cur_sum - (1<<bet), bet + 1, goal_sum);
	
	return dp[round][cur_sum][bet] = p_win + p_lose;
}

double TestBettingStrategy::winProbability(int initSum, int goalSum, int rounds, int prob) {
	win_prob = 1.0 * prob / 100;
	mx_rounds = rounds;
	return solve(0, initSum, 0, goalSum);	
}


//Powered by [KawigiEdit] 2.0!