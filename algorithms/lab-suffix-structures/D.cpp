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

string t;
vector<string> s;
vector<map<char, int> > edges;
vector<int> lnk;
vector<int> length;
int last;

int main() {
    freopen("automaton.in", "r", stdin);
    freopen("automaton.out", "w", stdout);
    getline(cin, t);
    edges.pb(map<char, int>());
    lnk.pb(-1);
    length.pb(0);
    last = 0;

    for (int i = 0; i < sz(t); i++) {
        edges.pb(map<char, int>());
        length.pb(i + 1);
        lnk.pb(0);
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
                while (p >= 0 && edges[p][t[i]] == q) {
                    edges[p][t[i]] = new_q;
                    p = lnk[p];
                }
            }
        }
        last = r;
    }
    int edges_cnt = 0;
    cout << sz(edges) << ' ';
    for (auto it = edges.begin(); it != edges.end(); it++) {
        edges_cnt += it->size();
    }
    cout << edges_cnt << endl;
    for (auto it = edges.begin(); it != edges.end(); it++) {
        for (auto it1 = (*it).begin(); it1 != (*it).end(); it1++) {
            cout << std::distance(edges.begin(), it) + 1 << ' ' << it1->second + 1 << ' ' << it1->first << endl;
        }
    }

    vector<int> terminal_states;
    int cur = 0;
    for (int i = 0; i < sz(t); i++) {
        cur = edges[cur][t[i]];
    }
    while (cur != -1) {
        terminal_states.pb(cur + 1);
        cur = lnk[cur];
    }
    cout << sz(terminal_states) << endl;
    for (int i = 0; i < sz(terminal_states); i++) {
        cout << terminal_states[i] << ' ';
    }
    return 0;
}
