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

int n, k;
vector<int> a;
ll dp[31][31];

void solve(ll num, ll x, ll cur)
{
	if (num == k)
	{
		cout << cur;
		return;
	}
	for (int i = x; i < a[num]; i++)
		cur += dp[n - i - 1][k - num - 1];
	solve(num + 1, a[num] + 1, cur);
}

int main()
{
	#ifdef LOCAL
		freopen("input.txt", "r", stdin);
		freopen("output.txt", "w", stdout);
	#else
		freopen("choose2num.in", "r", stdin);
		freopen("choose2num.out", "w", stdout);
	#endif
	cin >> n >> k;
	a.resize(k);
	for (int i = 0; i < k; i++)
	{
		cin >> a[i];
		a[i]--;
	}
	dp[0][0] = 1;
	for (int i = 1; i < 31; i++)
		for (int j = 0; j < 31; j++)
			dp[i][j] = (j - 1 >= 0 ? dp[i - 1][j - 1] : 0) + dp[i - 1][j];
	solve(0, 0, 0);
	return 0;
}