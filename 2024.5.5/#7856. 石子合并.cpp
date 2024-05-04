#include <bits/stdc++.h>
#define pb emplace_back
#define fst first
#define scd second
#define mkp make_pair
#define mems(a, x) memset((a), (x), sizeof(a))

using namespace std;
typedef long long ll;
typedef double db;
typedef unsigned long long ull;
typedef long double ldb;
typedef pair<ll, ll> pii;

const int maxn = 410;

int n, L, R, a[maxn], b[maxn], f[maxn][maxn], g[maxn][maxn];

inline void upd(int &x, int y) {
	x = (x < y ? x : y);
}

void solve() {
	scanf("%d%d%d", &n, &L, &R);
	L = max(L, 2);
	R = min(R, n);
	mems(f, 0x3f);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
		f[i][i] = 0;
		b[i] = b[i - 1] + a[i];
	}
	for (int i = n - 1; i; --i) {
		mems(g, 0x3f);
		g[1][i] = 0;
		for (int j = i + 1; j <= n; ++j) {
			for (int l = min(R, j - i + 1); l >= 2; --l) {
				int t = i + l - 2, &o = g[l][j], *F = f[j] + j + 1, *G = g[l - 1] + j, k = j - 1;
				while (k - 8 >= t) {
					upd(o, *(--G) + *(--F));
					upd(o, *(--G) + *(--F));
					upd(o, *(--G) + *(--F));
					upd(o, *(--G) + *(--F));
					upd(o, *(--G) + *(--F));
					upd(o, *(--G) + *(--F));
					upd(o, *(--G) + *(--F));
					upd(o, *(--G) + *(--F));
					k -= 8;
				}
				while (k >= t) {
					upd(o, *(--G) + *(--F));
					--k;
				}
			}
			int t = min(R, j - i + 1);
			for (int k = L; k <= t; ++k) {
				upd(f[j][i], g[k][j] + b[j] - b[i - 1]);
			}
			g[1][j] = f[j][i];
		}
	}
	printf("%d\n", f[n][1] > 1e9 ? -1 : f[n][1]);
}

int main() {
	int T = 1;
	// scanf("%d", &T);
	while (T--) {
		solve();
	}
	return 0;
}
