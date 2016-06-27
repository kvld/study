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
    int d, w, num;    

    bool operator<(job const& rhs) const {
        return d < rhs.d;
    }
};

struct comparable {
    bool operator()(job const& a, job const& b) {
        if (a.w == b.w) {
            return a.d > b.d;
        }
        return a.w < b.w;
    }
};

int main() {
    freopen("p1sumwu.in", "r", stdin);
    freopen("p1sumwu.out", "w", stdout);
    int n;
    cin >> n;
    multiset<job, comparable> jobs;
    vector<job> a;
    for (int i = 0; i < n; i++) {
        int d, w;
        cin >> d >> w;
        a.pb(job{d, w, i});
    }
    sort(all(a));

    ll time = 1;
    for (int i = 0; i < n; i++) {
        if (time <= a[i].d) {
            jobs.insert(a[i]);
            time++;
        } else {
            if (jobs.begin()->w < a[i].w) {
                jobs.erase(jobs.begin());
                jobs.insert(a[i]);
            }
        }
    }

    time = 0;
    vector<job> schedule (all(jobs));
    sort(all(schedule));
    vector<ll> begin_time (n, -1);

    ll sumw = 0;
    for (int i = 0; i < sz(a); i++) {
        sumw += a[i].w;
    }
    for (int i = 0; i < sz(schedule); i++) {
    //    cout << schedule[i].num << endl;
        begin_time[schedule[i].num] = time;
        sumw -= schedule[i].w;
        time++;
    }
    for (int i = 0; i < sz(begin_time); i++) {
        if (begin_time[i] == -1) {
            begin_time[i] = time++;
        }
    }
    cout << sumw << endl;
    for (int i = 0; i < n; i++) {
        cout << begin_time[i] << ' ';
    }
    return 0;
}
