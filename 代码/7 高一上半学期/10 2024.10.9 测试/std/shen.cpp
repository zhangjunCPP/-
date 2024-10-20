#include <bits/stdc++.h>

constexpr int P = 998244353;

int power(int b, int e) {
	int res = 1;
	while (e) {
		if (e & 1) res = 1ll * res * b % P;
		b = 1ll * b * b % P, e >>= 1;
	}
	return res;
}

int main() {
	
	
	std::cin.tie(nullptr)->sync_with_stdio(false);
	int n, m;
	std::cin >> n >> m;
	int ivs = power(n % P, P - 2);

	std::vector<std::vector<int>> bin(m + 2, std::vector<int>(m + 2)), pw(3, std::vector<int>(m + 2));
	bin[0][0] = pw[0][0] = pw[1][0] = pw[2][0] = 1;
	for (int i = 1; i <= m + 1; i++) {
		bin[i][0] = bin[i][i] = 1;
		for (int j = 1; j < i; j++) {
			bin[i][j] = bin[i - 1][j - 1] + bin[i - 1][j];
			if (bin[i][j] >= P) bin[i][j] -= P;
		}
		pw[0][i] = 1ll * pw[0][i - 1] * (n - 1) % P;
		pw[1][i] = 1ll * pw[1][i - 1] * (n + 1) % P;
		pw[2][i] = 1ll * pw[2][i - 1] * ivs % P;
	}

	std::vector<int> s(m + 2);
	s[0] = n % P;
	for (int i = 1; i <= m; i++) {
		for (int j = 0; j < i; j++) s[i] = (s[i] + 1ll * bin[i + 1][j] * s[j]) % P;
		s[i] = 1ll * (pw[1][i + 1] - s[i] - 1 + P) * power(i + 1, P - 2) % P;
	}

	auto calc = [&](int a, int b, int c, int d) -> int {
		int res = 0;
		for (int i = 0; i <= a; i++) {
			int tmp = 1ll * bin[a][i] * pw[1][a - i] % P * s[b + i] % P;
			if (i & 1) {
				res -= tmp;
				if (res < 0) res += P;
			} else {
				res += tmp;
				if (res >= P) res -= P;
			}
		}
		return 1ll * res * pw[0][c] % P * pw[2][a + b + c + d] % P;
	};

	int a = 0, b = 0, c = 0;
	for (int i = 0; i < m; i++) {
		char op;
		std::cin >> op;

		int res;
		if (op == '<') {
			res = calc(a + 1, b, c, 0) - calc(a, b, c, 1);
			if (res < 0) res += P;
			++b;
		} else if (op == '>') {
			res = calc(a, b + 1, c, 0) - calc(a, b, c, 1);
			if (res < 0) res += P;
			++a;
		} else {
			res = calc(a, b, c, 1);
			++c;
		}
		std::cout << res << ' ';
	}
	std::cout << calc(a, b, c, 0) << '\n';
}