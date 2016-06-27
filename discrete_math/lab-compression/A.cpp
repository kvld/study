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
#define pii pair<long long, int>
  
using namespace std;
 
typedef long long ll;
  
const int MAXN = 10000;
const double INF = 2 * (1e9) + 1;
const ll INF_64 = (1LL << 62);
const int MOD = 1000000007;
 
const double EPS = 1e-8;
const double PI = acos(-1.0);
 
int n;
vector<ll> a (1000);
 
struct node
{
    ll pr;
    int l, r;
    node(ll _pr)
    {
        pr = _pr;
        l = -1;
        r = -1;
    }
};
 
vector<node> tree;
ll ans = 0;
 
void dfs(int vv, ll plen)
{
    node v = tree[vv];
    if (v.l == -1 && v.r == -1)
    {
        ans += plen * a[vv];
    }
    if (v.l != -1)
        dfs(v.l, plen + 1);
    if (v.r != -1)
        dfs(v.r, plen + 1);
}
 
 
int main()
{
    #ifdef LOCAL
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #else
        freopen("huffman.in", "r", stdin);
        freopen("huffman.out", "w", stdout);
    #endif
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    set<pii> d;
    for (int i = 0; i < n; i++)
    {   
        node p = node(a[i]);
        tree.pb(p);
        d.insert(mp(a[i], sz(tree) - 1));
    }
    while (sz(d) > 1)
    {
        pii x, y, z;
        x = *(d.begin());
        d.erase(d.begin());
        y = *(d.begin());
        d.erase(d.begin());
        node p = node(x.fr + y.fr);
        p.l = x.sc;
        p.r = y.sc;
        tree.pb(p);
        d.insert(mp(p.pr, sz(tree) - 1));
    }
    dfs((*d.begin()).sc, 0); 
    cout << ans << endl;
    return 0;
}