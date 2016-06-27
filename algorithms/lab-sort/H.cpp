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
   
const int MAXN = 100001;
const int INF = 2 * (1e9) + 1;
const ll INF_64 = (1LL << 62);
const int MOD = 1000000007;
  
const double EPS = 1e-9;
const double PI = acos(-1.0);
  
int n, m, k;
vector<vector<pair<int, int> > > ans;

int main()
{
    #ifdef LOCAL
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #else
        freopen("netbuild.in", "r", stdin);
        freopen("netbuild.out", "w", stdout);
    #endif
    cin >> n;
    int npow = 1;
    while (npow < n)
        npow *= 2;
    int m = 0;
    for (int l = 2; l <= npow; l *= 2)
    {
        for (int p = l; p >= 2; p /= 2)
        {
            vector<pair<int, int> > layer;
            for (int i = 0; i < npow; i += p)
            {
                for (int j = i; j <= i + (p / 2); j++)
                {
                    if (j == (p / 2) + i)
                        break;
                    int lr = 0;
                    if (p == l)
                        lr = 2 * i + p - j;
                    else
                        lr = j + (p / 2) + 1;
                    if (lr <= n && j + 1 <= n)
                        layer.pb(mp(j + 1, lr)), m++;
                }
            }
            ans.pb(layer);
        }
    }

    cout << n << ' ' << m << ' ' << sz(ans) << endl;
    for (int i = 0; i < sz(ans); i++)
    {
        cout << sz(ans[i]) << ' ';
        for (int j = 0; j < sz(ans[i]); j++)
            cout << ans[i][j].fr << ' ' << ans[i][j].sc << ' ';
        cout << endl;
    }
    return 0;
}