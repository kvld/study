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
vector<int> num (11, 0);

void gen(int x, int y)
{
	//cerr << x << ' ' << y << endl;
	if (n <= x + 1)
	{
		if (k == y + 1)
		{
			vector<vector<int> > dd;
			for (int i = 0; i < y + 1; i++)
			{
				vector<int> d;
				for (int j = 0; j < x + 1; j++)
				{
					if (num[j] == i)
						d.pb(j + 1);
				}
				dd.pb(d);
			}
			sort(all(dd));
			for (int i = 0; i < sz(dd); i++)
			{
				for (int j = 0; j < sz(dd[i]); j++)
					cout << dd[i][j] << ' ';
				cout << endl;
			}
			cout << endl;
		}
		return;
	}
	for (int i = 0; i < y + 1; i++)
	{
		num[x] = i;
		if (x + 1 < n)
			gen(x + 1, y);
	}
	if (y + 1 < k)
	{
		num[x] = y + 1;
		if (x + 1 < n)
			gen(x + 1, y + 1);
	}
}

int main()
{
    #ifdef LOCAL
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #else
        freopen("part2sets.in", "r", stdin);
        freopen("part2sets.out", "w", stdout);
    #endif
    cin >> n >> k;
    gen(0, 0);
    return 0;
}