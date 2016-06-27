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

struct job {
    int d, num;    

    bool operator<(job const& rhs) const {
        return d > rhs.d;
    }
};

struct machine {
    int t, num, d;

    bool operator<(machine const& rhs) const {
        return t * d < rhs.t * rhs.d;
    }
};

int main() {
    freopen("qsumci.in", "r", stdin);
    freopen("qsumci.out", "w", stdout);
    int n, m;
    cin >> n >> m;
    vector<job> a;
    vector<machine> b;
    for (int i = 0; i < n; i++) {
        int t;
        cin >> t;
        a.pb(job{t, i});
    }
    for (int i = 0; i < m; i++) {
        int t;
        cin >> t;
        b.pb(machine{t, i, 1});
    }

    multiset<machine> s;
    for (int i = 0; i < sz(b); i++) {
        s.insert(b[i]);
    }
    vector<vector<int> > schedule (m);
    for (int i = 0; i < n; i++) {
        machine t = *s.begin();
        t.d++;
        schedule[t.num].pb(i);
        s.erase(s.begin());
        s.insert(t);
    }

    sort(all(a));
    vector<ll> machines_nums (n), begin_time (n);
    ll time = 0;
    for (int i = 0; i < m; i++) {
        time = 0;
        for (int j = 0; j < sz(schedule[i]); j++) {
            job cur_job = a[schedule[i][sz(schedule[i]) - j - 1]];
//            cout << cur_job.num << endl;
            machines_nums[cur_job.num] = i;
            begin_time[cur_job.num] = time;
            time += b[i].t * cur_job.d;
        }
    }
    /*ll ans = 0;
    for (int i = 0; i < n; i++) {
        ans += (begin_time[i] + b[machines_nums[i]].t * a[i].d);
    }*/
    ll ans = 0;
    for (int i = 0; i < m; i++) {
        time = 0;
        for (int j = 0; j < sz(schedule[i]); j++) {
            time += b[i].t * a[schedule[i][sz(schedule[i]) - j - 1]].d;
            ans += time;
        }
    }
    cout << ans << endl;
    for (int i = 0; i < n; i++) {
        cout << machines_nums[i] + 1 << ' ' << begin_time[i] << endl;
    }
    return 0;
}
