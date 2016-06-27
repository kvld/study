#pragma comment(linker, "/STACK:200000000")

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
#include <stack>
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
   
const int MAXN = 100001;
const double INF = 2 * (1e9) + 1;
const ll INF_64 = (1LL << 62);
const int MOD = 1000000007;
  
const double EPS = 1e-8;
const double PI = acos(-1.0);
  
int n;
vector<pair<int, int> > g[MAXN];
ll a[MAXN], b[MAXN], c[MAXN];
bool used[MAXN] = {0};
 
void dfs(int x)
{
	//cerr << x << endl;
	used[x] = true;
	int cnt = 0;
	for (int i = 0; i < sz(g[x]); i++)
	{
		if (!used[g[x][i].fr])
		{
			cnt++;
			dfs(g[x][i].fr);
			a[x] = max(a[x], b[g[x][i].fr] + g[x][i].sc - c[g[x][i].fr]);
			b[x] += c[g[x][i].fr];
		}
	}
	a[x] += b[x];
	c[x] = max(a[x], b[x]);
}


int main()
{
	#ifdef LOCAL
		freopen("input.txt", "r", stdin);
		freopen("output.txt", "w", stdout);
	#else
		freopen("matching.in", "r", stdin);
		freopen("matching.out", "w", stdout);
	#endif
	cin >> n;
	for (int i = 0; i < n - 1; i++)
	{
		int u, v, x;
		cin >> u >> v >> x;
		u--, v--;
		g[u].pb(mp(v, x));
		g[v].pb(mp(u, x));
	}
	for (int i = 0; i < n; i++)
		a[i] = b[i] = c[i] = 0;
	dfs(0);
	cout << c[0];
	return 0;
}