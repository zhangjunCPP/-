#include <bits/stdc++.h>
#define MAXN 50
#define MOD ((int) 1e9 + 7)
using namespace std;

int n;
long long ans;
char s[MAXN + 10];

int A[MAXN + 10];
long long f[MAXN + 10], fac[MAXN + 10], ifac[MAXN + 10];

void gao(int L, int R) {
	int len = R - L + 1;
	int cnt[10] = {0};
	for (int i = 1; i < L; i++) cnt[A[i]]++;

	for (int m = 1; m <= 9; m++) for (int c = cnt[m]; c <= cnt[m] + len; c++) {
		int tot = len - (c - cnt[m]);
		auto calc = [&]() {
			memset(f, 0, sizeof(long long) * (tot + 3));
			f[0] = 1;
			for (int i = 0; i <= 9; i++) if (i != m) {
				int lim = c - (i > m ? 1 : 0) - cnt[i];
				if (lim < 0) return 0LL;
				for (int j = tot; j > 0; j--) for (int k = 1; k <= lim && k <= j; k++)
					f[j] = (f[j] + f[j - k] * ifac[k]) % MOD;
			}
			return f[tot];
		};
		ans = (ans + m * calc() % MOD * fac[len] % MOD * ifac[c - cnt[m]]) % MOD;
	}
}

void solve() {
	scanf("%s", s + 1); n = strlen(s + 1);
	ans = 0;
	for (int i = 1; i < n; i++) for (A[1] = 1; A[1] <= 9; A[1]++) gao(2, i);
	for (int i = 1; i <= n; i++) for (A[i] = (i == 1 ? 1 : 0); A[i] < s[i] - '0'; A[i]++) gao(i + 1, n);
	gao(n + 1, n);
	printf("%lld\n", ans);
}

int main() {
	fac[0] = 1;
	for (int i = 1; i <= MAXN; i++) fac[i] = fac[i - 1] * i % MOD;
	ifac[0] = ifac[1] = 1;
	for (int i = 2; i <= MAXN; i++) ifac[i] = (MOD - MOD / i) * ifac[MOD % i] % MOD;
	for (int i = 2; i <= MAXN; i++) ifac[i] = ifac[i] * ifac[i - 1] % MOD;

	int tcase; scanf("%d", &tcase);
	while (tcase--) solve();
	return 0;
}