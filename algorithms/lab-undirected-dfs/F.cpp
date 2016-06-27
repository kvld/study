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
vector<int> ans;
bool used[20000];
vector<int> stack;
bool is_point[20000];
int timer = 0;
int tin[20000], up[20000];
map<pair<int, int>, int> color;
pair<int, int> id[200000];
int cnt = 0;
int mcolor = 0;


void dfs(int u, int pr)
{
    up[u] = tin[u] = ++timer;
    used[u] = true;
    int c = 0;
    for (int i = 0; i < g[u].size(); i++) {
        int w = g[u][i];
        if (w == pr)
            continue;
        if (!used[w]) {
            c++;
            dfs(w, u);
            up[u] = min(up[u], up[w]);
            if (pr != -1 && up[w] >= tin[u]) {
                if (!is_point[u])
                    cnt++;
                is_point[u] = true;
            }
        }
        else {
            up[u] = min(up[u], tin[w]);
        }
    }

    if (pr == -1 && c > 1) {
        if (!is_point[u])
            cnt++;
        is_point[u] = true;
    }
}

void dfs2(int v, int c, int pr) 
{
    //cerr << v+1<< ' ' << c << ' ' << pr+1 << endl;
    used[v] = true;
    for (int i = 0; i < sz(g[v]); i++) {
        int u = g[v][i];
        if (u == pr)
            continue;
        if (!used[u]) {
            if (up[u] >= tin[v]) {
                mcolor++;
                color[mp(min(u, v), max(u, v))] = mcolor;
                //cerr << "1painting " << u+1 << ' ' << v+1 << ' ' << mcolor << endl;
                dfs2(u, mcolor, v);
            } else {
                color[mp(min(u, v), max(u, v))] = c;
                //cerr << "2painting " << u+1 << ' ' << v+1 << ' ' << c << endl;
                dfs2(u, c, v);
            }
        } else {
            if (tin[u] <= tin[v]) {
                color[mp(min(u, v), max(u, v))] = c;
                //cerr << "3painting " << u+1 << ' ' << v+1 << ' ' << c << endl;
            }
        }
    }
}

int main()
{
    freopen("biconv.in", "r", stdin);
    freopen("biconv.out", "w", stdout);
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        g[--u].pb(--v);
        g[v].pb(u);
        color[mp(min(u, v), max(u,v))] = 0;
        id[i] = mp(min(u, v), max(u, v));
    }
    for (int i = 0; i < n; i++)
        used[i] = 0, is_point[i] = false;
    for (int i = 0; i < n; i++) {
        if (used[i] == 0) {
            dfs(i, -1);
        }
    }
    for (int i = 0; i < n; i++)
        used[i] = 0;
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            dfs2(i, -1, -1);
        }
    }
    cout << mcolor << endl;
    for (int i = 0; i < m; i++) {
        cout << color[id[i]] << ' ';
    }
    return 0;
}
