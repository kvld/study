#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <string.h>
#include <cmath>
#include <map>
#include <vector>
#include <ctime>
#include <set>
#include <queue>
#include <deque>
#include <cassert>
#include <sstream>
#define all(a) a.begin(), a.end()
#define sz(a) (int)a.size()
#define sqr(x) (x) * (x)
#define pb push_back
#define mp make_pair
#define fr first
#define sc second
 
using namespace std;
 
typedef long long ll;
 
const int MAXN = 30000;
const double INF = 2 * (1e9) + 1;
const ll INF_64 = (1LL << 62);
const int MOD = 1000000007;
 
const double EPS = 1e-8;
const double PI = acos(-1.0);
 
int n;
vector<pair<int, int> > points;
vector<double> d (MAXN, INF + .0);
vector<bool> used (MAXN, false);
vector<int> pr (MAXN, -1);
double ans = .0;

double dist(int a, int b, int c, int d) {
    return sqrt(sqr(a - c) + sqr(b - d));
}

void prim()
{
    d[0] = 0.0;
    for (int i = 0; i < n; i++) {
        int cur = -1;
        for (int j = 0; j < n; j++) {
            if (!used[j] && (cur == -1 || d[cur] - EPS > d[j]))
                cur = j;
        }
        used[cur] = true;
        if (pr[cur] != -1)
            ans += dist(points[cur].fr, points[cur].sc, points[pr[cur]].fr, points[pr[cur]].sc);
        for (int j = 0; j < n; j++) {
            double dist_cur_j = dist(points[cur].fr, points[cur].sc, points[j].fr, points[j].sc);
            if (dist_cur_j + EPS < d[j]) {
                d[j] = dist_cur_j;
                pr[j] = cur;
            }
        }
    }
}

int main()
{
    freopen("spantree.in", "r", stdin);
    freopen("spantree.out", "w", stdout);
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        points.pb(mp(x, y));
    }
    prim();
    printf("%.8f", ans);
    return 0;
}