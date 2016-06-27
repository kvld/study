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

string s = "";
long long dp[50][50];

int main()
{
    #ifdef LOCAL
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #else
        freopen("brackets2num.in", "r", stdin);
        freopen("brackets2num.out", "w", stdout);
    #endif
    cin >> s;
    for (int i = 0; i < 40; i++)
        dp[0][i] = 0;
    dp[0][0] = 1;
    for (int i = 1; i <= 40; i++)
    {
        for (int j = 0; j <= 40; j++)
        {
            dp[i][j] = (j < 0 ? 0 : dp[i - 1][j - 1]) + dp[i - 1][j + 1];
        }
    }
    int balance = 0;
    long long ans = 0;
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == '(')
            balance++;
        else
        {
            ans += dp[s.length() - i - 1][balance + 1];
            balance--;
        }
    }
    cout << ans << endl;

    return 0;
}