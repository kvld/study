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
   
const int MAXN = 2002;
const double INF = 2 * (1e9) + 1;
const ll INF_64 = (1LL << 62);
const int MOD = 1000000007;
  
const double EPS = 1e-8;
const double PI = acos(-1.0);
  
int n;
ll dp[MAXN][MAXN], rr[MAXN][MAXN];
ll prefix[MAXN];
string p[MAXN][MAXN];
 
void rec_ans(int l, int r)
{
    if (l == r)
        cout << p[l][r] << endl;
    else
    {
        p[l][rr[l][r]] = p[l][r] + "0";
        p[rr[l][r] + 1][r] = p[l][r] + "1";
        rec_ans(l, rr[l][r]);
        rec_ans(rr[l][r] + 1, r);
    }
}

int main()
{
	#ifdef LOCAL
		freopen("input.txt", "r", stdin);
		freopen("output.txt", "w", stdout);
	#else
		freopen("optimalcode.in", "r", stdin);
		freopen("optimalcode.out", "w", stdout);
	#endif
	cin >> n;
	prefix[0] = 0;
	int x;
	for (int i = 0; i < n; i++)
	{
		cin >> x;
		prefix[i + 1] = prefix[i] + x;
	} 
	for (int i = 0; i <= n; i++)
		for (int j = 0; j <= n; j++)
			dp[i][j] = -1;

	for (int i = 0; i <= n; i++)
	{
		dp[i][i] = 0;
		rr[i][i] = i;
	}

	for (int len = 2; len <= n; len++)
	{
		for (int l = 0; l <= n - len; l++)
		{
			int r = l + len - 1;
			dp[l][r] = INF_64;

			for (int i = max(rr[l][r - 1] - 1, (ll)l); i < min(rr[l + 1][r] + 1, (ll)r); i++)
			{
				if (dp[l][i] + dp[i + 1][r] < dp[l][r])
				{
					dp[l][r] = dp[l][i] + dp[i + 1][r];
					rr[l][r] = i;
				}
			}

			dp[l][r] += prefix[r + 1] - prefix[l];
		}
	}
	cout << dp[0][n - 1] << endl;
	rec_ans(0, n - 1);
	return 0;
}