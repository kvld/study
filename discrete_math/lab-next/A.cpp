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

string s;

int main()
{
    #ifdef LOCAL
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #else
        freopen("nextvector.in", "r", stdin);
        freopen("nextvector.out", "w", stdout);
    #endif
    cin >> s;
    string t = s;
    for (int i = sz(s) - 1; i >= 0; i--)
    	if (t[i] == '1')
    	{
    		t[i] = '0';
    		for (int j = i + 1; j < sz(s); j++)
    			t[j] = '1';
    		break;
    	}
    cout << (s == t ? "-" : t) << endl;
    t = s;
    for (int i = sz(s) - 1; i >= 0; i--)
    	if (t[i] == '0')
    	{
    		t[i] = '1';
    		for (int j = i + 1; j < sz(s); j++)
    			t[j] = '0';
    		break;
    	}
    cout << (s == t ? "-" : t) << endl;
    return 0;
}