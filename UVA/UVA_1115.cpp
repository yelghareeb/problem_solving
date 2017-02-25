/*
	UVA 1115
	Author: Youssef ElGhareeb
*/

#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define vi vector<int>
#define pb push_back
#define loop(i,n) for(int i=0; i<n; i++)
#define pii pair<int, int>

int n;

struct Cube {
    double base;
    double height;
    double width;
    double depth;
    Cube(double b, double h, double w, double d) {
        base  = b;
        height = h;
        width = w;
        depth = d;
    }
    Cube(){}
};

vector<Cube> v;
const double EPS = 0.00000000001;

bool sort_base(const Cube& cube1, const Cube& cube2) {
    return cube1.base < cube2.base;
}

struct Sort_end {
    bool operator () (const Cube& cube1, const Cube& cube2) {
        return cube1.base + cube1.height > cube2.base + cube2.height;
    }    
};

int main () {
    int tests;
    scanf("%d", &tests);
    loop(test, tests) {
        scanf("%d", &n);
        v.clear();
        v.resize(n);
        loop(i, n) {
            double b, h, w, d;
            scanf("%lf%lf%lf%lf", &b, &h, &w, &d);
            v[i] = Cube(b, h, w, d);
        }
        double total_vol;
        scanf("%lf", &total_vol);
        sort(v.begin(), v.end(), sort_base);
        priority_queue<Cube, vector<Cube>, Sort_end> pq;
        pq.push(v[0]);
        double area = v[0].width * v[0].depth;
        double final_height = v[0].base;
        bool finished = false;
        for (int i=1; i<n && !finished; i++) {
            if (pq.empty()) {
                pq.push(v[i]);
                area += v[i].width * v[i].depth;
                final_height = v[i].base;
            }
            else if (v[i].base < pq.top().base + pq.top().height) {
                double delta_height = v[i].base - final_height;
                if (total_vol >= area * delta_height) {
                    total_vol -= area * delta_height;
                    final_height = v[i].base;
                }
                else {
                    final_height += total_vol / area;
                    finished = true;
                    total_vol = -EPS;
                    break;
                }
                area += v[i].width * v[i].depth;
                pq.push(v[i]);
            }
            else {
                while (!pq.empty() && v[i].base >= pq.top().base + pq.top().height) {
                    Cube c = pq.top();
                    pq.pop();
                    double delta_height = c.base + c.height - final_height;
                    if (total_vol >= delta_height * area) {
                        total_vol -= delta_height * area;
                        final_height = c.base + c.height;
                        area -= c.width * c.depth;
                    }
                    else {
                        final_height += total_vol / area;
                        total_vol = -EPS;
                        finished = true;
                        break;
                    }
                }
                i--;
            }   
        }
        if (!finished) {
            while (!pq.empty()) {
                Cube c = pq.top();
                pq.pop();
                double delta_height = c.base + c.height - final_height;
                if (total_vol >= delta_height * area) {
                    total_vol -= delta_height * area;
                    final_height = c.base + c.height;
                    area -= c.width * c.depth;
                }
                else {
                    final_height += total_vol / area;
                    total_vol = -EPS;
                    break;
                }
            }
        }
        if (total_vol > 0) printf("OVERFLOW\n");
        else printf("%.2lf\n", final_height);
        if (test < tests - 1) printf("\n");
    }
    return 0;
}