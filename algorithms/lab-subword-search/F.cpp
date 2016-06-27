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

using namespace std;

typedef long long ll;

const int MAXN = 200;
const int INF = 2 * (1e9) + 1;
const ll INF_64 = (1LL << 62);
const int MOD = 1000000007;

const double EPS = 1e-8;
const double PI = acos(-1.0);

string s;
vector<int> ans;
vector<int> z;

void z_function(string s) {
    z[0] = sz(s);
    int l = 0, r = 0;
    for (int i = 1; i < sz(s); i++) {
        if (i <= r)
            z[i] = min(z[i - l], r - i + 1);
        while (i + z[i] < sz(s) && s[z[i]] == s[i + z[i]])
            z[i]++;
        if (r < i + z[i] - 1) {
            l = i;
            r = i + z[i] - 1;
        }
    }
}

int main() {
    freopen("period.in", "r", stdin);
    freopen("period.out", "w", stdout);
    cin >> s;
    z.resize(sz(s));
    z_function(s);
    for (int i = 1; i < sz(s); i++) {
        if (sz(s) % i == 0 && (i + z[i] == sz(s))) {
            cout << i;
            return 0;
        }
    }
    cout << sz(s);
    return 0;
}
