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

int n, k, m;
vector<int> cur_ch;
int dp[31][31];

void print(vector<int> p)
{
    for (int i = 0; i < p.size(); i++)
    {
        cout << p[i] << ' ';
    }
    cout << endl;
}

long long cnt(int e, int nn)
{
    if (dp[e][nn] != -1)
        return dp[e][nn];
    dp[e][nn] = 0;
    for (int i = e + 1; i <= n; i++)
        dp[e][nn] += cnt(i, nn - 1);
    return dp[e][nn];
}

void solve(int cur_k, int e, int nn)
{
    if (cur_k == 0 || e > n)
    {
        print(cur_ch);
        return;
    }
    if (cnt(e, nn) >= cur_k)
    {
        cur_ch.pb(e);
        solve(cur_k, e + 1, nn - 1);
    }
    else
    {
        solve(cur_k - cnt(e, nn), e + 1, nn);
    }
}

int main()
{
    #ifdef LOCAL
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #else
        freopen("num2choose.in", "r", stdin);
        freopen("num2choose.out", "w", stdout);
    #endif
    cin >> n >> k >> m;
    m++;
    for (int i = 0; i <= 30; i++)
        for (int j = 0; j <= 30; j++)
            dp[i][j] = -1;
    for (int i = 1; i <= 30; i++)
        dp[i][1] = 1;
    vector<int> ch;
    solve(m, 1, k);
    return 0;
}