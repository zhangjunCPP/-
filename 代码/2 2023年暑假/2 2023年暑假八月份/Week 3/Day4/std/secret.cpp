#include <bits/stdc++.h>

using namespace std;

int solve255(int n, const vector<pair<int, int>> &d) {
	int s = 0;
	for (const auto &t: d) {
		s = (s + (t.first % 255) * (t.second % 255)) % 255;
	}
	vector<int> primes = {3, 5, 17};
	vector<int> ost = {0, 0, 0};
	for (int it = 0; it < (int) primes.size(); it++) {
		if (s % primes[it] == 0) {
			continue;
		}
		int pw = 1;
		for (int i = 1; i <= n && pw != 0; i++) {
			pw = (pw * i) % (primes[it] - 1);
		}
		ost[it] = 1;
		for (int i = 0; i < pw; i++) {
			ost[it] = (ost[it] * s) % primes[it];
		}
	}
	for (int i = 0; i < 255; i++) {
		if (i % primes[0] == ost[0] && i % primes[1] == ost[1] && i % primes[2] == ost[2]) {
			return i;
		}
	}
	exit(233);
}

typedef bitset<257> bt;

int solve257(int n, vector<pair<int, int>> pr) {
	int pw = 1;
	for (int i = 1; i <= (n + 1) / 2 && pw != 0; i++) {
		pw = (pw * i) % 256;
	}
	for (int i = 1; i <= n / 2 && pw != 0; i++) {
		pw = (pw * i) % 256;
	}

	if (pw != 0) {
		assert(n <= 11);
		vector<int> d;
		for (const auto &t: pr) {
			for (int i = 0; i < t.second; i++) {
				d.emplace_back(t.first);
			}
		}
		int ans = 1;
		for (int mask = 0; mask < (1 << n) && ans != 0; mask++) {
			if (__builtin_popcount(mask) == (n + 1) / 2) {
				int s = 0;
				for (int i = 0; i < n; i++) {
					if ((mask >> i) & 1) {
						s += d[i];
					} else {
						s -= d[i];
					}
				}
				s %= 257;
				if (s < 0) {
					s += 257;
				}
				ans = (ans * s) % 257;
			}
		}
		int res = 1;
		for (int i = 0; i < pw; i++) {
			res = (res * ans) % 257;
		}
		return res;
	}

	sort(pr.begin(), pr.end(), [&](auto a, auto b) {
		return a.second < b.second;
	});
	int sn = 0;
	for (int i = 0; i < (int) pr.size() - 1; i++) {
		sn += pr[i].second;
	}
	if (min(sn, pr.back().second) >= 256) {
		return 0;
	}
	if (sn >= pr.back().second && n >= 256 * 2) {
		return 0;
	}

	int s = 0;
	for (const auto &t: pr) {
		s = (s + (t.first % 257) * (t.second % 257)) % 257;
	}
	s = (s * 129) % 257;
	sn = min(sn, n / 2);

	vector<bt> dp(sn + 1, 0);
	dp[0][0] = true;

	for (int it = 0; it < (int) pr.size() - 1; it++) {
		for (int c = 0; c < pr[it].second; c++) {
			int d = pr[it].first;
			for (int k = sn - 1; k >= 0; k--) {
				dp[k + 1] |= (dp[k] << d);
				if (d != 0) {
					dp[k + 1] |= (dp[k] >> (257 - d));
				}
			}
		}
	}

	for (int k = 0; k <= sn; k++) {
		for (int sm = 0; sm < 257; sm++) {
			if (dp[k][sm] && pr.back().second + k >= (n / 2)) {
				int cur = (sm + (((n / 2) - k) % 257) * pr.back().first) % 257;
				if (cur == s) {
					return 0;
				}
			}
		}
	}

	return 1;
}

int crt[300][300];

int solve_digits(int n, const vector<pair<int, int>> &d) {
	return crt[solve255(n, d)][solve257(n, d)];
}

void solve() {
	int k;
	cin >> k;
	vector<pair<int, int>> d;
	int n = 0;
	for (int i = 0; i < k; i++) {
		int x, y;
		cin >> x >> y;
		d.emplace_back(x, y);
		n += y;
	}
	cout << solve_digits(n, d) << "\n";
}

int main() {
	freopen("secret.in", "r", stdin);
	freopen("secret.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	for (int i = 0; i < 255 * 257; i++) {
		crt[i % 255][i % 257] = i;
	}

	int t;
	cin >> t;
	while (t--) {
		solve();
	}

	return 0;
}
