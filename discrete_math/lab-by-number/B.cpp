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

int n;
vector<int> a;

ll fact(ll k)
{
	if (k == 0 || k == 1)
		return 1;
	return k * fact(k - 1);
}

int main()
{
	#ifdef LOCAL
		freopen("input.txt", "r", stdin);
		freopen("output.txt", "w", stdout);
	#else
		freopen("perm2num.in", "r", stdin);
		freopen("perm2num.out", "w", stdout);
	#endif
	cin >> n;
	a.resize(n);
	vector<int> used (n + 1, false);
	ll ans = 0;
	for (int i = 0; i < n; i++)
		cin >> a[i];
	for (int i = 0; i < n; i++)
	{
		int x = 0;
		for (int j = 1; j < a[i]; j++)
		{
			if (!used[j])
				x++;
		}
		used[a[i]] = true;
		ans += x * fact(n - i - 1);
	}
	cout << ans;
	return 0;
}