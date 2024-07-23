#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;
using u64 = unsigned long long;

constexpr u32 P = 998244353;

constexpr int N = 300;
int A[N + 1];

u32 dp[2][N + 1][N + 1][2];
u32 fac[N + 1], binom[N + 1][N + 1];

void inc(u32 &a, u32 b) {
	a += b;
	if (a >= P) {
		a -= P;
	}
}

u32 add(u32 a, u32 b) {
	inc(a, b);
	return a;
}

int main() {
	freopen("heap.in","r",stdin);
	freopen("heap.out","w",stdout);
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int N, M;
	std::cin >> N >> M;

	std::string S;
	std::cin >> S;

	for (int i = 1; i <= M; i++) {
		std::cin >> A[i];
	}
	fac[0] = 1;
	for (int i = 1; i <= N; i++) {
		fac[i] = u64(fac[i - 1]) * i % P;
	}
	for (int i = 0; i <= N; i++) {
		binom[i][0] = 1;
		for (int j = 1; j <= i; j++) {
			binom[i][j] = add(binom[i - 1][j - 1], binom[i - 1][j]);
		}
	}

	int cur = 0;
	dp[cur][M][0][0] = 1;
	int pop = 0;
	int push = 0;
	for (auto c : S) {
		cur ^= 1;
		std::memset(dp[cur], 0, sizeof(dp[cur]));
		if (c == '+') {
			for (int i = 0; i <= M; i++) {
				for (int j = 0; j <= i; j++) {
					if (j < i) {
						inc(dp[cur][i][j + 1][0], dp[cur ^ 1][i][j][0]);
						inc(dp[cur][i][j + 1][1], dp[cur ^ 1][i][j][0]);
						inc(dp[cur][i][j + 1][1], dp[cur ^ 1][i][j][1]);
					}
					int choice = N - A[i] - (M - i) - (push - pop - j);
					inc(dp[cur][i][j][0], u64(choice) * dp[cur ^ 1][i][j][0] % P);
					inc(dp[cur][i][j][1], u64(choice) * dp[cur ^ 1][i][j][1] % P);
				}
			}
			push++;
		} else {
			for (int i = 1; i <= M; i++) {
				for (int j = 1; j <= i; j++) {
					inc(dp[cur][i][j - 1][0], dp[cur ^ 1][i][j][0]);
					if (j != 1) {
						inc(dp[cur][i][j - 1][1], dp[cur ^ 1][i][j][1]);
					} else {
						int free = pop - (M - i);
						for (int k = i - free - 1; k < i; k++) {
							inc(dp[cur][k][0][0], u64(binom[free][i - k - 1]) * fac[i - k - 1] % P * dp[cur ^ 1][i][1][1] % P);
						}
					}
				}
			}
			pop++;
		}
	}

	std::cout << dp[cur][0][0][0] << "\n";

	return 0;
}