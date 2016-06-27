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

const int MAXN = 500;
const int INF = 2 * (1e9) + 1;
const ll INF_64 = (1LL << 62);
const int MOD = 1000000007;

const double EPS = 1e-8;
const double PI = acos(-1.0);

struct edge {
    int u;
    int v;
    int w;
    edge(int __u, int __v, int __w) {
        u = __u;
        v = __v;
        w = __w;
    }
};

int n, m;
vector<edge> g;
int d[MAXN];
int parent[MAXN];
vector<int> path;

int main()
{
    freopen("negcycle.in", "r", stdin);
    freopen("negcycle.out", "w", stdout);
    cin >> n;
    m = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int ww;
            cin >> ww;
            if (ww != 1000000000) {
                g.pb(edge(i, j, ww));
                m++;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        d[i] = 0;
        parent[i] = -1;
    }
    int last_updated = -1;
    for (int k = 0; k < n; k++) {
        last_updated = -1;
        for (int i = 0; i < m; i++) {
            edge cur = g[i];
            if (d[cur.u] < INF) {
                if (d[cur.v] > d[cur.u] + cur.w) {
                    d[cur.v] = max(-INF, d[cur.u] + cur.w);
                    parent[cur.v] = cur.u;
                    last_updated = cur.v;
                }
            }
        }
    }
    if (last_updated == -1) {
        cout << "NO";
    } else {
        cout << "YES" << endl;
        int cur = last_updated;
        for (int i = 0; i < n; i++) {
            cur = parent[cur];
        }

        int y = cur;
        while (y != -1) {
            path.pb(y);
            if (sz(path) > 1 && cur == y)
                break;
            y = parent[y];
        }
        reverse(all(path));
        cout << sz(path) << endl;
        for (int i = 0; i < sz(path); i++) {
            cout << path[i] + 1 << ' ';
        }
    }
    return 0;
}
