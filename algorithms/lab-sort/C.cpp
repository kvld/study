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
  
int a[30000000];
int n = 0, k, nk, A, B, C, x, y;

int qsort(int l, int r, int k) 
{
    if (l == r)
        return a[l];
    if (l > r)
        return 0;
    int mid = a[l + rand() % (r - l + 1)];
    int i = l, j = r;
    do {
        while (a[i] < mid)
            i++;
        while (a[j] > mid)
            j--;
        if (i <= j)
        {
            swap(a[i], a[j]);
            i++;
            j--;
        }
    } while (i <= j);
 
    if (l <= k && k <= j)
        return qsort(l, j, k);
    if (i <= k && k <= r)
        return qsort(i, r, k);
    return mid;
}

int main()
{
    srand(time(NULL));
    #ifdef LOCAL
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #else
        freopen("kth.in", "r", stdin);
        freopen("kth.out", "w", stdout);
    #endif
    cin >> nk >> k >> A >> B >> C >> a[0] >> a[1];
    k--;
    for (int i = 2; i < nk; i++)
    {
        a[i] = A * a[i - 2] + B * a[i - 1] + C;
    }
    cout << qsort(0, nk - 1, k);
    return 0;
}