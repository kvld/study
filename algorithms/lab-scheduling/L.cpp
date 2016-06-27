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

const int MAXN = 200;
const int INF = 2 * (1e9) + 1;
const ll INF_64 = (1LL << 62);
const int MOD = 1000000007;

const double EPS = 1e-8;
const double PI = acos(-1.0);

struct job {
    int d, num, d_dupl;    

    bool operator<(job const& rhs) const {
        return d < rhs.d;
    }
};

int n, m;
vector<job> a;
vector<vector<int> > g, rg;

int leaf = -1;
void dfs_leaf(int v) {
    leaf = v;
    for (int i = 0; i < sz(g[v]); i++) {
        dfs_leaf(g[v][i]);
    }
}

void dfs_d(int v) {
    for (int i = 0; i < sz(rg[v]); i++) {
        int u = rg[v][i];
        a[u].d = min(a[u].d, a[v].d - 1);
        dfs_d(u);
    }
}

int main() {
    freopen("pintreep1l.in", "r", stdin);
    freopen("pintreep1l.out", "w", stdout);
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        int t;
        cin >> t;
        a.pb(job{t, i, t});
    }
    g.resize(n);
    rg.resize(n);
    for (int i = 0; i < n - 1; i++) {
        int x, y;
        cin >> x >> y;
        x--, y--;
        g[x].pb(y);
        rg[y].pb(x);
    }
    dfs_leaf(0);
    dfs_d(leaf);
    sort(all(a));
    
    ll F = 0;
    vector<ll> r (n, 0);
    vector<ll> q (n, 0); 
    vector<ll> x (n, 0);
    
    for (int i = 0; i < n; i++) {
        int k = a[i].num;
        ll t = max(r[k], F);

        x[k] = t;

        q[t]++;
        if (q[t] == m) {
            F = t + 1;
        }

        if (sz(g[k]) > 0) {
            int j = g[k][0];
            r[j] = max(r[j], t + 1);
        }
    }
    ll ans = -INF;
    for (int i = 0; i < n; i++) {
        int j = a[i].num;
        ans = max(ans, x[j] - a[i].d_dupl);
    }
    cout << ans + 1 << endl;
    for (int i = 0; i < n; i++) {
        cout << x[i] << ' ';
    }
    return 0;
}
