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

int main()
{
	#ifdef LOCAL
		freopen("input.txt", "r", stdin);
		freopen("output.txt", "w", stdout);
	#else
		freopen("nextchoose.in", "r", stdin);
		freopen("nextchoose.out", "w", stdout);
	#endif
	cin >> n >> k;
	vector<int> a (k);
	for (int i = 0; i < k; i++)
		cin >> a[i];
	int i;
	for (i = k - 1; i >= 0; i--)
		if (a[i] != i - k + n + 1)
			break;
	if (i < 0)
	{
		cout << -1;
		return 0;
	}
	a[i]++;
	i++;
	for (; i < k; i++)
		a[i] = a[i - 1] + 1;
	for (int i = 0; i < k; i++)
		cout << a[i] << ' ';
	return 0;
}