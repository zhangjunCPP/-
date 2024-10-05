#include<bits/stdc++.h>
const int maxn = 1e6 + 10;
char s[maxn];
int len[maxn], m;
inline void solve() {
   int n; scanf("%d%s", &n, s + 1);
   len[m = 1] = 1;
   for (int i = 1; i < n; i++) {
      if (s[i] == '0') len[++m] = 1;
      else len[m]++;
   }
   long long ans = 1ll * n * (n - 1) / 2;
   for (int i = 1; i <= m; i++)
      ans -= 1ll * len[i] * (len[i] - 1) / 2;
   printf("%lld\n", ans);
   for (int i = 1, val = n; i <= m; i++) {
      for (int j = 1; j <= len[i]; j++)
         printf("%d ", val - len[i] + j);
      val -= len[i];
   }
   puts("");
}
int main() {
   freopen("inv.in", "r", stdin);
   freopen("inv.out", "w", stdout);
   int T; scanf("%d", &T);
   while (T--)
      solve();
   return 0;
}