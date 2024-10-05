#include<bits/stdc++.h>
using ll = long long;
constexpr ll mod = 998244353;
constexpr int lim2 = 44, lim3 = 28, B = 13;
ll x, y, z;
int w[lim3];
ll pwx[lim3], pwy[lim2], pw3[lim3 + 1];
ll S[lim3];
std::vector<ll> f[B][2];
std::vector<bool> vis[B][2];
ll calc(int a, int to, ll s, int lim) {
   if (a == -1)
      return ! to;
   if (a < B && ! lim && vis[a][to][s])
      return f[a][to][s];
   ll ans = 0, val = 1, nxt = a ? S[a - 1] : 1;
   for (int i = 0; i <= (lim ? w[a] : 2); i++) {
      int lim_ = lim & (i == w[a]);
      if (i) (val *= pwx[a] * z % mod) %= mod;
      ll sum = 0;
      for (int j : {0, 1})  {
         ll t = s + pw3[a] * i + j * nxt;
         if ((t >= S[a]) == to) {
            t >= S[a] && (t -= S[a]);
            ll t_ = t & (nxt - 1);
            sum += calc(a - 1, j, t_, lim_) * pwy[__builtin_popcountll(t ^ t_)];
         }
      }
      ans += sum % mod * val;
   }
   ans %= mod;
   if (a < B && ! lim)
      f[a][to][s] = ans, vis[a][to][s] = true;
   return ans;
}
int main() {
   freopen("power.in", "r", stdin);
   freopen("power.out", "w", stdout);
   ll n; scanf("%lld", &n);
   for (int i = 0; i < lim3; i++)
      w[i] = n % 3, n /= 3;
   scanf("%lld%lld%lld", &x, &y, &z);
   pwx[0] = x;
   for (int i = 1; i < lim3; i++)
      pwx[i] = pwx[i - 1] * pwx[i - 1] % mod * pwx[i - 1] % mod;
   pwy[0] = 1;
   for (int i = 1; i < lim2; i++)
      pwy[i] = pwy[i - 1] * y % mod;
   for (int i = pw3[0] = 1; i <= lim3; i++)
      pw3[i] = pw3[i - 1] * 3;
   for (int i = 0; i < lim3; i++)
      for (S[i] = 1; S[i] < pw3[i + 1]; S[i] <<= 1);
   for (int i = 0; i < B; i++)
      for (int j : {0, 1})
            f[i][j].resize(S[i]), vis[i][j].resize(S[i]);
   printf("%lld\n", (mod + calc(lim3 - 1, 0, 0, 1) - 1) % mod);
   return 0;
}
