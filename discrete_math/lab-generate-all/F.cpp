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

int main()
{
    #ifdef LOCAL
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #else
        freopen("subsets.in", "r", stdin);
        freopen("subsets.out", "w", stdout);
    #endif
    cin >> n;
    vector<vector<int> > t;
    for (int i = 0; i < (1 << n); i++)
    {
    	vector<int> tt;
    	for (int j = 0; j < n; j++)
    		if (i & (1 << j))
    			tt.pb(j + 1);
    	t.pb(tt);
    }
    sort(all(t));
    for (int i = 0; i < sz(t); i++)
    {
    	for (int j = 0; j < sz(t[i]); j++)
    		cout << t[i][j] << ' ';
    	cout << endl;
    }
    return 0;
}