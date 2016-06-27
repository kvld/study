
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
 
struct edge {
    int v;
    int w;
    edge(int __v, int __w) {
        v = __v;
        w = __w;
    }
};
 
int n, m, s, t;
vector<edge> g[MAXN];
int d[MAXN];
bool used[MAXN];
 
void dijkstra(int start)
{
    for (int i = 0; i < n; i++)
        d[i] = INF, used[i] = false;
    d[start] = 0;
    for (int i = 0; i < n; i++) {
        int cur = -1;
        for (int j = 0; j < n; j++) {
            if (!used[j] && (cur == -1 || d[j] < d[cur])) {
                cur = j;
            }
        }
        if (d[cur] == INF) {
            break;
        } else {
            used[cur] = true;
        }
        for (int j = 0; j < g[cur].size(); j++) {
            int to = g[cur][j].v;
            if (d[to] > d[cur] + g[cur][j].w) {
                d[to] = d[cur] + g[cur][j].w;
            }
        }
    }
}
 
int main()
{
    freopen("pathmgep.in", "r", stdin);
    freopen("pathmgep.out", "w", stdout);
    cin >> n >> s >> t;
    --s, --t;
    int ww;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &ww);
            if (ww != -1 && ww != 0) {
                g[i].pb(edge(j, ww));
            }
        }
    }
    dijkstra(s);
    printf("%d\n", (d[t] == INF ? -1 : d[t]));
    return 0;
}