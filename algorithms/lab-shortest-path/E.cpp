
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
 
const int MAXN = 2000;
const ll INF = 9LL * (ll)1e18;
const ll INF_64 = (1LL << 62);
const int MOD = 1000000007;
 
const double EPS = 1e-8;
const double PI = acos(-1.0);
 
struct edge {
    int u;
    int v;
    ll w;
    edge(int __u, int __v, ll __w) {
        u = __u;
        v = __v;
        w = __w;
    }
};
 
int n, m, s;
vector<edge> g;
vector<int> gn[MAXN];
ll d[MAXN];
int p[MAXN];
bool used[MAXN];

void dfs(int v) {
    used[v] = true;
    for (int i = 0; i < sz(gn[v]); i++) {
        int to = gn[v][i];
        if (!used[to])
            dfs(to);
    }
}
 
int main()
{
    freopen("path.in", "r", stdin);
    freopen("path.out", "w", stdout);
    cin >> n >> m >> s;
    --s;
    for (int i = 0; i < m; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        --u, --v;
        g.pb(edge(u, v, w));
        gn[u].pb(v);
    }
    for (int i = 0; i < n; i++) {
        d[i] = INF;
        p[i] = -1;
    }
    d[s] = 0;
    int last_updated = -1;
    for (int k = 0; k < n; k++) {
        last_updated = -1;
        for (int i = 0; i < m; i++) {
            edge cur = g[i];
            if (d[cur.u] < INF) {
                if (d[cur.v] > d[cur.u] + cur.w) {
                    d[cur.v] = max(-INF, d[cur.u] + cur.w);
                    p[cur.v] = cur.u;
                    last_updated = cur.v;
                }
            }
        }
    }
    set<int> on_cycle;
    if (last_updated != -1) {
        int cur = last_updated;
        for (int i = 0; i < n; i++) {
            cur = p[cur];
        }

        int y = cur;
        vector<int> path;
        bool can = false;
        while (y != -1) {
            path.pb(y);
            if (d[y] != INF) {
                can = true;
            }
            y = p[y];
            if (sz(path) > 1 && cur == y)
                break;
        }
        if (can) {
            for (int i = 0; i < sz(path); i++) {
                on_cycle.insert(path[i]);
            }
            for (int i = 0; i < n; i++)
                used[i] = false;
            dfs(path[0]);
            for (int i = 0; i < n; i++) 
                if (used[i])
                    on_cycle.insert(i);
        }
    }
    for (int i = 0; i < n; i++) {
        if (on_cycle.count(i)) {
            cout << "-" << endl;
            continue;
        }
        if (d[i] == INF) 
            cout << "*" << endl;
        else 
            cout << d[i] << endl;
    }
    return 0;
}