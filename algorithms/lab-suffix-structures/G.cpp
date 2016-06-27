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

int main() {
    freopen("common.in", "r", stdin);
    freopen("common.out", "w", stdout);
    getline(cin, s);
    getline(cin, t);
    if (t.length() < s.length()) {
        swap(s, t);
    }
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

    int cur = 0, max_len = 0, ans_len = 0;
    string cur_ans;
    for (int i = 0; i < sz(s); i++) {
        char c = s[i];

        while (cur != -1 && edges[cur].find(c) == edges[cur].end()) {
            cur = lnk[cur];
            max_len = length[cur];
        }

        if (cur == -1) {
            cur = max_len = 0;
        }

        if (edges[cur].find(c) != edges[cur].end()) {
            cur = edges[cur][c];
            max_len++;
        }

        if (ans_len < max_len) {
            ans_len = max_len;
            cur_ans = s.substr(i - max_len + 1, max_len);
        } else if (ans_len == max_len) {
            string possible_ans = s.substr(i - ans_len + 1, ans_len);
            if (possible_ans < cur_ans) {
                cur_ans = possible_ans;
            }
        }
    }
    cout << cur_ans << endl;
    return 0;
}
