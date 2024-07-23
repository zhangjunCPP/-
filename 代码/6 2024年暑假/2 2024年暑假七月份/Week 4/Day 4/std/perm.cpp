#include <bits/stdc++.h>

using i64 = long long;

constexpr int P = 998244353;
using i64 = long long;
// assume -P <= x < 2P
int norm(int x) {
	if (x < 0) {
		x += P;
	}
	if (x >= P) {
		x -= P;
	}
	return x;
}
template<class T>
T power(T a, i64 b) {
	T res = 1;
	for (; b; b /= 2, a *= a) {
		if (b % 2) {
			res *= a;
		}
	}
	return res;
}
struct Z {
	int x;
	Z(int x = 0) : x(norm(x)) {}
	Z(i64 x) : x(norm(x % P)) {}
	int val() const {
		return x;
	}
	Z operator-() const {
		return Z(norm(P - x));
	}
	Z inv() const {
		assert(x != 0);
		return power(*this, P - 2);
	}
	Z &operator*=(const Z &rhs) {
		x = i64(x) * rhs.x % P;
		return *this;
	}
	Z &operator+=(const Z &rhs) {
		x = norm(x + rhs.x);
		return *this;
	}
	Z &operator-=(const Z &rhs) {
		x = norm(x - rhs.x);
		return *this;
	}
	Z &operator/=(const Z &rhs) {
		return *this *= rhs.inv();
	}
	friend Z operator*(const Z &lhs, const Z &rhs) {
		Z res = lhs;
		res *= rhs;
		return res;
	}
	friend Z operator+(const Z &lhs, const Z &rhs) {
		Z res = lhs;
		res += rhs;
		return res;
	}
	friend Z operator-(const Z &lhs, const Z &rhs) {
		Z res = lhs;
		res -= rhs;
		return res;
	}
	friend Z operator/(const Z &lhs, const Z &rhs) {
		Z res = lhs;
		res /= rhs;
		return res;
	}
	friend std::istream &operator>>(std::istream &is, Z &a) {
		i64 v;
		is >> v;
		a = Z(v);
		return is;
	}
	friend std::ostream &operator<<(std::ostream &os, const Z &a) {
		return os << a.val();
	}
};

struct Comb {
	int n;
	std::vector<Z> _fac;
	std::vector<Z> _invfac;
	std::vector<Z> _inv;

	Comb() : n{0}, _fac{1}, _invfac{1}, _inv{0} {}
	Comb(int n) : Comb() {
		init(n);
	}

	void init(int m) {
		if (m <= n) return;
		_fac.resize(m + 1);
		_invfac.resize(m + 1);
		_inv.resize(m + 1);

		for (int i = n + 1; i <= m; i++) {
			_fac[i] = _fac[i - 1] * i;
		}
		_invfac[m] = _fac[m].inv();
		for (int i = m; i > n; i--) {
			_invfac[i - 1] = _invfac[i] * i;
			_inv[i] = _invfac[i] * _fac[i - 1];
		}
		n = m;
	}

	Z fac(int m) {
		if (m > n) init(2 * m);
		return _fac[m];
	}
	Z invfac(int m) {
		if (m > n) init(2 * m);
		return _invfac[m];
	}
	Z inv(int m) {
		if (m > n) init(2 * m);
		return _inv[m];
	}
	Z binom(int n, int m) {
		if (n < m || m < 0) return 0;
		return fac(n) * invfac(m) * invfac(n - m);
	}
} comb;

int main() {
	freopen("perm.in","r",stdin);
	freopen("perm.out","w",stdout);
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int n, q;
	std::cin >> n >> q;

	std::vector<int> a(n);
	for (int i = 0; i < n; i++) {
		std::cin >> a[i];
	}

	std::vector<Z> f(n + 1);
	f[0] = 1;

	std::vector<std::array<int, 3>> qry(q);
	for (int i = 0; i < q; i++) {
		int l, r;
		std::cin >> l >> r;
		qry[i] = {l, r, i};
	}

	std::vector<Z> ans(q);

	const int B = 50;

	std::sort(qry.begin(), qry.end(), [&](auto a, auto b) {
		if (a[0] / B != b[0] / B) {
			return a[0] < b[0];
		} else {
			return a[1] < b[1];
		}
	});

	int l = 0, r = 0;

	std::vector<int> cnt(n);

	auto add = [&](int x, int v) {
		if (cnt[x] != 0) {
			for (int i = 1; i <= n; i++) {
				f[i] += f[i - 1] * cnt[x];
			}
		}
		cnt[x] += v;
		if (cnt[x] != 0) {
			for (int i = n; i >= 1; i--) {
				f[i] -= f[i - 1] * cnt[x];
			}
		}
	};

	for (auto [ql, qr, k] : qry) {
		while (r < qr) {
			add(a[r++], 1);
		}
		while (l > ql) {
			add(a[--l], 1);
		}
		while (r > qr) {
			add(a[--r], -1);
		}
		while (l < ql) {
			add(a[l++], -1);
		}
		for (int i = 0; i <= n; i++) {
			ans[k] += f[i] * comb.fac(n - i);
		}
	}

	for (auto x : ans) {
		std::cout << x << "\n";
	}

	return 0;
}