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

string s;
vector<int> ans;
vector<int> pf;

void prefix_function(string s) {
    int c = 0;
    pf[0] = 0;
    for (int i = 1; i < sz(s); i++) {
        int j = pf[i - 1];
        while (j > 0 && s[j] != s[i])
            j = pf[j - 1], c++;
        if (s[i] == s[j])
            j++;
        pf[i] = j;
    }
}

int main() {
    freopen("prefix.in", "r", stdin);
    freopen("prefix.out", "w", stdout);
    cin >> s;
    pf.resize(sz(s));
    prefix_function(s);
    for (int i = 0; i < sz(s); i++) {
        cout << pf[i] << ' ';
    }
    return 0;
}
