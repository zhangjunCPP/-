#include<bits/stdc++.h>
using ll = long long;
constexpr ll mod = 998244353;
const int N = 5e3, maxn = 5e3 + 10;
ll binom[maxn][maxn], pw[maxn][maxn];
inline void Main() {
   int n, X; scanf("%d%d", &n, &X);
   ll ans = 0;
   for (int v = 2; v <= X; v++)
      for (int c0 = 0; c0 <= n; c0++) {
         int c1 = n - c0;
         (ans += binom[n][c0] * pw[v - 1][c0] % mod * pw[X - v + 1][c1] % mod * std::min(c0 - (n % 2 && c0 > n / 2), c1 - (n % 2 && c1 > n / 2))) %= mod;
      }
   printf("%lld\n", (ans << 1) % mod);
}
int main() {
   freopen("beauty.in", "r", stdin);
   freopen("beauty.out", "w", stdout);
   for (int v = 0; v <= N; v++)
      for (int i = pw[v][0] = 1; i <= N; i++)
         pw[v][i] = pw[v][i - 1] * v % mod;
   for (int i = 0; i <= N; i++)
      for (int j = binom[i][0] = 1; j <= i; j++)
         binom[i][j] = (binom[i - 1][j - 1] + binom[i - 1][j]) % mod;
   int T; scanf("%d", &T);
   while (T--) Main();
   return 0;
}