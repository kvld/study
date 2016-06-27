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

bool check(string b)
{
    vector<char> stack;
    for (int i = 0; i < sz(b); i++)
        if (b[i] == '(')
        {
            stack.pb(b[i]);
        }
        else
        {
            if (sz(stack) == 0)
                return false;
            stack.pop_back();
        }
    return (sz(stack) == 0);
}

void gen(char bracket, int balance, string res)
{
    if (balance < -1)
    {
        return;
    }
    if (sz(res) == n)
    {
        if (balance == 0 && check(res))
            cout << res << endl;
        return;
    }
    gen('(', balance + 1, res + bracket);
    gen(')', balance - 1, res + bracket);
}

int main()
{
    #ifdef LOCAL
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #else
        freopen("brackets.in", "r", stdin);
        freopen("brackets.out", "w", stdout);
    #endif
    cin >> n;
    n *= 2;
    gen('(', 0, "");
    gen(')', 0, "");
    return 0;
}