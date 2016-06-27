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

string s, t;
vector<map<char, int> > edges;
vector<int> lnk;
vector<int> length;
int last;

vector<bool> used;
vector<bool> tstates;
vector<ll> cnt;

void dfs(int v) {
    used[v] = true;

    if (tstates[v]) {
        cnt[v] = 1;
    } else {
        cnt[v] = 0;
    }
    for (auto it = edges[v].begin(); it != edges[v].end(); it++) {
        if (!used[it->second]) {
            dfs(it->second);
        }
        cnt[v] += cnt[it->second];
    }
}

int main() {
    freopen("refrain.in", "r", stdin);
    freopen("refrain.out", "w", stdout);
    t = "";
    int n, tmp;
    cin >> n >> tmp;
    for (int i = 0; i < n; i++) {
        cin >> tmp;
        tmp--;
        t += char(tmp + '0');
    }
    edges.pb(map<char, int>());
    lnk.pb(-1);
    length.pb(0);
    last = 0;

    vector<int> pos;
    pos.pb(0);
    for (int i = 0; i < sz(t); i++) {
        edges.pb(map<char, int>());
        length.pb(i + 1);
        lnk.pb(0);
        pos.pb(last);
        int r = sz(edges) - 1;

        int p = last;
        while (p >= 0 && edges[p].find(t[i]) == edges[p].end()) {
            edges[p][t[i]] = r;
            p = lnk[p];
        }

        if (p != -1) {
            int q = edges[p][t[i]];
            if (length[p] + 1 == length[q]) {
                lnk[r] = q;
            } else {
                edges.pb(edges[q]);
                length.pb(length[p] + 1);
                lnk.pb(lnk[q]);
                int new_q = sz(edges) - 1;
                lnk[q] = lnk[r] = new_q;
                pos.pb(p); 
                while (p >= 0 && edges[p][t[i]] == q) {
                    edges[p][t[i]] = new_q;
                    p = lnk[p];
                }
            }
        }
        last = r;
    }

    tstates.assign(sz(edges), false);
    cnt.assign(sz(edges), 0);
    int cur = last;
    while (cur != -1) {
        tstates[cur] = true;
        cur = lnk[cur];
    }
    used.resize(sz(edges)); 
    dfs(0);
    
    ll best = 0;
    int best_pos = 0;
    for (int i = 0; i < sz(edges); i++) {
        if (cnt[i] * 1ll * length[i] > best) {
            best = cnt[i] * 1ll * length[i];
            best_pos = i;
        }
    }

    //cout << t << endl;
    //cout << pos[best_pos] << ' ' << length[best_pos] << endl;
    //string substr = t.substr(pos[best_pos] - length[best_pos] + 1, length[best_pos]);
    vector<char> ans;
    ans.resize(length[best_pos]);
    cur = best_pos;
    while (cur != 0) {
        int i = pos[cur];
        for (auto it = edges[i].begin(); it != edges[i].end(); it++) {
            if (it->second == cur) {
                //cout << length[cur] - 1 << ' ' << it->first << ' ' << sz(ans) << endl;
                ans[length[cur] - 1] = it->first;
            }
        }
        cur = pos[cur];
    }

    cout << best << endl << sz(ans) << endl;
    for (int i = 0; i < sz(ans); i++) {
        int val = int(ans[i]) - int('0') + 1;
        cout << val << (i == sz(ans) - 1 ? "" : " ");
    }

    return 0;
}
