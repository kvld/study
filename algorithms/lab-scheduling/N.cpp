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

int main() {
    freopen("f2cmax.in", "r", stdin);
    freopen("f2cmax.out", "w", stdout);
    int n;
    cin >> n;
    int time[2][n];
    set<pair<int, pair<int, int> > > s;
    for (int i = 0; i < n; i++) {
        cin >> time[0][i];
        s.insert(mp(time[0][i], mp(0, i)));
    }
    for (int i = 0; i < n; i++) {
        cin >> time[1][i];
        s.insert(mp(time[1][i], mp(1, i)));
    }
    deque<int> L, R;
    vector<bool> used (n, false);
    while (sz(s) > 0) {
        pair<int, pair<int, int > > t = *s.begin();
        s.erase(s.begin());
        if (used[t.sc.sc]) {
            continue;
        }
        used[t.sc.sc] = true;
        if (t.sc.fr == 0) {
            L.pb(t.sc.sc);
        } else {
            R.push_front(t.sc.sc);
        }
    }
    for (auto e : R) {
        L.pb(e);
    }
    ll t = 0, t_all = 0;
    for (int i = 0; i < sz(L); i++) {
        t += time[0][L[i]];
        t_all = max(t_all, t) + time[1][L[i]];
    }
    cout << t_all << endl;
    for (auto e : L) {
        cout << e + 1 << ' ';
    }
    cout << endl;
    for (auto e : L) {
        cout << e + 1 << ' ';
    }
    return 0;
}
