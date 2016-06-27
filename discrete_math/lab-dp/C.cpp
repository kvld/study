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
   
const int MAXN = 2000;
const double INF = 2 * (1e9) + 1;
const ll INF_64 = (1LL << 62);
const int MOD = 1000000007;
  
const double EPS = 1e-8;
const double PI = acos(-1.0);
  
int n, m;
vector<int> a (MAXN), b (MAXN);
int dp[MAXN + 1][MAXN + 1]; 
pair<int, int> pr[MAXN + 1][MAXN + 1];

int main()
{
	#ifdef LOCAL
		freopen("input.txt", "r", stdin);
		freopen("output.txt", "w", stdout);
	#else
		freopen("lcs.in", "r", stdin);
		freopen("lcs.out", "w", stdout);
	#endif
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> a[i];
	cin >> m;
	for (int i = 0; i < m; i++)
		cin >> b[i];
	for (int i = 0; i < n; i++)
		dp[i][0] = 0;
	for (int i = 0; i < m; i++)
		dp[0][i] = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (a[i] == b[j])
				dp[i + 1][j + 1] = dp[i][j] + 1, pr[i + 1][j + 1] = mp(i, j);
			else 
			{
				if (dp[i][j + 1] > dp[i + 1][j])
					pr[i + 1][j + 1] = mp(i, j + 1);
				else
					pr[i + 1][j + 1] = mp(i + 1, j);
				dp[i + 1][j + 1] = max(dp[i][j + 1], dp[i + 1][j]);
			}
		}
	}
	int x = n, y = m;
	vector<int> ans;
	while (x != 0 && y != 0)
	{
		if (pr[x][y] == mp(x - 1, y - 1))
		{
			x--, y--;
			ans.pb(a[x]);
		}
		else
		{
			if (pr[x][y] == mp(x - 1, y))
				x--;
			else
				y--;
		}
	}
	cout << sz(ans) << endl;
	for (int i = sz(ans) - 1; i >= 0; i--)
		cout << ans[i] << ' ';
	return 0;
}