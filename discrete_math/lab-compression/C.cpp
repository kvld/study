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
#define pii pair<int, int>
 
using namespace std;

typedef long long ll;
 
const int MAXN = 10000;
const double INF = 2 * (1e9) + 1;
const ll INF_64 = (1LL << 62);
const int MOD = 1000000007;

const double EPS = 1e-8;
const double PI = acos(-1.0);

string s;
string q = "abcdefghijklmnopqrstuvwxyz";

int main()
{
    #ifdef LOCAL
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #else
        freopen("mtf.in", "r", stdin);
        freopen("mtf.out", "w", stdout);
    #endif
    cin >> s;
    for (int i = 0; i < sz(s); i++)
    {
        char t = s[i];
        for (int j = 0; j < 26; j++)
        {
            if (q[j] == t)
            {
                cout << j + 1 << ' ';
                q.erase(q.begin() + j);
                q = t + q;
                break;
            }
        }
    }
    return 0;
}