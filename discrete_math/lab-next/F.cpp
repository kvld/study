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

int n;
vector<int> a;

int main()
{
    #ifdef LOCAL
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #else
        freopen("nextmultiperm.in", "r", stdin);
        freopen("nextmultiperm.out", "w", stdout);
    #endif
    cin >> n;
    a.resize(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    vector<int> t = a;
    
    for (int i = n - 1; i >= 0; i--)
    {
        if (i - 1 >= 0 && t[i - 1] < t[i])
        {
            int mn = INF, mnp;
            for (int j = i; j < n; j++)
            {
                if (mn >= t[j] && t[j] > t[i - 1])
                    mn = t[j], mnp = j;
            }
            swap(t[i - 1], t[mnp]);
            reverse(t.begin() + i, t.begin() + n);
            break;
        }
    }
    bool eq = (t == a);
    for (int i = 0; i < n; i++)
        cout << (eq ? 0 : t[i]) << ' ';
    cout << endl;
    return 0;
}