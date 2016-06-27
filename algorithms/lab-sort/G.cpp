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
vector<vector<pair<int, int> > > layers;

int main()
{
    #ifdef LOCAL
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #else
        freopen("netcheck.in", "r", stdin);
        freopen("netcheck.out", "w", stdout);
    #endif
    cin >> n >> m >> k;
    for (int i = 0; i < k; i++)
    {
        int r;
        cin >> r;
        vector<pair<int, int> > new_layer;
        for (int j = 0; j < r; j++)
        {
            int x, y;
            cin >> x >> y;
            if (x > y)
                swap(x, y);
            new_layer.pb(mp(--x, --y));
        }
        layers.pb(new_layer);
    }
    bool good = true;
    for (int mask = 0; mask < (1 << n); mask++)
    {
        vector<int> bits (n);
        for (int i = 0; i < n; i++)
            bits[i] = 1 & (mask >> i);
        for (int i = 0; i < k; i++)
        {
            for (int j = 0; j < sz(layers[i]); j++)
            {
                if (bits[layers[i][j].fr] > bits[layers[i][j].sc])
                    swap(bits[layers[i][j].fr], bits[layers[i][j].sc]);
            }
        }
        bool is_sorted = true;
        for (int i = 1; i < n; i++)
            if (bits[i - 1] > bits[i])
                is_sorted = false;
        if (!is_sorted)
            good = false;
    }
    if (good)
        cout << "Yes";
    else
        cout << "No";
    return 0;
}