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
vector<string> ans;

string num_to_str(int x)
{
    string ans = "";
    while (x != 0)
    {
        ans += '0' + (x % 10);
        x /= 10;
    }
    reverse(all(ans));
    return ans;
}

void gen(int n, int k, vector<int> a)
{
    //cout << n << ' ' << k << endl;
    if (k == 0)
        return;
    if (n == 0)
    {
        string t = "";
        for (int i = sz(a) - 1; i >= 0; i--)
        {
            t += num_to_str(a[i]);
            if (i != 0)
                t += '+';
        }
        ans.pb(t);
        return;
    }
    else
    {
        if (n - k >= 0)
        {
            a.pb(k);
            gen(n - k, k, a);
            a.pop_back();
        }
        if (k >= 1)
        {
            gen(n, k - 1, a);
        }
    }
}

int main()
{
    #ifdef LOCAL
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #else
        freopen("partition.in", "r", stdin);
        freopen("partition.out", "w", stdout);
    #endif
    cin >> n;
    vector<int> tmp;
    gen(n, n, tmp);
    sort(all(ans));
    reverse(all(ans));
    for (int i = sz(ans) - 1; i >= 0; i--)
        cout << ans[i] << endl;
    return 0;
}