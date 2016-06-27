
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
    
const int MAXN = 402;
const double INF = 2 * (1e9) + 1;
const ll INF_64 = (1LL << 62);
const int MOD = 1000000007;
   
const double EPS = 1e-8;
const double PI = acos(-1.0);
 
int n;
vector<pair<int, int> > a;
int dp[MAXN][MAXN];
int pr[MAXN][MAXN];
string ans = "";
 
void get(int i, int j)
{
    if (i == j)
        ans += "A";
    else
    {
        ans += "(";
        get(i, pr[i][j]);
        get(pr[i][j] + 1, j);
        ans += ")";
    }
}
 
int main()
{
    #ifdef LOCAL
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #else
        freopen("matrix.in", "r", stdin);
        freopen("matrix.out", "w", stdout);
    #endif
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        a.pb(mp(x, y));
    }
    for (int i = 0; i < MAXN; i++)
        dp[i][i] = 0;
    for (int l = 2; l <= n; l++) 
    {
        for (int i = 1; i <= n - l + 1; i++) 
        {
            int j = i + l - 1;
            dp[i][j] = INF;
            pr[i][j] = i;
            for (int k = i; k <= j - 1; k++) 
            {
                //cerr << a[i - 1].fr << ' ' << a[k].sc << ' ' << a[j - 1].sc << endl;
                int alt = dp[i][k] + dp[k + 1][j] + a[i - 1].fr * a[k].fr * a[j - 1].sc;
                if (alt < dp[i][j])
                {
                    dp[i][j] = alt;
                    pr[i][j] = k;
                }
            }
        }
    }
    get(1, n);
    cout << ans;
    return 0;
}