#include<bits/stdc++.h>
using ll = long long;
inline ll C3(int n) {return 1ll * n * (n - 1) * (n - 2) / 6;}
inline ll C2(int n) {return 1ll * n * (n - 1) / 2;}
const int maxn = 1e5 + 10;
int n;
int tr[maxn];
inline void add(int x, int y) {
   for (int i = x; i <= n; i += i & -i) tr[i] += y;
}
inline int qry(int x, int y = 0) {
   for (int i = x; i; i -= i & -i) y += tr[i];
   return y;
}
int a[maxn], b[maxn], c[maxn];
int p[maxn];
int cntab[maxn], cntac[maxn], cntbc[maxn], cntabc[maxn];
void cdq(int l, int r) {
   if (l == r)
      return ;
   int mid = (l + r) >> 1;
   cdq(l, mid), cdq(mid + 1, r);
   int i = mid + 1, j = l;
   while (i <= r) {
      while (j <= mid && b[p[j]] < b[p[i]])
         add(c[p[j]], 1), j++;
      cntabc[p[i]] += qry(c[p[i]]), i++;
   }
   while ((--j) >= l)
      add(c[p[j]], -1);
   std::inplace_merge(p + l, p + mid + 1, p + r + 1, [&](int x, int y) {return b[x] < b[y];});
}
inline void solve() {
   scanf("%d", &n);
   for (int i = 1; i <= n; i++)
      scanf("%d%d%d", &a[i], &b[i], &c[i]);
   std::iota(p + 1, p + n + 1, 1);
   std::sort(p + 1, p + n + 1, [&](int x, int y) {return a[x] < a[y];});
   memset(tr, 0, sizeof(tr));
   memset(cntabc, 0, sizeof(cntabc)); 
   cdq(1, n);
   for (int i = 1; i <= n; i++) {
      cntab[p[i]] = qry(a[p[i]]);
      add(a[p[i]], 1);
   }
   memset(tr, 0, sizeof(tr));
   for (int i = 1; i <= n; i++) {
      cntbc[p[i]] = qry(c[p[i]]);
      add(c[p[i]], 1);
   }
   std::sort(p + 1, p + n + 1, [&](int x, int y) {return a[x] < a[y];});
   memset(tr, 0, sizeof(tr));
   for (int i = 1; i <= n; i++) {
      cntac[p[i]] = qry(c[p[i]]);
      add(c[p[i]], 1);
   }
   ll sum = n + C2(n) + C3(n);
   for (int i = 1; i <= n; i++)
      sum -= cntabc[i], sum -= C2(cntab[i]) + C2(cntbc[i]) + C2(cntac[i]), sum += 2ll * C2(cntabc[i]);
   printf("%lld\n", sum);
}
int main() {
   freopen("max.in", "r", stdin);
   freopen("max.out", "w", stdout);
   int T; scanf("%d", &T);
   while (T--) solve();
   return 0;
}
