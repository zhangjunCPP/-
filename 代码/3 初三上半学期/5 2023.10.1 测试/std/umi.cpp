
#include<bits/stdc++.h>
#define LL long long
#define DB double
#define MOD 998244353
#define ls(x) x << 1
#define rs(x) x << 1 | 1
#define lowbit(x) x & (-x)
#define PII pair<int, int>
#define MP make_pair
#define VI vector<int>
#define VII vector<int>::iterator
#define all(x) x.begin(), x.end()
#define EB emplace_back
#define SI set<int>
#define SII set<int>::iterator
#define QI queue<int>
using namespace std;
template<typename T> void chkmn(T &a, const T &b) { (a > b) && (a = b); }
template<typename T> void chkmx(T &a, const T &b) { (a < b) && (a = b); }
int inc(const int &a, const int &b) { return a + b >= MOD ? a + b - MOD : a + b; }
int dec(const int &a, const int &b) { return a - b < 0 ? a - b + MOD : a - b; }
int mul(const int &a, const int &b) { return 1LL * a * b % MOD; }
int sqr(const int &a) { return 1LL * a * a % MOD; }
void Inc(int &a, const int &b) { ((a += b) >= MOD) && (a -= MOD); }
void Dec(int &a, const int &b) { ((a -= b) < 0) && (a += MOD); }
void Mul(int &a, const int &b) { a = 1LL * a * b % MOD; }
void Sqr(int &a) { a = 1LL * a * a % MOD; }
int qwqmi(int x, int k = MOD - 2)
{
    int res = 1;
    while(k)
    {
        if(k & 1) Mul(res, x);
        Sqr(x), k >>= 1;
    }
    return res;
}
const int N = 1e5 + 5;
const int M = 1e6 + 5;
const int F = 21;
int fac[M], facinv[M];
void preprocess()
{
    fac[0] = facinv[0] = 1;
    for(int i = 1; i < M; ++i)
        fac[i] = mul(fac[i - 1], i);
    facinv[M - 1] = qwqmi(fac[M - 1]);
    for(int i = M - 2; i >= 1; --i)
        facinv[i] = mul(facinv[i + 1], i + 1);
}
int C(int n, int m)
{
    if(n < m) return 0;
    return mul(fac[n], mul(facinv[m], facinv[n - m]));
}
int calc(int x)
{
    return dec(C(2 * x, x), C(2 * x, x + 1));
}
int n, m, id, Q, s[N];
vector<int> G[N];
int f[N][F], depth[N];
void predfs(int u, int fa)
{
    // cerr << u << " " << fa << endl;
    f[u][0] = fa;
    depth[u] = depth[fa] + 1;
    for(int i = 1; i < F; ++i)
        f[u][i] = f[f[u][i - 1]][i - 1];
    for(auto v : G[u])
    {
        if(v == fa)
            continue;
        predfs(v, u);
    }
}
int LCA(int x, int y)
{
    if(depth[x] < depth[y])
        swap(x, y);
    for(int i = F - 1; i >= 0; --i)
        if(depth[f[x][i]] >= depth[y])
            x = f[x][i];
    if(x == y) return x;
    for(int i = F - 1; i >= 0; --i)
        if(f[x][i] ^ f[y][i])
            x = f[x][i], y = f[y][i];
    return f[x][0];
}
namespace solve1
{
    int w[15], d;
    int vis[25], cnt, a[15], b[15];
    int ans = 0;
    void search(int lst)
    {
        if(2 * d - lst + 1 < d - cnt) return;
        if(cnt == d)
        {
            int acnt = 0, bcnt = 0;
            for(int i = 1; i <= 2 * d; ++i)
            {
                if(vis[i]) a[++acnt] = i;
                else b[++bcnt] = i;
            }
            bool flag = 1;
            for(int i = 1; i <= d; ++i)
            {
                if(w[i] == 0) flag &= (a[i] < b[i]);
                else flag &= (a[i] > b[i]);
            }
            if(flag) ++ans;
            return;
        }
        for(int i = lst + 1; i <= 2 * d; ++i)
        {
            ++cnt;
            vis[i] = 1;
            search(i);
            vis[i] = 0;
            --cnt;
        }
    }
    void work()
    {
        while(Q--)
        {
            int x, y;
            scanf("%d %d", &x, &y);
            int lca = LCA(x, y);
            d = depth[x] + depth[y] - 2 * depth[lca] + 1;
            int l = 0, r = d;
            w[++l] = s[x];
            while(x != lca)
            {
                x = f[x][0];
                w[++l] = s[x];
            }
            while(y != lca)
            {
                w[r--] = s[y];
                y = f[y][0];
            }
            cnt = ans = 0;
            search(0);
            Mul(ans, C(m, 2 * d));
            printf("%d\n", ans);
        }
    }
};
namespace solve2
{
    void work()
    {
        while(Q--)
        {
            int x, y;
            scanf("%d %d", &x, &y);
            int lca = LCA(x, y);
            int d = depth[x] + depth[y] - 2 * depth[lca] + 1;
            printf("%d\n", mul(calc(d), C(m, 2 * d)));
        }
    }
};
namespace solve3
{
    int w[N];
    void work()
    {
        while(Q--)
        {
            int x, y;
            scanf("%d %d", &x, &y);
            int lca = LCA(x, y);
            int d = depth[x] + depth[y] - 2 * depth[lca] + 1;
            int l = 0, r = d;
            w[++l] = s[x];
            while(x != lca)
            {
                x = f[x][0];
                w[++l] = s[x];
            }
            while(y != lca)
            {
                w[r--] = s[y];
                y = f[y][0];
            }
            int cnt = 1, ans = 1;
            for(int i = 2; i <= d; ++i)
            {
                if(w[i] == w[i - 1]) ++cnt;
                else Mul(ans, calc(cnt)), cnt = 1;
            }
            Mul(ans, calc(cnt));
            Mul(ans, C(m, 2 * d));
            printf("%d\n", ans);
        }
    }
};
namespace solve
{
    int prod[N];
    int g[N][F];
    void dfs(int u, int top)
    {
        g[u][0] = f[top][0];
        for(int i = 1; i < F; ++i)
            g[u][i] = g[g[u][i - 1]][i - 1];
        for(auto v : G[u])
        {
            if(v == f[u][0])
                continue;
            if(s[u] == s[v])
            {
                prod[v] = mul(prod[top], calc(depth[v] - depth[top] + 1));
                dfs(v, top);
            }
            else
            {
                prod[v] = prod[u];
                dfs(v, v);
            }
        }
    }
    void work()
    {
        prod[0] = prod[1] = 1;
        dfs(1, 1);
        while(Q--)
        {
            int x, y;
            scanf("%d %d", &x, &y);
            int lca = LCA(x, y);
            int d = depth[x] + depth[y] - 2 * depth[lca] + 1;
            int _x = x, _y = y;
            for(int i = F - 1; i >= 0; --i)
                if(depth[g[_x][i]] >= depth[lca])
                    _x = g[_x][i];
            for(int i = F - 1; i >= 0; --i)
                if(depth[g[_y][i]] >= depth[lca])
                    _y = g[_y][i];
            int ans = mul(prod[x], prod[y]);
            Mul(ans, qwqmi(mul(prod[_x], prod[_y])));
            Mul(ans, calc(depth[_x] + depth[_y] - 2 * depth[lca] + 1));
            Mul(ans, C(m, 2 * d));
            printf("%d\n", ans);
        }
    }
};



int main()
{
    freopen("umi.in","r",stdin);
    freopen("umi.out","w",stdout);
    preprocess();
    scanf("%d %d %d", &n, &m, &id);
    for(int i = 1; i <= n; ++i)
        scanf("%d", &s[i]);
    for(int i = 1; i < n; ++i)
    {
        int x, y;
        scanf("%d %d", &x, &y);
        G[x].EB(y), G[y].EB(x);
    }
    predfs(1, 0);
    scanf("%d", &Q);
    solve::work();
    return 0;
}
