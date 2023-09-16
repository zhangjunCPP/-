#include<bits/stdc++.h>

using namespace std;

int main() {
    freopen("balance.in", "r", stdin);
    freopen("balance.out", "w", stdout);
    int n;
    cin >> n;
    vector<vector<int>> vec(n + 1);
    for (int i = 1, u, v; i < n; i++) {
        cin >> u >> v;
        vec[u].push_back(v);
        vec[v].push_back(u);
    }

    vector<vector<int>> nxt(19, vector<int>(n + 1));
    auto update = [&nxt](int u, int v) {
        nxt[0][u] = v;
        for (int i = 1; i <= 18; i++) nxt[i][u] = nxt[i - 1][nxt[i - 1][u]];
    };

    vector<int> sz(n + 1);
    function<void(int, int)> dfs = [&dfs, &vec, &sz, &update](int u, int f) {
        sz[u] = 1;
        int w = 0;
        for (int v: vec[u]) {
            if (v == f) continue;
            dfs(v, u);
            sz[u] += sz[v];
            if (sz[v] > sz[w]) w = v;
        }
        update(u, w);
    };
    dfs(1, 0);

    auto calc = [&nxt, &sz](int u) {
        int v = u;
        for (int i = 18; i >= 0; i--)
            if (sz[nxt[i][v]] * 2 >= sz[u]) v = nxt[i][v];
        return v;
    };

    vector<int> Ans(n + 1);
    function<void(int, int)> dfs2 = [&dfs2, &vec, &sz, &Ans, &update, &nxt, &calc](int u, int f) {
//        cerr << u << ' ' << f << endl;
        int w = 0, x = 0;
        for (int v: vec[u]) {
            if (sz[v] > sz[w]) x = w, w = v;
            else if (sz[v] > sz[x]) x = v;
        }
        int tmp = nxt[0][u];
        update(u, w);
        Ans[u] = calc(w);

        for (int v: vec[u]) {
            if (v == f || v == w) continue;
            sz[u] -= sz[v];
            sz[v] += sz[u];
            dfs2(v, u);
            sz[v] -= sz[u];
            sz[u] += sz[v];
        }
        if (w && w != f) {
            update(u, x);
            sz[u] -= sz[w];
            sz[w] += sz[u];
            dfs2(w, u);
            sz[w] -= sz[u];
            sz[u] += sz[w];
        }
        update(u, tmp);
    };
    dfs2(1, 0);
    for (int i = 1; i <= n; i++) cout << Ans[i] << '\n';
    return 0;
}