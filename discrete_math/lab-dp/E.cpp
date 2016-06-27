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
   
const int MAXN = 5002;
const double INF = 2 * (1e9) + 1;
const ll INF_64 = (1LL << 62);
const int MOD = 1000000007;
  
const double EPS = 1e-8;
const double PI = acos(-1.0);

string a, b;
int dp[MAXN][MAXN];

int main()
{
	#ifdef LOCAL
		freopen("input.txt", "r", stdin);
		freopen("output.txt", "w", stdout);
	#else
		freopen("levenshtein.in", "r", stdin);
		freopen("levenshtein.out", "w", stdout);
	#endif
	cin >> a >> b;
	for (int i = 0; i <= sz(a); i++)
		dp[i][0] = i;
	for (int i = 0; i <= sz(b); i++)
		dp[0][i] = i;

	for (int i = 1; i <= sz(a); i++)
	{
		for (int j = 1; j <= sz(b); j++)
		{
			dp[i][j] = min(min(dp[i - 1][j] + 1, dp[i][j - 1] + 1), dp[i - 1][j - 1] + (a[i - 1] != b[j - 1]));
		}
	}
	cout << dp[sz(a)][sz(b)];
	return 0;
}