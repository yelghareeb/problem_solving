/*
	Algorithm for counting the number of inversions in an array
	This is similar to the merge sort 
	
	Author: Youssef ElGhareeb
*/

#include <bits/stdc++.h>
using namespace std;

#define loop(i,n) for(int i = 0; i < n; i++)
typedef long long LL;

const int MOD = 1e9 + 7;

int merge(vector<int>& v, int s, int mid, int e) {
    vector<int> aux(e - s + 1);
    int p1 = s, p2 = mid + 1, cntr = 0, invs = 0;
    while (p1 <= mid && p2 <= e) {
        if (v[p1] <= v[p2]) aux[cntr++] = v[p1++];
        else { 
            aux[cntr++] = v[p2++]; 
            invs += mid - p1 + 1;
        }
    }
    while (p1 <= mid) {
        aux[cntr++] = v[p1++];
    }
    while (p2 <= e) {
        aux[cntr++] = v[p2++];
    }
    loop(i, aux.size()) v[s++] = aux[i];
    return invs;
}

int _count_inversions(vector<int>& v, int s, int e) {
    if (s == e) return 0;
    int mid = (s + e) / 2;
    int res = 0;
    res += _count_inversions(v, s, mid);
    res += _count_inversions(v, mid + 1, e);
    res += merge(v, s, mid, e);
    return res;
}

int count_inversions(vector<int> v) {
    return _count_inversions(v, 0, v.size() - 1);
}

int main()
{
#ifdef DEBUG
    freopen("in.txt", "r", stdin);
#endif
    int a[] = {3, 5, 2, 4, 1};
    vector<int> v(a, a + 5);
    assert(7 == count_inversions(v));
    return 0;
}