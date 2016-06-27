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
vector<vector<int> > g (20000);
vector<vector<int> > tg (20000);
int ans[20000];
vector<int> topsort;
int used[20000];

void dfs(int u) {
    used[u] = 1;
    for (int i = 0; i < sz(g[u]); i++) {
        int v = g[u][i];
        if (used[v] == 0)
            dfs(v);
    }
    topsort.pb(u);
}

void dfs_cond(int u, int numb) {
    ans[u] = numb;
    used[u] = 1;
    for (int i = 0; i < sz(tg[u]); i++) {
        int v = tg[u][i];
        if (used[v] == 0) 
            dfs_cond(v, numb);
    }
}

int main()
{
    freopen("cond.in", "r", stdin);
    freopen("cond.out", "w", stdout);
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        g[--u].pb(--v);
        tg[v].pb(u);
    }
    for (int i = 0; i < n; i++)
        used[i] = ans[i] = 0;
    for (int i = 0; i < n; i++)
        if (used[i] == 0)
            dfs(i);
    reverse(all(topsort));
    for (int i = 0; i < n; i++)
        used[i] = 0;
    int cond_numb = 1;
    for (int i = 0; i < sz(topsort); i++) {
        if (used[topsort[i]] == 0)
            dfs_cond(topsort[i], cond_numb), cond_numb++;
    }
    cout << cond_numb - 1 << endl;
    for (int i = 0; i < n; i++)
        cout << ans[i] << ' ';
    return 0;
}
