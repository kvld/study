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

const int MAXN = 10000;
const double INF = 2 * (1e9) + 1;
const ll INF_64 = (1LL << 62);
const int MOD = 1000000007;

const double EPS = 1e-8;
const double PI = acos(-1.0);

int n, m;
vector<vector<int> > g (100000);
int color[100000];
int cnt = 0;

void dfs(int u)
{
    for (int i = 0; i < sz(g[u]); i++) {
        int v = g[u][i];
        if (color[v] == 0) {
            color[v] = (color[u] == 1 ? 2 : 1);
            dfs(v);
        } else if (color[v] == color[u]) {
            cout << "NO";
            exit(0);
        }
    }
}

int main()
{
    freopen("bipartite.in", "r", stdin);
    freopen("bipartite.out", "w", stdout);
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        g[--u].pb(--v);
        g[v].pb(u);
    }
    for (int i = 0; i < n; i++)
        color[i] = 0;
    for (int i = 0; i < n; i++) {
        if (color[i] == 0) {
            color[i] = 1;
            dfs(i);
        }
    }
    cout << "YES";
    return 0;
}
