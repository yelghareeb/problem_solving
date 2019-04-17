/*  
 * Author: Youssef Elghareeb
 */

#include <bits/stdc++.h>
using namespace std;

#define loop(i,n) for(int i = 0; i < n; i++)
#define pii pair<int, int>
#define all(v) v.begin(),v.end()
#define S second
#define F first
#define vi vector<int>
#define pb push_back

typedef long long LL;

const double INF = 1e9;
const int MOD = 1e9 + 7;

#define vpii vector<pii>

LL getRandomNumber() {
    srand (time(NULL));
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    return rng();
}

void randomShuffle(vector<int>& v) {
    srand (time(NULL));
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    shuffle(v.begin(), v.end(), rng);
}

void printArray(vector<int>& v) {
    for(int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl;
}

int main() {
#ifdef DEBUG
    freopen("in.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    vector<int> v(10);
    for (int i = 1; i <= 10; i++) v[i - 1] = i;
    cout << "Initial array: " << endl;
    printArray(v);
    randomShuffle(v);
    cout << "Array after shuffling: " << endl;
    printArray(v);
    cout << "Some random numbers: " << endl;
    for (int i = 0; i < 10; i++) {
        cout << getRandomNumber() << " ";
    }
    cout << endl;
    return 0;
}