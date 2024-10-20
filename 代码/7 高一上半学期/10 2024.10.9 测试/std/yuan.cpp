#include <bits/stdc++.h>

using i64 = long long;

void solve() {
	int n;
	i64 k;
	std::cin >> n >> k;
	k = std::min(k, 20ll);
	std::vector<i64> a(n);
	for (i64 &i : a) std::cin >> i;
	if (k) {
		k--;
		std::vector<std::pair<i64, int>> b(n);
		for (int i = 0; i < n; i++) b[i] = std::make_pair(a[i], i);
		std::sort(b.begin(), b.end());
		for (int l = 0, r; l < n; l = r) {
			for (r = l + 1; r < n && b[l].first == b[r].first; r++);
			for (int i = l; i < r; i++) a[b[i].second] = r - l;
		}
		while (k--) {
			std::vector<int> cnt(n + 1);
			for (i64 i : a) cnt[i]++;
			for (i64 &i : a) i = cnt[i];
		}
	}
	for (int i = 0; i < n; i++) std::cout << a[i] << " \n"[i == n - 1];
}

int main() {
	
	
	std::cin.tie(nullptr)->sync_with_stdio(false);
	int t;
	std::cin >> t;
	while (t--) solve();
}