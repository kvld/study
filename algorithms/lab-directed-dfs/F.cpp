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
vector<int> topsort;
set<pair<int, int> > edges;
int used[100000];

void dfs(int u) {
    used[u] = 1;
    for (int i = 0; i < sz(g[u]); i++) {
        int v = g[u][i];
        if (used[v] == 1) {
            cout << -1;
            exit(0);
        }
        if (used[v] == 0)
            dfs(v);
    }
    used[u] = 2;
    topsort.pb(u);
}


int main()
{
    freopen("hamiltonian.in", "r", stdin);
    freopen("hamiltonian.out", "w", stdout);
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        g[--u].pb(--v);
        edges.insert(mp(u, v));
    }
    for (int i = 0; i < n; i++)
        used[i] = 0;
    for (int i = 0; i < n; i++)
        if (used[i] == 0)
            dfs(i);
    reverse(all(topsort));
    for (int i = 0; i < sz(topsort) - 1; i++) {
        bool has_edge = edges.count(mp(topsort[i], topsort[i + 1]));
        if (!has_edge) {
            cout << "NO";
            exit(0);
        }
    }
    cout << "YES";
    return 0;
}
