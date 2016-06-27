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
  
int a[100000];
int n = 0, k;

void siftDown(int i) 
{
	while (2 * i + 1 < n) 
	{
		int l = 2 * i + 1, r = 2 * i + 2;
		int j = l;
		if (r < n && a[l] > a[r]) 
			j = r;
		if (a[i] <= a[j])
			break;
		swap(a[i], a[j]);
		i = j;
	}
}

void siftUp(int i) 
{
	while (a[i] < a[(i - 1) / 2])
	{
		swap(a[i], a[(i - 1) / 2]);
		i = (i - 1) / 2;
	}
}

int extract()
{
	int res = a[0];
	a[0] = a[n - 1];
	n--;
	siftDown(0);
	return res;
}

void insert(int i)
{
	n++;
	a[n - 1] = i;
	siftUp(n - 1);
}

int main()
{
    #ifdef LOCAL
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #else
        freopen("sort.in", "r", stdin);
        freopen("sort.out", "w", stdout);
    #endif
	cin >> k;
	for (int i = 0; i < k; i++)
	{
		scanf("%d", &a[i]);
	}
	n = k;
	for (int i = k / 2; i >= 0; i--)
		siftDown(i);
	for (int i = 0; i < k; i++)
	{
		printf("%d ", extract());
	}
	return 0;
}