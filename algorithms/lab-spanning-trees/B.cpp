
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
vector<edge> mst;
int cost = 0;
int p[MAXN];

bool comp(const edge& a, const edge& b) {
    return (a.w < b.w);
}

void dsu_make_set(int i) {
    p[i] = i;
}

int dsu_get_set(int i) {
    if (p[i] == i) {
        return i;
    }
    return (p[i] = dsu_get_set(p[i]));
}

void dsu_union_set(int x, int y) {
    x = dsu_get_set(x);
    y = dsu_get_set(y);
    if (rand() % 2 == 1) {
        swap(x, y);
    }
    if (x != y) {
        p[x] = y;
    }
}

void kruskal() {
    for (int i = 0; i < n; i++)
        dsu_make_set(i);
    sort(all(edges), comp);
    for (int i = 0; i < m; i++) {
        if (dsu_get_set(edges[i].u) != dsu_get_set(edges[i].v)) {
            cost += edges[i].w;
            mst.pb(edges[i]);
            dsu_union_set(edges[i].u, edges[i].v);
        }
    }
}
 
int main()
{
    freopen("spantree2.in", "r", stdin);
    freopen("spantree2.out", "w", stdout);
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.pb(edge(--u, --v, w));
    }
    kruskal();
    cout << cost << endl;
    return 0;
}