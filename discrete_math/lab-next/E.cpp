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
        freopen("nextbrackets.in", "r", stdin);
        freopen("nextbrackets.out", "w", stdout);
    #endif
    cin >> s;
    string t = s;
    int balance = 0;
    for (int i = sz(s) - 1; i >= 0; i--)
    {
        if (s[i] == '(')
            balance--;
        if (s[i] == ')')
            balance++;
        if (s[i] == '(' && balance > 0)
        {
            cerr << i << endl;
            s[i] = ')';
            int len = sz(s) - i - balance, j = i + 1;
            len /= 2;
            for (j = i + 1; len != 0; j++, len--)
                s[j] = '(';
            for (; j < sz(s); j++)
                s[j] = ')';
            break;
        }
    }
    if (t == s)
    {
        cout << '-';
        return 0;
    }
    cout << s;
    return 0;
}