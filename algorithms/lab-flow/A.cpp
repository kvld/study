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

int n, m, k;
vector<int> g[MAXN];
vector<char> used (MAXN);
vector<int> matching (MAXN, -1);

bool dfs(int v) {
    if (used[v]) {
        return false;
    } else {
        used[v] = true;
    }
    for (auto to: g[v]) {
        //cerr << to + 1 << ' ' << (matching[to] == -1 ? -1 : matching[to] + 1) << endl;
        if (matching[to] == -1 || dfs(matching[to])) {
            matching[to] = v;
            return true;
        }
    }
    return false;
}

int main()
{
    freopen("matching.in", "r", stdin);
    freopen("matching.out", "w", stdout);
    cin >> n >> m >> k;
    for (int i = 0; i < k; i++) {
        int u, v;
        cin >> u >> v;
        g[--u].pb(--v);
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        used.assign(n, false);
        ans += dfs(i);
    }
    cout << ans;
    return 0;
}