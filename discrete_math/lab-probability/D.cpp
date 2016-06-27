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
#include <stack>
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
    
const int MAXN = 100001;
const double INF = 2 * (1e9) + 1;
const ll INF_64 = (1LL << 62);
const int MOD = 1000000007;
   
const double EPS = 1e-9;
const double PI = acos(-1.0);

int n, m, absorbing_cnt = 0, nonabsorbing_cnt = 0;

vector<int> yy1, yy2;
vector<double> yy3;

vector<bool> absorbing;
double Q[410][410], R[410][410], E[410][410], N[410][410], G[410][410];
 

int main()
{
    #ifdef LOCAL
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #else
        freopen("absmarkchain.in", "r", stdin);
        freopen("absmarkchain.out", "w", stdout);
    #endif
    for (int i = 0; i < 410; i++)
        for (int j = 0; j < 410; j++)
            Q[i][j] = R[i][j] = E[i][j] = N[i][j] = G[i][j] = 0.0;

    cin >> n >> m;
    absorbing.assign(n, false);
    for (int i = 0; i < m; i++)
    {
        double x;
        int u, v;
        scanf("%d%d%lf", &u, &v, &x);
        yy1.pb(--u);
        yy2.pb(--v);
        yy3.pb(x);

        if (fabs(x - 1.0) <= EPS && u == v)
            absorbing[u] = true, absorbing_cnt++;
    }

    nonabsorbing_cnt = n - absorbing_cnt;
    vector<int> position (n);
    int u = 0, v = 0;
    for (int i = 0; i < n; i++)
    {
        if (absorbing[i])
            position[i] = u++;
        else
            position[i] = v++;
    }

    for (int i = 0; i < m; i++)
    {
        if (absorbing[yy2[i]] && !absorbing[yy1[i]])
            R[position[yy1[i]]][position[yy2[i]]] = yy3[i];
        else
            if (!absorbing[yy2[i]])
                Q[position[yy1[i]]][position[yy2[i]]] = yy3[i];
    }

    for (int i = 0; i < nonabsorbing_cnt; i++)
    {
        E[i][i] = 1.0;
        N[i][i] = 1.0;
        for (int j = 0; j < nonabsorbing_cnt; j++)
            E[i][j] -= Q[i][j];
    }

    // gauss
    for (int i = 0; i < nonabsorbing_cnt; i++)
    {
        if (fabs(E[i][i] - 1) > EPS)
        {
            double mul = E[i][i];
            for (int j = 0; j < nonabsorbing_cnt; j++)
            {
                E[i][j] /= mul;
                N[i][j] /= mul;
            } 
        }
        for (int j = 0; j < nonabsorbing_cnt; j++)
        {
            if (i != j)
            {
                double mul = E[j][i];
                for (int k = 0; k < nonabsorbing_cnt; k++)
                {
                    E[j][k] -= mul * E[i][k];
                    N[j][k] -= mul * N[i][k];
                }
            }
        }
    }

    for (int i = 0; i < nonabsorbing_cnt; i++)
        for (int j = 0; j < absorbing_cnt; j++)
            for (int k = 0; k < nonabsorbing_cnt; k++)
                G[i][j] += N[i][k] * R[k][j];

    for (int i = 0; i < n; i++)
    {
        double probability = 0.0;
        if (absorbing[i])
        {
            for (int j = 0; j < nonabsorbing_cnt; j++)
                probability += G[j][position[i]];
            probability += 1.0;
            probability /= (n + .0);
        }
        printf("%.20lf\n", probability);
    }
    return 0;
}