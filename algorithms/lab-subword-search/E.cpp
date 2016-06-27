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

string p, t;
vector<int> ans;
vector<int> z1;
vector<int> z2;

void z_function(string s, vector<int>& z) {
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
    freopen("search3.in", "r", stdin);
    freopen("search3.out", "w", stdout);
    cin >> p >> t;
    string s = p + "#" + t;
    z1.resize(sz(s));
    z_function(s, z1);
    reverse(all(p));
    reverse(all(t));
    s = p + "#" + t;
    z2.resize(sz(s));
    z_function(s, z2);
    /*
    for (int i = 1; i < sz(s); i++) {
        cout << z1[i] << ' ' << z2[i] << endl;
    }
    */
    for (int i = sz(p) + 1; i < sz(s) - sz(p) + 1; i++) {
        cout << i << ' ' << sz(s) - i + 1 << endl;
        if (z1[i] + z2[sz(s) - i + 1] >= sz(p) - 1) {
            ans.pb(i - sz(p) - 1);
        }
    }
    cout << sz(ans) << endl;
    for (int i = 0; i < sz(ans); i++) {
        cout << ans[i] + 1 << ' ';
    }
    return 0;
}
