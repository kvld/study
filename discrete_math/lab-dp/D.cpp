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
  
using namespace std;
 
typedef long long ll;
  
const int MAXN = 10000;
const double INF = 2 * (1e9) + 1;
const ll INF_64 = (1LL << 62);
const int MOD = 1000000007;
 
const double EPS = 1e-8;
const double PI = acos(-1.0);
 
int n, w;
vector<int> a, b;
int dp[1002][10001];
 
int main()
{
    #ifdef LOCAL
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #else
        freopen("knapsack.in", "r", stdin);
        freopen("knapsack.out", "w", stdout);
    #endif
    cin >> n >> w;
    a.resize(n + 1);
    b.resize(n + 1);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int i = 0; i < n; i++)
        cin >> b[i];
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= w; j++)
            dp[i][j] = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j <= w; j++)
        {
            dp[i][j] = dp[i - 1][j];
            if (j >= a[i - 1])
                dp[i][j] = max(dp[i][j], dp[i - 1][j - a[i - 1]] + b[i - 1]);
        }
    }
    vector<int> ans;
    int x = n, y = w;
    while (dp[x][y] != 0)
    {
        if (dp[x][y] == dp[x - 1][y])
            x--;
        else
        {
            ans.pb(x);
            x--, y -= a[x];
        }
    }
    cout << sz(ans) << endl;
    for (int i = sz(ans) - 1; i >= 0; i--)
        cout << ans[i] << ' ';
    return 0;
}