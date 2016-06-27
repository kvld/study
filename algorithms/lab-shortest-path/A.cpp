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

int n, m;
vector<int> g[MAXN];
set<pair<int, int > > st;
int d[MAXN];
bool used[MAXN];

void dijkstra(int start)
{
    for (int i = 0; i < n; i++)
        d[i] = INF, used[i] = false;
    d[start] = 0;
    for (int i = 0; i < n; i++)
        st.insert(mp(d[i], i));
    for (int i = 0; i < n; i++) {
        int cur = st.begin()->second;
        st.erase(st.begin());
        for (int j = 0; j < g[cur].size(); j++) {
            int to = g[cur][j];
            if (d[to] > d[cur] + 1) {
                set<pair<int, int> >::iterator to_pos = st.find(mp(d[to], to));
                st.erase(to_pos);
                d[to] = d[cur] + 1;
                st.insert(mp(d[to], to));
            }
        }
    }
}

int main()
{
    freopen("pathbge1.in", "r", stdin);
    freopen("pathbge1.out", "w", stdout);
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        g[--u].pb(--v);
        g[v].pb(u);
    }
    dijkstra(0);
    for (int i = 0; i < n; i++) {
        cout << ((d[i] == INF) ? 0 : d[i]) << ' ';
    }
    return 0;
}
