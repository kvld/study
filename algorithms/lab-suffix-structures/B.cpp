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
    freopen("array.in", "r", stdin);
    freopen("array.out", "w", stdout);
    string s;
    getline(cin, s);
    char lc = char(0);
    s += lc;
    vector<int> suffix_array (sz(s));
    vector<int> buckets (max(512, sz(s)));
    for (int i = 0; i < sz(s); i++) {
        buckets[s[i]]++;
    }
    // ababb$ -> $aabbb
    int acc = 0;
    for (int i = 0; i < sz(buckets); i++) {
        acc += buckets[i];
        buckets[i] = acc - buckets[i];
    }
    
    for (int i = 0; i < sz(s); i++) {
        suffix_array[buckets[s[i]]] =  i;
        buckets[s[i]]++;
    }
    
    vector<int> c (sz(s));
    c[suffix_array[0]] = 0;
    for (int i = 1; i < sz(s); i++) {
        c[suffix_array[i]] = c[suffix_array[i - 1]];
        if (s[suffix_array[i]] != s[suffix_array[i - 1]]) {
            c[suffix_array[i]]++;
        }
    }
    vector<int> sa_tmp (sz(s));
    vector<int> c_tmp (sz(s));
    int last_c = c[suffix_array[sz(s) - 1]] + 1;
    for (int len = 1; len < sz(s); len *= 2) {
        fill(all(buckets), 0);
        for (int i = 0; i < sz(s); i++) {
            buckets[c[i]]++;
        }
        int acc = 0;
        for (int i = 0; i < last_c; i++) {
            acc += buckets[i];
            buckets[i] = acc - buckets[i];
        }
        for (int i = 0; i < sz(s); i++) {
            int index = (suffix_array[i] - len + sz(s)) % sz(s); 
            sa_tmp[buckets[c[index]]] = index;
            buckets[c[index]]++;
        }
        suffix_array = sa_tmp;
        /*
        for (int i =0; i < sz(suffix_array); i++) {
            cout << suffix_array[i] << ' ' ;
        }
        cout << endl;
        */
        c_tmp[suffix_array[0]] = 0;
        for (int i = 1; i < sz(s); i++) {
            c_tmp[suffix_array[i]] = c_tmp[suffix_array[i - 1]];
            if (c[suffix_array[i]] != c[suffix_array[i - 1]]) {
                c_tmp[suffix_array[i]]++;
            } else if (c[(suffix_array[i] + len) % sz(s)] != c[(suffix_array[i - 1] + len) % sz(s)]) {
                c_tmp[suffix_array[i]]++;
            }
        }
        c = c_tmp;
        last_c = c[suffix_array[sz(s) - 1]] + 1;
        /*
        for (int i = 0; i < sz(c); i++) {
            cout << c[i] << ' ';
        }
        cout << endl;
        */
    }

    for (int i = 1; i < sz(suffix_array); i++) {
        cout << suffix_array[i] + 1 << ' ';
    }
    return 0;
}
