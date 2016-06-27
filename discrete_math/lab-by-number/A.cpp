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

ll n, k;

ll fact(ll k)
{
	if (k == 0)
		return 1LL;
	if (k == 1)
		return 1LL;
	return k * 1LL * fact(k - 1);
}

int main()
{
	#ifdef LOCAL
		freopen("input.txt", "r", stdin);
		freopen("output.txt", "w", stdout);
	#else
		freopen("num2perm.in", "r", stdin);
		freopen("num2perm.out", "w", stdout);
	#endif
	cin >> n >> k;
	vector<bool> used (n + 1, false);
	for (int i = 0; i < n; i++)
	{
		ll x = (k / fact(n - i - 1)) + 1;
		assert(x <= n);
		k = k % fact(n - i - 1);
		ll j, cc = 0;
		for (j = 1; j <= n; j++) 
		{
			if (!used[j])
				cc++;
			if (x == cc)
				break;
		}
		used[j] = true;
		cout << j << ' ';
	}
	return 0;
}