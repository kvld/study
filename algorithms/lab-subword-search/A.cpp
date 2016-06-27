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

int main() {
    freopen("search1.in", "r", stdin);
    freopen("search1.out", "w", stdout);
    cin >> p >> t;
    for (int i = 0; i < sz(t); i++) {
        bool found = true;
        for (int j = 0; j < sz(p); j++) {
            if (i + j >= sz(t)) {
                found = false;
                break;
            }
            if (t[i + j] != p[j]) {
                found = false;
                break;
            }
        }
        if (found) {
            ans.pb(i);
        }
    }
    cout << sz(ans) << endl;
    for (int i = 0; i < sz(ans); i++) {
        cout << ans[i] + 1 << ' ';
    }
    return 0;
}
