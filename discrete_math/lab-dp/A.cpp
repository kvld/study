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
  
int n, m;
vector<int> g[MAXN], gr[MAXN];
vector<int> ind (MAXN, 0);
vector<int> topsort;
vector<int> used (MAXN, 0);
vector<int> dp (MAXN, 0);
 

void ts()
{
	queue<int> s;
	ind[0] = -1;
	s.push(0);
	while (!s.empty())
	{
		int front = s.front();
		s.pop();
		topsort.pb(front);
		for (int i = 0; i < sz(g[front]); i++)
		{
			ind[g[front][i]]--;
			if (ind[g[front][i]] == 0)
				s.push(g[front][i]);
		}
	}
}
 
 
int main()
{
	#ifdef LOCAL
		freopen("input.txt", "r", stdin);
		freopen("output.txt", "w", stdout);
	#else
		freopen("countpaths.in", "r", stdin);
		freopen("countpaths.out", "w", stdout);
	#endif
	cin >> n >> m;
	for (int i = 0; i < m; i++)
	{
		int u, v;
		cin >> u >> v;
		u--, v--;
		ind[v]++;
		g[u].pb(v);
		gr[v].pb(u);
	}
	ts();
	dp[0] = 1;
	for (int i = 0; i < n; i++)
	{
		int cur = topsort[i];
		for (int j = 0; j < sz(gr[cur]); j++)
		{
			dp[cur] += (dp[gr[cur][j]] % MOD);
			dp[cur] %= MOD;
		}
	}
	cout << (dp[n - 1] % MOD);
	return 0;
}