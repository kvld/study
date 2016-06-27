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
   
const int MAXN = 5000;
const double INF = 2 * (1e9) + 1;
const ll INF_64 = (1LL << 62);
const int MOD = 1000000007;
  
const double EPS = 1e-8;
const double PI = acos(-1.0);
  
int n;
vector<int> a (MAXN);
vector<int> dp (MAXN), pr (MAXN);
 
int main()
{
	#ifdef LOCAL
		freopen("input.txt", "r", stdin);
		freopen("output.txt", "w", stdout);
	#else
		freopen("lis.in", "r", stdin);
		freopen("lis.out", "w", stdout);
	#endif
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> a[i];
	dp[0] = 1;
	pr[0] = -1;
	for (int i = 1; i < n; i++)
	{
		dp[i] = 1;
		pr[i] = -1;
		for (int j = i - 1; j >= 0; j--)
		{
			if (a[i] > a[j])
			{
				if (dp[j] + 1 > dp[i])
				{
					dp[i] = dp[j] + 1;
					pr[i] = j;
				}
			}
		}
	}
	int ans = 0, ansp = 0;
	for (int i = 0; i < n; i++)
	{
		if (dp[i] > ans)
			ans = dp[i], ansp = i;
	}
	vector<int> aa;
	int cur = ansp;
	while (cur != -1)
	{
		aa.pb(a[cur]);
		cur = pr[cur];
	}
	cout << sz(aa) << endl;
	for (int i = sz(aa) - 1; i >= 0; i--)
		cout << aa[i] << ' ';
	return 0;
}