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
string s;
vector<int> a;

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
		freopen("nextpartition.in", "r", stdin);
		freopen("nextpartition.out", "w", stdout);
	#endif
	cin >> s;
	string t = "";
	int i;
	for (i = 0; i < sz(s); i++)
	{
		if (s[i] == '=')
			break;
		t += s[i];
	}
	n = str2num(t);
	t = "";
	s += '+';
	for (i++; i < sz(s); i++)
	{
		if (s[i] == '+')
		{
			a.pb(str2num(t));
			t = "";
		}
		else
			t += s[i];	
	}
	if (sz(a) == 1 && n == a[0])
	{
		cout << "No solution";
		return 0;
	}
	else
	{
		a[sz(a) - 2]++;
		a[sz(a) - 1]--;
		if (a[sz(a) - 2] > a[sz(a) - 1])
		{
			a[sz(a) - 2] += a[sz(a) - 1];
			a.pop_back();
		}
		else
		{
			while (a[sz(a) - 2] <= (a[sz(a) - 1] >> 1))
			{
				a.pb(a[sz(a) - 1] - a[sz(a) - 2]);
				a[sz(a) - 2] = a[sz(a) - 3];
			}
		}
	}
	cout << n << '=';
	for (int i = 0; i < sz(a) - 1; i++)
		cout << a[i] << '+';
	cout << a[sz(a) - 1];
	return 0;
}