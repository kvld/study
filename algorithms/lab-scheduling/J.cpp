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
    freopen("p1p1sumu.in", "r", stdin);
    freopen("p1p1sumu.out", "w", stdout);
    ll n, d1, d2, A, B, C, D;
    cin >> n;
    vector<int> scheduler (n + 10);
    cin >> d1 >> d2 >> A >> B >> C >> D;
    scheduler[min(d1, n + 1)]++;
    scheduler[min(d2, n + 1)]++;
    for (int i = 2; i < n; i++) {
        ll d = (A * d1 + B * d2 + C) % D;
        scheduler[min(d, n + 1)]++;
        d1 = d2;
        d2 = d;
    }
    ll time = 0, ans = 0;
    for (int i = 1; i < sz(scheduler); i++) {
        for (int j = 0; j < scheduler[i]; j++) {
            time++;
            if (time <= i) {
                ans++;
            }
        }
    }
    cout << ans << endl;
    return 0;
}
