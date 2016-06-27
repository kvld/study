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
#define prev pprev

using namespace std;

typedef long long ll;

const int MAXN = 50001;
const int INF = 2 * (1e9) + 1;
const ll INF_64 = (1LL << 62);
const int MOD = 1000000007;

const double EPS = 1e-8;
const double PI = acos(-1.0);

int root;
int parent[MAXN];
int prev[MAXN];
int pi[MAXN];
int p[MAXN];
ll begin_time[MAXN];

struct job {
    int p, w, num;    

    bool operator<(job const& rhs) const {
        if (num == rhs.num || root == rhs.num) {
           return false;
        }
        if (root == num) {
           return true;
        }
        if (w * rhs.p == p * rhs.w) {
            return num < rhs.num;
        }
        return w * rhs.p - p * rhs.w < 0; 
    }

    void add_v(job * c) {
        p += c->p;
        w += c->w;
        parent[c->num] = prev[num];
        prev[num] = prev[c->num];
        
    }
};

int n, m;
vector<job> a;

int get(int x) {
    return p[x] == x ? p[x] : p[x] = get(p[x]);
}

void unite(int x, int y) {
    x = get(x);
    y = get(y);
    p[y] = x;
}

struct comparable {
    bool operator()(job* const& a, job* const& b) {
        return (*a) < (*b);
    }
};

int main() {
    freopen("p1outtreewc.in", "r", stdin);
    freopen("p1outtreewc.out", "w", stdout);
    cin >> n;
    for (int i = 0; i < n; i++) {
        int t;
        scanf("%d", &t);
        a.pb(job{t, 0, i});
    } 
    for (int i = 0; i < n; i++) {
        int t;
        scanf("%d", &t);
        a[i].w = t;
    }
    for (int i = 0; i < n; i++) {
        parent[i] = -1;
        prev[i] = i;
    }
    for (int i = 0; i < n - 1; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        parent[--x] = --y;
    }
    root = -1;
    for (int i = 0; i < n; i++) {
        if (parent[i] == -1) {
            root = i;
            break;
        }
    }
    
    //cout << root << endl;
    
    for (int i = 0; i < n; i++) {
        p[i] = i;
    }
    
    vector<job> J (all(a));
    set<job *, comparable> s;

    for (int i = 0; i < sz(a); i++) {
        s.insert(&J[i]);
    }
    while (sz(s) > 1) {
        auto last_it = s.end();
        last_it--;
        job* t = *last_it;
        //cout << t->num << endl;
        s.erase(last_it);

        if (t->num != root) {
            int j = get(parent[t->num]);
            s.erase(&J[j]);

            J[j].add_v(t);
            unite(J[j].num, t->num);

            s.insert(&J[j]);
        }
    }
    int k = 0;
    int cur = prev[(*s.begin())->num];
    while (true) {
        //cout << cur << endl;
        pi[k++] = cur;
        if (parent[J[cur].num] != -1) {
           cur = parent[J[cur].num];
        } else {
            break;
        }
    }

    ll time = 0, ans = 0;
    for (int i = n - 1; i >= 0; i--) {
        int j = pi[i];
        begin_time[j] = time;
        time += a[j].p;
        ans += time * 1ll * a[j].w;
    }

    //cout << ans << endl;
    printf("%lld\n", ans);
    for (int i = 0; i < n; i++) {
        printf("%lld ", begin_time[i]);
    //    cout << begin_time[i] << ' ';
    }


    return 0;
}
