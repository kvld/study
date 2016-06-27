
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
 
string s;
int dp[MAXN][MAXN];
vector<char> answ (MAXN);

int rec(int l, int r)
{
	if (dp[l][r] == -1)
	{
		if (s[l] == s[r])
			dp[l][r] = rec(l + 1, r - 1) + 2;
		else
			dp[l][r] = max(rec(l + 1, r), rec(l, r - 1));
	}
	return dp[l][r];
}

void ans(int l, int r, int pl, int pr)
{
	while (l <= r)
	{
		if (l == r && dp[l][r] == 1)
			answ[pl] = s[l], l++, pl++;
		else
		{
			if (s[l] == s[r])
			{
				answ[pl] = s[l], l++, pl++;
				answ[pr] = s[r], r--, pr--;
			}
			else
			{
				if (dp[l + 1][r] > dp[l][r - 1])
					l++;
				else
					r--;
			}
		}
	}
}

int main()
{
	#ifdef LOCAL
		freopen("input.txt", "r", stdin);
		freopen("output.txt", "w", stdout);
	#else
		freopen("palindrome.in", "r", stdin);
		freopen("palindrome.out", "w", stdout);
	#endif
	cin >> s;
	cerr << M_PI;
	for (int i = 0; i < sz(s); i++)
	{
		for (int j = 0; j < sz(s); j++)
		{
			if (i == j)
				dp[i][j] = 1;
			else if (i > j)
				dp[i][j] = 0;
			else
				dp[i][j] = -1;	
		}
	}
	rec(0, sz(s) - 1);
	ans(0, sz(s) - 1, 0, dp[0][sz(s) - 1] - 1);
	cout << dp[0][sz(s) - 1] << endl;
	for (int i = 0; i < dp[0][sz(s) - 1]; i++)
		cout << answ[i];
	return 0;
}