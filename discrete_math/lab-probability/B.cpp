
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
   
double px(double x, int n)
{
    if (n == 1)
        return double(x);
    if (n == 2)
        return double(x * x);
    if (n == 3)
        return double(x * x * x);
}
 
int n, m, k;
double p[10001];
 
int main()
{
    #ifdef LOCAL
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #else
        freopen("shooter.in", "r", stdin);
        freopen("shooter.out", "w", stdout);
    #endif
    cin >> n >> m >> k;
    double A = 0.0;
    for (int i = 0; i < n; i++)
    {
    	cin >> p[i];
        A += px((1.0 - p[i]), m);
    }
    double B = px((1.0 - p[k - 1]), m);
    double P = (B / A);
    assert(A != 0);
    printf("%.14f", P);
    return 0;
}