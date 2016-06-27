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

const int MAXN = 200;
const int INF = 2 * (1e9) + 1;
const ll INF_64 = (1LL << 62);
const int MOD = 1000000007;

const double EPS = 1e-8;
const double PI = acos(-1.0);

int main() {
    freopen("r2cmax.in", "r", stdin);
    freopen("r2cmax.out", "w", stdout);
    int n;
    cin >> n;
    int time[2][n];
    int max_time = 100050;
    for (int i = 0; i < n; i++) {
        cin >> time[0][i];
    }
    for (int i = 0; i < n; i++) {
        cin >> time[1][i];
    }
    int dp[2][max_time];
    for (int j = 0; j < max_time; j++) {
            dp[0][j] = dp[1][j] = INF;
    }
    dp[0][0] = 0;
    int st = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < max_time; j++) {
            dp[st][j] = dp[(st + 1) % 2][j] + time[1][i - 1];
            if (j >= time[0][i - 1]) {
                dp[st][j] = min(dp[st][j], dp[(st + 1) % 2][j - time[0][i - 1]]);
            }
        }
        st = (st + 1) % 2;
    }
    int ans = INF + 1;
    for (int j = 0; j < max_time; j++) 
        ans = min(ans, max(j, dp[(st + 1) % 2][j]));
    cout << ans << endl;
    return 0;
}
