#include <iostream>
#include <algorithm>
#include <set>

int n, q, a[300007];
int f[300007];
int p[300007];

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	std::cin >> n >> q;
	for (int i = 1; i <= n; ++i) {
		std::cin >> a[i];
	}
	std::sort(a + 1, a + n + 1);
	std::multiset<int, std::greater<>> s;
	int l = 0;
	for (int i = 1; i <= n; ++i) {
		s.insert(f[i - 1] - (i - 1));
		while (l < i + 1 - a[i] && l < i - 1) {
			s.erase(s.find(f[l] - l));
			++l;
		}
		while (l > i + 1 - a[i] && l > 0) {
			--l;
			s.insert(f[l] - l);
		}
		f[i] = -0x3b9aca00;
		if (i - a[i] >= 0) {
			f[i] = p[i - a[i]] + 1;
		}
		if (!s.empty()) {
			f[i] = std::max(f[i], *s.begin() + i - a[i] + 1);
		}
		p[i] = std::max(p[i - 1], f[i]);
	}
	for (int i = 0; i <= n; ++i) {
		f[i] += n - i;
	}
	while (q--) {
		int x;
		std::cin >> x;
		int l = 0, r = n, ans = -1;
		while (l <= r) {
			int mid = (l + r) >> 1;
			if (f[mid] >= x) {
				l = (ans = mid) + 1;
			} else {
				r = mid - 1;
			}
		}
		std::cout << ans << ' ';
	}
	std::cout << '\n';
	return 0;
}