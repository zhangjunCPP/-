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

const int maxn = 300100;
const int logn = 21;
const ll mod = 998244353;
const ll inv2 = (mod + 1) / 2, inv3 = (mod + 1) / 3;

ll n, m, p[9], inv[maxn];
char s[maxn];

struct node {
	ll a[3];
	node() {
		mems(a, 0);
	}
} f[maxn][logn], g[maxn][logn];

inline node operator + (const node &a, const node &b) {
	node res;
	res.a[0] = (a.a[0] + b.a[0]) % mod;
	res.a[1] = (a.a[1] + b.a[1]) % mod;
	res.a[2] = (a.a[2] + b.a[2]) % mod;
	return res;
}

inline node operator * (const node &a, const node &b) {
	node res;
	res.a[0] = (res.a[0] + (a.a[0] * b.a[0] + a.a[0] * b.a[0]) % mod * p[0]) % mod;
	res.a[0] = (res.a[0] + (a.a[0] * b.a[1] + a.a[1] * b.a[0]) % mod * p[1]) % mod;
	res.a[0] = (res.a[0] + (a.a[0] * b.a[2] + a.a[2] * b.a[0]) % mod * p[2]) % mod;
	res.a[1] = (res.a[1] + (a.a[1] * b.a[0] + a.a[0] * b.a[1]) % mod * p[2]) % mod;
	res.a[1] = (res.a[1] + (a.a[1] * b.a[1] + a.a[1] * b.a[1]) % mod * p[0]) % mod;
	res.a[1] = (res.a[1] + (a.a[1] * b.a[2] + a.a[2] * b.a[1]) % mod * p[1]) % mod;
	res.a[2] = (res.a[2] + (a.a[2] * b.a[0] + a.a[0] * b.a[2]) % mod * p[1]) % mod;
	res.a[2] = (res.a[2] + (a.a[2] * b.a[1] + a.a[1] * b.a[2]) % mod * p[2]) % mod;
	res.a[2] = (res.a[2] + (a.a[2] * b.a[2] + a.a[2] * b.a[2]) % mod * p[0]) % mod;
	return res;
}

node query(int k, int l, int r, int ql, int qr) {
	if (ql <= l && r <= qr) {
		return g[l][k];
	}
	int mid = (l + r) >> 1;
	node res;
	if (ql < mid) {
		res = res + query(k - 1, l, mid - 1, ql, qr) * f[mid][k - 1];
	}
	if (qr > mid) {
		res = res + query(k - 1, mid + 1, r, ql, qr) * f[l][k - 1];	
	}
	return res;
}

void solve() {
	p[0] = inv2;
	p[1] = inv3;
	p[2] = inv3 * 2 % mod;
	scanf("%lld%lld%s", &n, &m, s + 1);
	inv[1] = 1;
	for (int i = 2; i <= n; ++i) {
		inv[i] = (mod - mod / i) * inv[mod % i] % mod;
	}
	for (int i = 1; i <= n; ++i) {
		int x = (s[i] == 'R' ? 0 : (s[i] == 'P' ? 1 : 2));
		f[i][0].a[x] = g[i][1].a[x] = 1;
	}
	for (int j = 1; (1 << j) <= n; ++j) {
		for (int i = 1; i + (1 << j) - 1 <= n; ++i) {
			f[i][j] = f[i][j - 1] * f[i + (1 << (j - 1))][j - 1];
		}
	}
	for (int j = 2; (1 << j) - 1 <= n; ++j) {
		for (int i = 1; i + (1 << j) - 2 <= n; ++i) {
			g[i][j] = g[i][j - 1] * f[i + (1 << (j - 1)) - 1][j - 1] + f[i][j - 1] * g[i + (1 << (j - 1))][j - 1];
		}
	}
	while (m--) {
		int l, r, ql, qr;
		scanf("%d%d%d%d", &l, &r, &ql, &qr);
		int t = (qr - l + 2) / 2 - (ql - l + 1) / 2, k = __lg(r - l + 1) + 1;
		printf("%lld\n", query(k, l, r, ql, qr).a[0] * inv[t] % mod);
	}
}

int main() {
	int T = 1;
	// scanf("%d", &T);
	while (T--) {
		solve();
	}
	return 0;
}
