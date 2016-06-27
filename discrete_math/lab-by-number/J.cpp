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
string s, t = "";

int str2num(string s)
{
	istringstream ss(s);
	int a;
	ss >> a;
	return a;
}

int main()
{
	#ifdef LOCAL
		freopen("input.txt", "r", stdin);
		freopen("output.txt", "w", stdout);
	#else
		freopen("part2num.in", "r", stdin);
		freopen("part2num.out", "w", stdout);
	#endif
	for (int i = 0; i < 110; i++)
		for (int j = 0; j < 110; j++)
			dp[i][j] = 0;
	for (int i = 0; i < 101; i++)
		dp[i][i] = 1;
	for (int i = 0; i < 101; i++)
		for (int j = 1; j < i; j++)
			for (int k = j; k < 101; k++)
				dp[i][j] += dp[i - j][k];
	for (int i = 0; i < 13; i++)
	{
		for (int j = 0; j < 13; j++)
			cerr << dp[i][j] << ' ';
		cerr << endl;
	}
	cin >> s;
	s += '+';
	vector<int> a;
	ll sum = 0;
	for (int i = 0; i < sz(s); i++)
	{
		if (s[i] == '+')
		{
			a.pb(str2num(t));
			sum += str2num(t);
			t = "";
		}
		else
			t += s[i];
	}
	ll ans = 0;
	int k = 0;
	int last_add = 1;
	while (sum > 0)
	{
		int j = 0;
		for (int i = last_add; i < a[k]; i++)
		{
			cerr << dp[sum][i] << ' ';
			j += dp[sum][i];
		}
		cerr << endl << j << endl;
		last_add = a[k];
		sum -= a[k];
		cerr << '-' << a[k] << endl;
		k++;
		ans += j;
	}
	cout << ans;
	return 0;
}