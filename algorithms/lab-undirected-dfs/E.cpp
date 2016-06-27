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
int color[20000];
int timer = 0;
int tin[20000], up[20000];
int mcolor = 0;

void dfs(int u, int pr)
{
    stack.pb(u);
    tin[u] = ++timer;
    up[u] = tin[u];
    used[u] = true;
    for (int i = 0; i < g[u].size(); i++) {
        int v = g[u][i];
        if (v == pr)
            continue;
        if (!used[v]) {
            dfs(v, u);
            up[u] = min(up[u], up[v]);
            if (up[v] > tin[u]) {
                cerr << u << ' ' << v;
                mcolor++;
                while (!stack.empty()) {
                    int top = stack.back();
                    stack.pop_back();
                    color[top] = mcolor;
                    if (top == v) 
                        break;
                }
            }
        }
        else {
            up[u] = min(up[u], tin[v]);
        }
    }
}

int main()
{
    freopen("bicone.in", "r", stdin);
    freopen("bicone.out", "w", stdout);
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        g[--u].pb(--v);
        g[v].pb(u);
    }
    for (int i = 0; i < n; i++)
        used[i] = 0;
    for (int i = 0; i < n; i++) {
        if (used[i] == 0) {
            dfs(i, -1);
            mcolor++;
            while (!stack.empty()) {
                int top = stack.back();
                color[top] = mcolor;
                stack.pop_back();
            }
        }
    }
    cout << mcolor << endl;
    for (int i = 0; i < n; i++)
        cout << color[i] << ' ';
    return 0;
}
