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

vector<map<char, int> > edges;


int main() {
    freopen("trie.in", "r", stdin);
    freopen("trie.out", "w", stdout);
    string s;
    cin >> s;

    edges.pb(map<char, int>());
    string cur_suffix = "";
    int edges_c = 0;
    for (int i = 0; i < sz(s); i++) {
        cur_suffix = s[sz(s) - i - 1] + cur_suffix;
        
        int cur = 0;
        for (int j = 0; j < sz(cur_suffix); j++) {
            char c = cur_suffix[j];
            if (edges[cur].find(c) == edges[cur].end()) {
                edges.pb(map<char, int>());
                edges[cur][c] = sz(edges) - 1;
                edges_c++; 
            }
            cur = edges[cur][c];
        }
    }
    cout << sz(edges) << ' ' << edges_c << endl;
    for (int i = 0; i < sz(edges); i++) {
        for (auto it = edges[i].begin(); it != edges[i].end(); it++) {
            cout << i + 1 << ' ' << it->second + 1 <<  ' ' << it->first << endl;            
        }
    }

    return 0;
}
