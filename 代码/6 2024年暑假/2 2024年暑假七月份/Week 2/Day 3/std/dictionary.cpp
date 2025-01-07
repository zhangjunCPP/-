#include <bits/stdc++.h>
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
constexpr i64 inf = 1e15;
i64 fPre[55];
i64 f(i64 k) {
	int n = std::__lg(k) + 1;
	return fPre[n] + (k - (1ll << (n - 1)) + 1) * n;
}
int main() {
	std::freopen("dictionary.in", "r", stdin);
	std::freopen("dictionary.out", "w", stdout);
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	for (int i = 1; i < 54; ++i) {
		fPre[i + 1] = fPre[i] + (1ll << (i - 1)) * i;
	}
	std::vector<i64> a{1}, d{1};
	auto D = [&](i64 n) {
		int k = std::upper_bound(a.begin(), a.end(), n) - a.begin();
		return d[k - 1] + k * (n - a[k - 1]);
	};
	auto calcD = [&](i64 n) -> i64 {
		if (n == 1) {
			return 1;
		}
		i64 l = n < 1000 ? 1 : n / 3, r = n / 2;
		while (l < r) {
			i64 m = (l + r) / 2;
			i64 fl = (m == 1 ? 0 : f(m)) + D(m) + D(n - m);
			i64 fr = f(m + 1) + D(m + 1) + D(n - m - 1);
			if (fl < fr) {
				r = m;
			} else {
				l = m + 1;
			}
		}
		return f(n) + (l == 1 ? 0 : f(l)) + D(l) + D(n - l);
	};
	int delta = 1;
	while (a.back() < inf) {
		i64 m = a.back();
		while (m < 1000 && calcD(m + 1) == d.back() + delta * (m + 1 - a.back())) {
			m++;
		}
		if (m >= 1000) {
			while (calcD(m / 2 * 3) == d.back() + delta * (m / 2 * 3 - a.back())) {
				m = m / 2 * 3;
			}
			i64 l = m, r = m / 2 * 3 - 1;
			while (l < r) {
				i64 x = (l + r + 1) / 2;
				if (calcD(x) == d.back() + delta * (x - a.back())) {
					l = x;
				} else {
					r = x - 1;
				}
			}
			m = l;
		}
		d.push_back(calcD(m));
		a.push_back(m);
		delta++;
	}
	int q;
	std::cin >> q;
	while (q--) {
		i64 n;
		std::cin >> n;
		std::cout << D(n) << "\n";
	}
	return 0;
}