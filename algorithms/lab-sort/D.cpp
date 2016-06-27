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
const double INF = 2 * (1e18) + 1;
const ll INF_64 = (1LL << 62);
const int MOD = 1000000007;
  
const double EPS = 1e-9;
const double PI = acos(-1.0);
  
int n;
double a;

double f(double x) 
{
    vector <double> h(n);
    h[0] = a;
    h[1] = x;

    for (int i = 2; i < n; i++) 
    {
        h[i] = 2 * h[i - 1] - h[i - 2] + 2;
        if (h[i] < EPS)
            return INF;
    }
    return h[n - 1];
}

int main()
{
    #ifdef LOCAL
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #else
        freopen("garland.in", "r", stdin);
        freopen("garland.out", "w", stdout);
    #endif
    cin >> n >> a;
    double left = 0, right = 1e9;
    for (int iter = 0; iter < 110; iter++)
    {
        double xl = (right + 2 * left) / 3;
        double xr = (left + 2 * right) / 3;
        if (f(xl) < f(xr))
        {
            right = xr;
        }
        else
        {
            left = xl;
        }
    }
    printf("%.2lf\n", f((left + right) / 2));
    return 0;
}