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
vector<int> pf;

void prefix_function(string s) {
    int c = 0;
    pf[0] = 0;
    for (int i = 1; i < sz(s); i++) {
        int j = pf[i - 1];
        while (j > 0 && s[j] != s[i])
            j = pf[j - 1], c++;
        if (s[i] == s[j])
            j++;
        pf[i] = j;
    }
}

int main() {
    freopen("search2.in", "r", stdin);
    freopen("search2.out", "w", stdout);
    cin >> p >> t;
    string kmp = p + "#" + t;
    pf.resize(sz(kmp));
    prefix_function(kmp);
    for (int i = sz(p) + 1; i < sz(kmp); i++) {
        if (pf[i] == sz(p)) {
            ans.pb(i - 2 * sz(p));
        }
    }
    cout << sz(ans) << endl;
    for (int i = 0; i < sz(ans); i++) {
        cout << ans[i] + 1 << ' ';
    }
    return 0;
}
