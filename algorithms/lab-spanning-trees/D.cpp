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
const double INF = 2 * (1e9) + 1;
const ll INF_64 = (1LL << 62);
const int MOD = 1000000007;
 
const double EPS = 1e-8;
const double PI = acos(-1.0);
 
struct edge {
    int u, v, w;
    edge(int _u, int _v, int _w)
    {
        u = _u;
        v = _v;
        w = _w;
    }
};
 
int n, m;
int g[MAXN][MAXN];
int deg[MAXN];
vector<int> ans;

void find_euler_path(int v) {
    for (int i = 0; i < n; i++) {
        if (g[v][i] > 0) {
            g[v][i]--;
            g[i][v]--;
            find_euler_path(i);
        }
    }
    ans.pb(v);
}

int main()
{
    freopen("euler.in", "r", stdin);
    freopen("euler.out", "w", stdout);
    cin >> n;
    for (int i = 0; i < n; i++) {
        deg[i] = 0;
        for (int j = 0; j < n; j++) {
            g[i][j] = 0;
        }
    }
    for (int i = 0; i < n; i++) {
        int m;
        cin >> m;
        for (int j = 0; j < m; j++) {
            int v;
            cin >> v;
            g[i][--v]++;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (g[i][j] > 0)
                deg[g[i][j]] += g[i][j];
        }
    }
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (deg[i] % 2 != 0) {
            cnt++;
            if (cnt > 2) {
                cout << -1;
                return 0;
            }
        }
    }
    find_euler_path(0);
    cout << sz(ans) - 1 << endl;
    for (auto x: ans) {
        cout << x + 1 << ' ';
    }
    return 0;
}