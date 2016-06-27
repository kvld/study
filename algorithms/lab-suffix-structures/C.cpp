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

vector<int> build_suffix_array(string s) { 
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
    }
    return suffix_array;
}

vector<int> build_lcp(string s, vector<int> suffix_array) {
    vector<int> rv (sz(s));
    vector<int> lcp (sz(s));
    for (int i = 0; i < sz(s) - 1; i++) {
        rv[suffix_array[i]] = i;
    }
    int cur = 0;
    for (int i = 0; i < sz(s) - 1; i++) {
        if (rv[i] == sz(s) - 1) {
            lcp[sz(s) - 1] = -1;
            cur = 0;
        } else {
            while (max(i + cur, suffix_array[rv[i] + 1] + cur) < sz(s) && s[i + cur] == s[suffix_array[rv[i] + 1] + cur]) {
                cur++;
            }
            lcp[rv[i]] = cur;
        }

        if (cur > 0) {
            cur--;
        }
    }
    return lcp;
}

struct node;
int global_num = 0;
struct node {
    struct node* parent;
    vector<node*> c;
    int depth;
    int num;
    int max_depth;

    node(node* _parent, int _depth) : parent(_parent), depth(_depth) {
        c.clear();
        num = global_num++;
        max_depth = 0;
    }
};

int edges = 0;
node* add_next_suffix(node* prev, int len, int lcp) {
    if (!prev->depth || prev->depth == lcp) {
        node* added = new node(prev, len);
        prev->c.pb(added);
        edges++;
        return added;
    } else {
        if (prev->parent->depth < lcp) {
            node* inserted = new node(prev->parent, lcp);
            prev->parent->c.pop_back();
            prev->parent->c.pb(inserted);
            inserted->c.pb(prev); 
            edges++;
            prev->parent = inserted;
        }
        return add_next_suffix(prev->parent, len, lcp);
    }
}

node* build_suffix_tree(string s) {
    vector<int> sa = build_suffix_array(s);
    vector<int> lcp = build_lcp(s, sa);
    node* root = new node(NULL, 0);
    node* prev = root;
    for (int i = 1; i < sz(s); i++) {
        //cout << sz(s) - sa[i] - 1 << ' ' << lcp[i - 1] << endl;
        prev = add_next_suffix(prev, sz(s) - sa[i] - 1, lcp[i - 1]);
    }
    return root;
}

int dfs(node* v) {
    if (sz(v->c) == 0) {
        v->max_depth = v->depth;
    } else {
        for (auto child : v->c) {
            v->max_depth = max(v->max_depth, dfs(child));
        }
    }
    return v->max_depth;
}

pair<int, int> calculate_positions(node* parent, node* child, int len) {
    int start = len - child->max_depth + parent->depth;
    int end = start + child->depth - parent->depth - 1;
    return mp(start, end);
}

void traversal(node* tree, int len) {
    for (auto child : tree->c) {
        pair<int, int> poss = calculate_positions(tree, child, len);
        cout << tree->num + 1 << ' ' << child->num + 1 << ' ' << poss.fr + 1 << ' ' << poss.sc + 1 << endl; 
        traversal(child, len);
    }
}

int numc = 0;
void compress_dfs(node* v) {
    v->num = numc++;
    for (int i = 0; i < sz(v->c); i++) {
        while (sz(v->c[i]->c) == 1) {
            v->c[i]->c[0]->parent = v;
            v->c[i] = v->c[i]->c[0];
            edges--;
            global_num--;   
        }
    }
    for (auto child : v->c) {
        compress_dfs(child);
    }
}

int main() {
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);
    string s;
    cin >> s;
    s += char(0);
    vector<int> sa = build_suffix_array(s);
    vector<int> lcp = build_lcp(s, sa);
    node* tree = build_suffix_tree(s); 
    compress_dfs(tree);
    cout << global_num << ' ' << edges << endl;
    dfs(tree); 
    traversal(tree, sz(s) - 1);
    return 0;
}
