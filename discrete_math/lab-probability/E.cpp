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

typedef vector<vector<double> > matrix;

int n;
matrix d;

matrix mul(matrix a, matrix b)
{
    matrix c;
    c.resize(n);
    for (int i = 0; i < n; i++)
        c[i].resize(n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            c[i][j] = 0;
            for (int k = 0; k < n; k++)
                c[i][j] += a[i][k] * b[k][j];
        }
    }
    return c;
}

matrix power(matrix a, int k)
{
    matrix b = a;
    for (int i = 0; i < k; i++)
        a = mul(a, b);
    return a;
}

int main()
{
    #ifdef LOCAL
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #else
        freopen("markchain.in", "r", stdin);
        freopen("markchain.out", "w", stdout);
    #endif
    cin >> n;
    d.resize(n);
    for (int i = 0; i < n; i++)
    {
        d[i].resize(n);
        for (int j = 0; j < n; j++)
            cin >> d[i][j];
    }
    d = power(d, 101);
    for (int i = 0; i < n; i++)
        printf("%.12lf\n", d[0][i]);
    return 0;
}