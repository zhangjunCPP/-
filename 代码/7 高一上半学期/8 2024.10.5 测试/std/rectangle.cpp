// #pragma GCC optimize("Ofast,no-stack-protector,unroll-loops")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,popcnt,abm,mmx,avx,avx2,fma")
// MagicDark
#include <bits/stdc++.h>
#define debug cerr << "[" << __LINE__ << "] "
#define SZ(x) (int) x.size() - 1
#define all(x) x.begin(), x.end()
#define ms(x, y) memset(x, y, sizeof x)
#define F(i, x, y) for (int i = (x); i <= (y); i++)
#define DF(i, x, y) for (int i = (x); i >= (y); i--)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
template <typename T> inline void chkmax(T& x, T y) {x = max(x, y);}
template <typename T> inline void chkmin(T& x, T y) {x = min(x, y);}
template <typename T> inline void read(T &x) {
	x = 0; int f = 1; char c = getchar();
	for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
	for (; isdigit(c); c = getchar()) x = (x << 1) + (x << 3) + (c ^ 48);
	x *= f;
}
const int N = 4e5 + 10;
int n, tx[N], ty[N];
struct Rec {
	int l, r, u, d;
} a[N];
bool operator < (Rec x, Rec y) {
	return x.r < y.r;
}
struct BIT {//区间加，单点查
	ll t[N];
	void clear() {
		ms(t, 0);
	}
	void add(int x, ll y) {
		for (; x <= 2 * n; x += x & -x) t[x] += y;
	}
	void add(int l, int r, ll x) {
		add(l, x), add(r + 1, -x);
	}
	ll query(int x) {
		ll s = 0;
		for (; x; x -= x & -x) s += t[x];
		return s;
	}
};
struct BBIT {//区间加，区间求和
	BIT k, b;
	void clear() {
		k.clear(), b.clear();
	}
	void add(int l, int r, ll x) {
		k.add(l, r, x);
		b.add(l, r, x * (- l + 1));
		b.add(r + 1, 2 * n, x * (r - l + 1));
	}
	ll query(int x) {
		return k.query(x) * x + b.query(x);
	}
	ll query(int l, int r) {
		return query(r) - query(l - 1);
	}
} A, B;
int id[N], deg[N];
ll ans;
struct Com {
	ll t[4];
	Com() {
		ms(t, 0);
	}
	void add(int x) {
		DF(i, 3, 1)
			F(j, 1, i)
				t[i] += (ll) t[i - j] * (j == 1 ? x : (j == 2 ? (ll) x * (x - 1) / 2 : (ll) x * (x - 1) * (x - 2) / 6));
	}
};
Com operator + (Com x, Com y) {
	Com z;
	F(i, 0, 3) z.t[i] = x.t[i] + y.t[i];
	return z;
}
struct Seg {
	#define mid ((l + r) >> 1)
	#define ls num << 1
	#define rs ls | 1
	#define li ls, l, mid
	#define ri rs, mid + 1, r
	int tag[N << 2];
	Com info[N << 2];
	void down(int num, int x) {
		tag[num] += x;
		info[num].add(x);
	}
	void pushdown(int num) {
		if (tag[num]) down(ls, tag[num]), down(rs, tag[num]), tag[num] = 0;
	}
	void pushup(int num) {
		info[num] = info[ls] + info[rs];
	}
	void change(int num, int l, int r, int L, int R, int x) {
		if (L <= l && r <= R) return down(num, x);
		pushdown(num);
		if (mid >= L) change(li, L, R, x);
		if (mid < R) change(ri, L, R, x);
		pushup(num);
	}
	void add(int l, int r, int x) {
		change(1, 1, 2 * n, l, r, x);
	}
	ll query() {
		return info[1].t[3];
	}
	void build(int num, int l, int r) {
		info[num].t[0] = r - l + 1;
		if (l == r) return;
		build(li), build(ri);
	}
	void build() {
		build(1, 1, 2 * n);
	}
};
struct DS {
	Seg A, B;
	void add(int l, int r, int x) {
		A.add(l, r, x);
		B.add(l, r - 1, x);
	}
	void build() {
		A.build(), B.build();
	}
	ll query() {
		return A.query() - B.query();
	}
} C, D;
signed main() {
	freopen("rectangle.in", "r", stdin);
	freopen("rectangle.out", "w", stdout);
	read(n);
	F(i, 1, n) {
		read(a[i].l), read(a[i].r), read(a[i].u), read(a[i].d);
		tx[i * 2 - 1] = a[i].l;
		tx[i * 2] = a[i].r;
		ty[i * 2 - 1] = a[i].u;
		ty[i * 2] = a[i].d;
	}
	sort(a + 1, a + n + 1);
	sort(tx + 1, tx + 2 * n + 1);
	sort(ty + 1, ty + 2 * n + 1);
	F(i, 1, n) {
		id[a[i].l = lower_bound(tx + 1, tx + 2 * n + 1, a[i].l) - tx] = i << 1;
		id[a[i].r = lower_bound(tx + 1, tx + 2 * n + 1, a[i].r) - tx] = i << 1 | 1;
		a[i].u = lower_bound(ty + 1, ty + 2 * n + 1, a[i].u) - ty;
		a[i].d = lower_bound(ty + 1, ty + 2 * n + 1, a[i].d) - ty;
	}
	F(i, 1, 2 * n)
		if (id[i] & 1) {
			deg[id[i] >> 1] += A.query(a[id[i] >> 1].u, a[id[i] >> 1].d) - B.query(a[id[i] >> 1].u, a[id[i] >> 1].d - 1);
			A.add(a[id[i] >> 1].u, a[id[i] >> 1].d, 1);
			B.add(a[id[i] >> 1].u, a[id[i] >> 1].d - 1, 1);
		} else {
			deg[id[i] >> 1] -= A.query(a[id[i] >> 1].u, a[id[i] >> 1].d) - B.query(a[id[i] >> 1].u, a[id[i] >> 1].d - 1);
		}
	A.clear(), B.clear();
	DF(i, 2 * n, 1)
		if (id[i] & 1) {
			deg[id[i] >> 1] += A.query(a[id[i] >> 1].u, a[id[i] >> 1].d) - B.query(a[id[i] >> 1].u, a[id[i] >> 1].d - 1);
			A.add(a[id[i] >> 1].u, a[id[i] >> 1].d, 1);
			B.add(a[id[i] >> 1].u, a[id[i] >> 1].d - 1, 1);
		} else {
			A.add(a[id[i] >> 1].u, a[id[i] >> 1].d, -1);
			B.add(a[id[i] >> 1].u, a[id[i] >> 1].d - 1, -1);
		}
	auto doit = [&] (DS &x, int y, int z) {
		x.add(a[id[y] >> 1].u, a[id[y] >> 1].d, z);
	};
	C.build(), D.build();
	F(i, 1, 2 * n) {
		if (!(id[i] & 1)) { //左端点
			doit(C, i, 1);
			doit(D, i, 1);
		}
		if (id[i] & 1) doit(C, i, -1);
		if (id[i + 1] & 1) doit(D, i + 1, -1);
		ans -= C.query() - D.query();
	}
	ans += (ll) n * (n - 1) * (n - 2) / 6;
	ll s = 0;
	F(i, 1, n) s += (ll) deg[i] * (n - deg[i] - 1);
	ans -= s / 2;
	cout << ans;
	return 0;
}
/* why?
*/