#include <bits/stdc++.h>
using namespace std;

typedef __uint128_t ll;

ll read() {
    ll x = 0; char ch = getchar();
    while (!isdigit(ch)) ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
    return x;
}

void print(ll x) {
    if (x > 9) print(x / 10);
    putchar(x % 10 + '0');
}

const int maxn = 125;
int T, n, m, K, mask[maxn];
ll a[maxn];

int main() {
	freopen("puzzle.in","r",stdin);
	freopen("puzzle.out","w",stdout); 
    n = read(), m = read(), K = read();
    for (int i = 0; i < n; i++) {
        a[i] = read();
    }
    ll ans = 0;
    function<void(int, int, ll)> dfs = [&](int cur, int w, ll s) {
        if (s + n * (((ll)1 << (cur + 1)) - 1) <= ans) return;
        if (!~cur) { ans = max(ans, s); return; }
        int mx = 0;
        for (int S = 0; S < 1 << w; S++) {
            int cnt = 0;
            for (int i = 0; i < n; i++) {
                if ((a[i] >> cur & 1) ^ __builtin_parity(S & mask[i])) cnt++;
            }
            mx = max(mx, cnt);
        }
        if (mx < n && w < K) {
            for (int i = 0; i < n; i++) {
                if (!(a[i] >> cur & 1)) mask[i] ^= 1 << w;
            }
            dfs(cur - 1, w + 1, s + n * ((ll)1 << cur));
            for (int i = 0; i < n; i++) {
                if (!(a[i] >> cur & 1)) mask[i] ^= 1 << w;
            }
        }
        dfs(cur - 1, w, s + mx * ((ll)1 << cur));
    };
    dfs(m - 1, 0, 0);
    print(ans), putchar('\n');
    return 0;
}
