#include <algorithm>
#include <iostream>

constexpr int mod = 0x3b800001;
int n, a[5007];

int dp[5007];
int solve() {
	for (int i = 1; i <= n; ++i) {
		dp[i] = a[i] = (a[i] % mod + mod) % mod;
	}
	for (int i = 2; i <= n; ++i) {
		int s = 0;
		for (int j = n; j >= 1; --j) {
			int t = (s + dp[j]) % mod;
			dp[j] = (s + dp[j] * (n - i - j + 2LL)) % mod * a[j] % mod;
			s = t;
		}
	}
	return dp[1];
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	std::cin >> n;
	for (int i = 1; i <= n; ++i) {
		std::cin >> a[i];
	}
	std::sort(a + 1, a + n + 1);
	std::cout << solve() << ' ';
	std::reverse(a + 1, a + n + 1);
	std::cout << solve() << '\n';
	return 0;
}