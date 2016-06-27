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
    freopen("o2cmax.in", "r", stdin);
    freopen("o2cmax.out", "w", stdout);
    int n;
    scanf("%d", &n);
    int time[2][n];
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &time[i][j]);
        }
    }
    vector<int> I, J;
    ll suma = 0, sumb = 0, cmax = 0;
    for (int i = 0; i < n; i++) {
        suma += time[0][i];
        sumb += time[1][i];
        cmax = max(cmax, (ll)(time[0][i] + time[1][i]));
    }
    cmax = max(cmax, max(suma, sumb));
    for (int i = 0; i < n; i++) {
        if (time[0][i] <= time[1][i]) {
            I.pb(i);
        } else {
            J.pb(i);
        }
    }
    int maxa = -1, maxb = -1;
    for (int i = 0; i < sz(I); i++) {
        if (maxa == -1 || time[0][maxa] < time[0][I[i]])
            maxa = I[i];
    }
    for (int i = 0; i < sz(J); i++) {
        if (maxb == -1 || time[1][maxb] < time[1][J[i]])
            maxb = J[i];
    }
    cout << cmax << endl;

    bool inv = false;
    if      (maxa != -1 && maxb == -1) inv = false;
    else if (maxa == -1 && maxb != -1) inv = true;
    else if (maxa != -1 && maxb != -1) inv = (time[0][maxa] > time[1][maxb] ? false : true);

    if (inv) {
        for (int i = 0; i < n; i++) {
            swap(time[0][i], time[1][i]);
        }
        swap(I, J);
    }


    vector<ll> begin_time_a (n, -1), begin_time_b (n, -1);
    ll timea = 0;
    int tindex = inv ? maxb : maxa;

    for (int i = 0; i < sz(I); i++) {
        if (I[i] == tindex) {
            continue;
        }
        begin_time_a[I[i]] = timea;
        timea += time[0][I[i]];
    }
    timea = cmax - time[0][tindex];
    begin_time_a[tindex] = timea;
    for (int i = 0; i < sz(J); i++) {
        timea -= time[0][J[i]];
        begin_time_a[J[i]] = timea;
    }

    ll timeb = 0;
    begin_time_b[tindex] = timeb;
    timeb += time[1][tindex];
    for (int i = 0; i < sz(I); i++) {
        if (I[i] == tindex) {
           continue;
        }
        begin_time_b[I[i]] = timeb;
        timeb += time[1][I[i]];
    }
    timeb = cmax;
    for (int i = 0; i < sz(J); i++) {
        timeb -= time[1][J[i]];
        begin_time_b[J[i]] = timeb;
    }

    if (inv) {
        swap(begin_time_a, begin_time_b);
    }

    for (int i = 0; i < n; i++) {
        cout << begin_time_a[i] << ' ';
    }

    cout << endl;
    for (int i = 0; i < n; i++) {
        cout << begin_time_b[i] << ' ';
    }
    return 0;
}
