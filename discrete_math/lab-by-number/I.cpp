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

ll dp[110][110];
int n, k;

int main()
{
	#ifdef LOCAL
		freopen("input.txt", "r", stdin);
		freopen("output.txt", "w", stdout);
	#else
		freopen("num2part.in", "r", stdin);
		freopen("num2part.out", "w", stdout);
	#endif
	cin >> n >> k;
	for (int i = 0; i < 110; i++)
		for (int j = 0; j < 110; j++)
			dp[i][j] = 0;
	for (int i = 0; i < 101; i++)
		dp[i][i] = 1;
	for (int i = 0; i < 101; i++)
		for (int j = 1; j < i; j++)
			for (int k = j; k < 101; k++)
				dp[i][j] += dp[i - j][k];
	vector<int> a;
	int i = 1;
	int cur = n;
	while (cur > 0)
	{
		int j = 0;
		while (j + dp[cur][i] <= k)
		{
			j += dp[cur][i];
			i++;
		}
		a.pb(i);
		cur -= i;
		k -= j;
	}
	for (int i = 0; i < sz(a) - 1; i++)
		cout << a[i] << '+';
	cout << a[sz(a) - 1];
	return 0;
}