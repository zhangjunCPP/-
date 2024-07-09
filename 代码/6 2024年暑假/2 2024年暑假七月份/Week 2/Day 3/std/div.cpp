#include <bits/stdc++.h>

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;

void solve() {
    int n, m;
    std::cin >> n >> m;
    std::map<int, int> f;
    std::set<std::pair<int, int>> g;
    std::vector<std::pair<int, int>> his;
    
    auto add = [&](int a, int c, bool rec) {
        int &x = f[a];
        g.erase({x, a});
        x += c;
        g.emplace(x, a);
        if (rec) {
            his.emplace_back(a, c);
        }
    };
    
    auto rollback = [&]() {
        for (auto [a, c] : his) {
            add(a, -c, false);
        }
        his.clear();
    };
    
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        int c, a;
        std::cin >> c >> a;
        add((a + 1) % m, c, false);
        add(a % m, -c, false);
        sum += c;
    }
    int ans = 0;
    if (sum % m == 0) {
        ans += 1;
    }
    int lim = 0;
    for (auto [a, b] : f) {
        lim = std::max(lim, std::abs(b));
    }
    if (lim == 0) {
        std::cout << "-1\n";
        return;
    }
    ++lim;
    
    for (int x = 2; x <= lim; ++x) {
        while (g.begin()->first <= -x) {
            auto [c, a] = *g.begin();
            add(a, x, true);
            add((a + 1) % m, -1, true);
        }
        while (g.rbegin()->first >= x) {
            auto [c, a] = *g.rbegin();
            add(a, -x, true);
            add((a + 1) % m, 1, true);
        }
        int a = g.begin()->first, b = g.rbegin()->first;
        if (a == b && (a == x - 1 || a == 0 || a == -x + 1)) {
            ++ans;
        }
        rollback();
    }
    
    std::cout << ans << "\n";
}

int main() {
    std::freopen("div.in", "r", stdin);
    std::freopen("div.out", "w", stdout);
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    
    return 0;
}