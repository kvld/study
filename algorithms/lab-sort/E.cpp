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
  
int n, m, k;
vector<string> a (1000), b (1000);

int main()
{
    #ifdef LOCAL
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #else
        freopen("radixsort.in", "r", stdin);
        freopen("radixsort.out", "w", stdout);
    #endif
    cin >> n >> m >> k;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int i = m - 1; i >= 0 && k > 0; i--, k--)
    {
        vector<int> c (26, 0);
        for (int j = 0; j < n; j++)
        {
            c[a[j][i] - 'a']++;
        }
        int cnt = 0;
        for (int j = 0; j < 26; j++)
        {
            int tmp = c[j];
            c[j] = cnt;
            cnt += tmp;
        }
        for (int j = 0; j < n; j++)
        {
            b[c[a[j][i] - 'a']] = a[j];
            c[a[j][i] - 'a']++;
        }
        a = b;
    }
    for (int i = 0; i < n; i++)
        cout << a[i] << endl;
    return 0;
}