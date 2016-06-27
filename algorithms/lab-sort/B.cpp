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

int n;
int a[100000];
int k;

int binarySearch(int x, bool leftLess) 
{
    int l = 0, r = n;
    while (r - l > 1) 
    {
        int mid = (r + l) / 2;
        if (a[mid] < x || (leftLess && a[mid] == x)) 
        {
            l = mid;
        } 
        else 
        {
            r = mid;
        }
    }
    if (a[l] == x) 
    {
        return l + 1;
    } else if (a[r] == x) 
    {
        return r + 1;
    }
    return -1;
}

int main()
{
    #ifdef LOCAL
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #else
        freopen("binsearch.in", "r", stdin);
        freopen("binsearch.out", "w", stdout);
    #endif
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    cin >> k;
    int q;
    for (int i = 0; i < k; i++)
    {
        cin >> q;
        int left = binarySearch(q, false);
        int right = binarySearch(q, true);
        cout << left << ' ' << right << endl;
    }
    return 0;
}