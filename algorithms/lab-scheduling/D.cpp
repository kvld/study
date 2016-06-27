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
    int p, d, num;    
    ll begin_time;

    bool operator<(job const& rhs) const {
        return d < rhs.d;
    }
};

struct comparable {
    bool operator()(job const& a, job const& b) {
        return a.p > b.p;
    }
};

int main() {
    freopen("p1sumu.in", "r", stdin);
    freopen("p1sumu.out", "w", stdout);
    int n;
    cin >> n;
    multiset<job, comparable> jobs;
    vector<job> a;
    for (int i = 0; i < n; i++) {
        int p, d;
        cin >> p >> d;
        a.pb(job{p, d, i});
    }
    sort(all(a));

    ll time = 0;
    for (int i = 0; i < n; i++) {
        jobs.insert(a[i]);

        a[i].begin_time = time;
        time += a[i].p;

        if (time > a[i].d) {
            time -= jobs.begin()->p;
            jobs.erase(jobs.begin());
        }
    }

    time = 0;
    vector<job> schedule (all(jobs));
    sort(all(schedule));
    vector<ll> begin_time (n, -1);
    for (int i = 0; i < sz(schedule); i++) {
        begin_time[schedule[i].num] = time;
        time += schedule[i].p;
    }
    cout << sz(schedule) << endl;
    for (int i = 0; i < n; i++) {
        cout << begin_time[i] << ' ';
    }
    return 0;
}
