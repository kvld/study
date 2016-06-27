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
 
const int MAXN = 1000;
const int INF = 2 * (1e9) + 1;
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
vector<edge> edges;
int cnt = 0;
vector<int> used;
vector<vector<edge> > ng (MAXN);
vector<vector<edge> > tng (MAXN);

void dfs_check(int v) {
    cnt++;
    used[v] = 1;
    for (int i = 0; i < sz(ng[v]); i++) {
        int to = ng[v][i].v;
        if (!used[to]) {
            dfs_check(to);
        }
    }
} 

bool check_new_graph(int root, int n) {
    used.assign(n, 0);
    cnt = 0;
    dfs_check(root);
    return cnt == n;
}

vector<int> topsort;
void dfs_topsort(int v) {
    used[v] = 1;
    for (int i = 0; i < sz(ng[v]); i++) {
        int to = ng[v][i].v;
        if (!used[to]) {
            dfs_topsort(to);
        }
    }
    topsort.pb(v);
}

vector<int> get_topsort(int n) {
    used.assign(n, 0);
    topsort.clear();
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            dfs_topsort(i);
        }
    }
    reverse(all(topsort));
    return topsort;
}

vector<int> components;
void dfs_css(int v, int c) {
    used[v] = 1;
    components[v] = c;
    for (int i = 0; i < sz(tng[v]); i++) {
        int to = tng[v][i].v;
        if (!used[to]) {
            dfs_css(to, c);
        }
    } 
}

ll mst(vector<edge> edges, int n, int root) {
    ll cost = 0;
    // zero edges
    vector<int> minimal_edge (n, INF);
    for (auto e: edges) {
        minimal_edge[e.v] = min(minimal_edge[e.v], e.w);
    }
    /*for (int i = 0; i < n; i++) {
        cout << minimal_edge[i] << ' ';
    }
    cout << endl;*/
    for (int i = 0; i < n; i++) {
        if (i == root) {
            continue;
        }
        cost += minimal_edge[i];
    }
    for (int i = 0; i < n; i++) {
        ng[i].clear();
        tng[i].clear();
    }
    for (int i = 0; i < sz(edges); i++) {
        if (edges[i].w == minimal_edge[edges[i].v]) {
            //cout << edges[i].u +1<< ' ' << edges[i].v +1<< endl;
            ng[edges[i].u].pb(edge(edges[i].u, edges[i].v, 0));
            tng[edges[i].v].pb(edge(edges[i].v, edges[i].u, 0));
            edges[i].w = 0;
        } else {
            edges[i].w -= minimal_edge[edges[i].v];
        }
    }


    //cout << endl;
    if (check_new_graph(root, n)) {
        return cost;
    }


    vector<int> topsort = get_topsort(n);
    /*for (int i = 0; i < sz(topsort); i++) {
        cout << topsort[i] + 1 << ' ';
    }
    cout << "=" << endl;*/

    // condensate
    components.assign(n, -1);
    used.assign(n, 0);
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        int j = topsort[i];
        if (!used[j]) {
            dfs_css(j, cnt);
            cnt++;
        }
    }
    /*for (int i = 0; i < n; i++) {
        cout << components[i] << ' ';
    }
    cout << endl;*/

    vector<edge> new_edges;
    for (auto e: edges) {
        if (components[e.v] != components[e.u]) {
            new_edges.pb(edge(components[e.u], components[e.v], e.w));
            //cout << components[e.u]+1 << ' ' << components[e.v]+1 << ' ' << e.w << endl;
        }
    }
    //cout << "END" << endl;
    cost += mst(new_edges, cnt, components[root]);
    return cost;
}

vector<int> g[MAXN];
void dfs(int v) {
    used[v] = 1;
    for (int i = 0; i < sz(g[v]); i++) {
        int to = g[v][i];
        if (!used[to]) {
            dfs(to);
        }
    }
}

int main()
{
    freopen("chinese.in", "r", stdin);
    freopen("chinese.out", "w", stdout);
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.pb(edge(--u, --v, w));
    }

    for (auto e: edges) {
        g[e.u].pb(e.v);
    }
    used.assign(n, 0);
    dfs(0);
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            cout << "NO";
            return 0;
        }
    }

    ll ans = mst(edges, n, 0);
    cout << "YES" << endl << ans << endl;
    return 0;
}