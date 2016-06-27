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
const double INF = 2 * (1e9) + 1;
const ll INF_64 = (1LL << 62);
const int MOD = 1000000007;
   
const double EPS = 1e-8;
const double PI = acos(-1.0);
   
int x, n;
vector<int> a, b;
 
int main()
{
    #ifdef LOCAL
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #else
        freopen("lottery.in", "r", stdin);
        freopen("lottery.out", "w", stdout);
    #endif
    b.pb(0);
    cin >> x >> n;
    for (int i = 0; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        a.pb(u);
        b.pb(v);
    }
    double mo = 0, mm = 1;
    for (int i = 0; i < n; i++)
    {
        mm *= a[i];
        mo += b[i] * (a[i] - 1) / mm;
    }
    printf("%.12f", x - mo - (b[n] / mm));
    return 0;
}