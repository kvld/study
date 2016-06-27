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
 
const int MAXN = 100;
const int INF = 2 * (1e9) + 1;
const ll INF_64 = (1LL << 62);
const int MOD = 1000000007;
 
const double EPS = 1e-8;
const double PI = acos(-1.0);

int n, m;
int g[MAXN][MAXN];
vector<bool> used (MAXN, false);
vector<int> p (MAXN, -1);

bool bfs() {
    used.assign(MAXN, false);

    queue<int> q;
    q.push(0);
    used[0] = true;
    p[0] = -1;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int i = 0; i < n; i++) {
            if (!used[i] && g[v][i] > 0) {
                q.push(i);
                used[i] = true;
                p[i] = v;
            }
        }
    }

    return used[n - 1] == true;
}

int main()
{
    freopen("maxflow.in", "r", stdin);
    freopen("maxflow.out", "w", stdout);
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            g[i][j] = 0;
        }
    }
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g[--u][--v] = w;
    }
    int max_flow = 0;
    int c = 0;
    while (bfs()) {
        int flow = INF;
        int v = n - 1;
        while (v != 0) {
            flow = min(flow, g[p[v]][v]);
            v = p[v];
        }

        v = n - 1;
        while (v != 0) {
            //cerr << p[v] << '->' << v << g[p[v]][v] << endl;
            //cerr << v << '->' << p[v] << g[v][p[v]] << endl;
            g[p[v]][v] -= flow;
            g[v][p[v]] += flow;
            v = p[v];
        }
        //cerr << endl;

        max_flow += flow;
    }
    cout << max_flow;
    return 0;
}