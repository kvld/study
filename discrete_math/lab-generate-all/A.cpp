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
 
int n = 0;
vector<string> a;


void gen(char c, string t)
{
    if (sz(t) == n - 1)
    {
        t += c;
        a.pb(t);
        return;
    }
    else
    {
        t += c;
        gen('0', t);
        if (c != '1')
            gen('1', t);
    }
}
 
int main()
{
    #ifdef LOCAL
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #else
        freopen("vectors.in", "r", stdin);
        freopen("vectors.out", "w", stdout);
    #endif
    cin >> n;
    gen('0', "");
    gen('1', "");
    cout << sz(a) << endl;
    for (int i = 0; i < sz(a); i++)
        cout << a[i] << endl;
    return 0;
}