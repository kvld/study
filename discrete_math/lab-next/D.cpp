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
		freopen("nextsetpartition.in", "r", stdin);
		freopen("nextsetpartition.out", "w", stdout);
	#endif
	bool first = false;
	while (cin >> n >> k)
	{
		string _t;
		if (n == 0 && k == 0)
			return 0;
		if (first)
			cout << endl;
		first = true;
		vector<vector<int> > a(k);
		for (int i = 0; i < k; i++)
		{
			string s, t = "";
			getline(cin, s);
			if (s == "")
			{
				i--;
				continue;
			}
			s += ' ';
			for (int j = 0; j < sz(s); j++)
				if (s[j] == ' ')
				{
					a[i].pb(str2num(t));
					t = "";
				}
				else
					t += s[j];
		}

		vector<int> used;

		for (int i = sz(a) - 1; i >= 0; i--)
		{
			bool flag = false;
			if (sz(used) != 0 && used[0] > a[i][sz(a[i]) - 1])
			{
				for (int k = sz(used) - 1; k >= 0; k--)
				{
					if (used[k] > a[i][sz(a[i]) - 1])
					{
						a[i].pb(used[k]);
						used.erase(used.begin() + k);
						sort(all(used));
						reverse(all(used));
						flag = true;
						break;
					}
				}
			}
			if (flag)
				break;
			for (int j = sz(a[i]) - 1; j >= 0; j--)
			{
				if (sz(used) != 0 && j > 0 && used[0] > a[i][j])
				{
					for (int k = sz(used) - 1; k >= 0; k--)
					{
						if (used[k] > a[i][j])
						{
							swap(a[i][j], used[k]);
							sort(all(used));
							reverse(all(used));
							flag = true;
							break;
						}
					}
				}
				if (flag)
					break;
				used.pb(a[i][j]);
				sort(all(used));
				reverse(all(used));
				a[i].erase(a[i].begin() + j);
				if (sz(a[i]) == 0)
					a.pop_back();
			}
			if (flag)
				break;
		}
		//for (int i = 0; i < sz(used); i++)
		//	cerr << used[i] << ' ';
		sort(all(used));
		for (int i = 0; i < sz(used); i++)
		{
			vector<int> tmp;
			tmp.pb(used[i]);
			a.pb(tmp);
		}
		cout << n << ' ' << sz(a) << endl;
		for (int i = 0; i < sz(a); i++)
		{
			for (int j = 0; j < sz(a[i]); j++)
				cout << a[i][j] << ' ';
			cout << endl;
		}
	}
	return 0;
}