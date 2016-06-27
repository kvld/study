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
#include <bitset>
#include <cassert>
#define pb push_back
#define mp make_pair
#define sqr(X) (X)*(X)

using namespace std;

const int INF = 1e9 + 1;
const double EPS = 1e-8;
const int MAXN = 100000;
const double PI = 3.14159265359;
const double E = 2.71828182846;

struct edge
{
    int v, w;
    edge(int _v, int _w)
    {
        v = _v;
        w = _w;
    }
};

int n, m, s, t;
vector<edge> g[MAXN];
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
    for (int i = 0; i < n; i++)
    {
        int cur = st.begin()->second;
        st.erase(st.begin());
        for (int j = 0; j < g[cur].size(); j++)
        {
            int to = g[cur][j].v;
            if (d[to] > d[cur] + g[cur][j].w)
            {
                set<pair<int, int> >::iterator to_pos = st.find(mp(d[to], to));
                st.erase(to_pos);
                d[to] = d[cur] + g[cur][j].w;
                st.insert(mp(d[to], to));
            }
        }
    }
}

int main()
{
    freopen("shortpath.in", "r", stdin);
    freopen("shortpath.out", "w", stdout);
    cin >> n >> m >> s >> t;
    s--, t--;
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        g[u].pb(edge(v, w));
        //g[v].pb(edge(u, w));
    }
    vector<int> d (n, INF),  p (n);
    d[s] = 0;
    vector<char> u (n);
    for (int i=0; i<n; ++i) {

        for (int c = 0; c < n; c++)
            cout << d[c] << ' ';
        cout << endl;

        int v = -1;
        for (int j=0; j<n; ++j)
            if (!used[j] && (v == -1 || d[j] < d[v]))
                v = j;
        if (d[v] == INF)
            break;
        used[v] = true;
 
        cout << v << endl;
        for (size_t j=0; j<g[v].size(); ++j) {
            int to = g[v][j].v,
                len = g[v][j].w;
            if (d[v] + len < d[to]) {
                cout << "r " << v << "->" << to << endl;
                d[to] = d[v] + len;
                p[to] = v;
            }
        }
    }
    for (int c = 0; c < n; c++)
        cout << d[c] << ' ';
    cout << endl;
    cout << (d[t] == INF ? -1 : d[t]) << endl;
    return 0;
}