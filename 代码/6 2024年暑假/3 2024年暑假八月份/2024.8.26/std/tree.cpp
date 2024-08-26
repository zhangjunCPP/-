#ifdef LOCAL
#include "stdafx.h"
#else
#include <bits/stdc++.h>
#define IL inline
#define LL long long
#define eb emplace_back
#define sz(v) ((int) (v).size())
#define L(i, j, k) for (int i = (j); i <= (k); ++i)
#define R(i, j, k) for (int i = (j); i >= (k); --i)
#define FIO(FILE) freopen(FILE".in", "r", stdin), freopen(FILE".out", "w", stdout)
using namespace std;

using vi = vector<int>;
#endif

constexpr int N = 1e6 + 9;
constexpr int P = 1e9 + 7;
int n, a[N], b[N], c[N], o[N], pb[N], ch[N][2], d[N], sz[N], p[N];

IL int qpow (int b, int k = P - 2) {
	int r = 1;
	for (; k; k >>= 1, b = (LL)b * b % P) if (k & 1) r = (LL)r * b % P;
	return r;
}

IL int bld (int i, int l, int L, int q) {
	int u = a[l];
	d[u] = q;
	sz[u] = 1;
	if (i > 1) {
		int R = L + i - 1;
		if (a[l + 1] == b[R - 1]) {
			int x = bld(i - 1, l + 1, L, q + 1);
			ch[u][0] = x;
			sz[u] += sz[x];
			p[x] = u;
		} else {
			int z = pb[a[l + 1]];
			int x = bld(z - L + 1, l + 1, L, q + 1);
			int y = bld(R - 1 - z, l + z - L + 2, z + 1, q + 1);
			ch[u][0] = x;
			ch[u][1] = y;
			sz[u] += sz[x] + sz[y];
			p[x] = p[y] = u;
		}
	}
	return u;
}

int ans = 1, all;

int m[N];

IL void dfsl (int u) {
	m[u] = c[u];
	if (!ch[u][0]) {
		return;
	}
	dfsl(ch[u][0]);
	m[u] = max(m[u], m[ch[u][0]]);
	if (!ch[u][1]) {
		all -= 1;
		if (m[ch[u][0]] == c[u]) {
			ans = 2 * ans % P;
		}
	} else {
		dfsl(ch[u][1]);
		m[u] = max(m[u], m[ch[u][1]]);
	}
}

IL void dfsr (int u) {
	if (!c[u]) {
		c[u] = n + 1;
	}
	m[u] = c[u];
	if (!ch[u][0]) {
		return;
	}
	dfsr(ch[u][0]);
	m[u] = min(m[u], m[ch[u][0]]);
	if (!ch[u][1]) {
		all -= 1;
		if (m[ch[u][0]] == c[u]) {
			ans = 2 * ans % P;
		}
	} else {
		dfsr(ch[u][1]);
		m[u] = min(m[u], m[ch[u][1]]);
	}
}

IL int pos (int x) {
	return x == ch[p[x]][1];
}

IL int C (int n, int m) {
	if (m > n / 2) {
		m = n - m;
	}
	int fc = 1;
	L (i, 1, m) {
		fc = (LL)fc * i % P;
	}
	fc = qpow(fc);
	R (i, n, n - m + 1) {
		fc = (LL)fc * i % P;
	}
	return fc;
}

int ns;

IL void calc (int x, int T) {
	int s = sz[ch[x][0]] + 1, cnt = 0;
	for (; p[x]; x = p[x]) {
		if (!ch[p[x]][1]) {
			cnt += 1;
		}
		if (pos(x)) {
			s += sz[ch[p[x]][0]] + 1;
		}
	}

	ns = (ns + (LL)ans * C(cnt, T - s) % P * qpow(2, all - cnt)) % P;
}

int main () {
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n;
	L (i, 1, n) {
		cin >> a[i];
	}
	L (i, 1, n) {
		cin >> b[i], pb[b[i]] = i;
	}
	L (i, 1, n) {
		cin >> o[i], c[o[i]] = i;
	}
	bld(n, 1, 1, 1);
	L (i, 1, n) {
		if (ch[i][0] && !ch[i][1]) {
			all += 1;
		}
	}
	if (*max_element(c + 1, c + n + 1) == 0) {
		cout << qpow(2, all) << '\n';
	} else {
		int rt = 0;
		L (i, 1, n) {
			if (c[i]) {
				if (!rt || d[i] < d[rt]) {
					rt = i;
				}
			}
		}
		int T = c[rt];
		if (ch[rt][1]) {
			dfsl(ch[rt][0]);
			dfsr(ch[rt][1]);

			calc(rt, T);
		} else {
			all -= 1;
			if (o[T - 1] || o[T + 1]) {
				if (o[T - 1]) {
					int x = o[T - 1];
					if (d[x] < d[rt]) {
						swap(ch[rt][1], ch[rt][0]);
					} else {
						while (p[x] != rt) {
							x = p[x];
						}
						if (pos(x)) {
							swap(ch[rt][1], ch[rt][0]);
						}
					}
				} else {
					int x = o[T + 1];
					if (d[x] > d[rt]) {
						while (p[x] != rt) {
							x = p[x];
						}
						if (!pos(x)) {
							swap(ch[rt][1], ch[rt][0]);
						}
					}
				}
				if (ch[rt][0]) {
					dfsl(ch[rt][0]);
				}
				if (ch[rt][1]) {
					dfsr(ch[rt][1]);
				}
				calc(rt, T);
			} else {
				calc(rt, T);
				swap(ch[rt][0], ch[rt][1]);
				calc(rt, T);
			}
		}
		cout << ns << '\n';
	}
}
// I love WHQ!