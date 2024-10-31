#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 100005;
const int mod = 998244353;
char str[MAXN];
int hsh[26][MAXN], pw[MAXN];
char ord[MAXN][26], rk[MAXN][26];
int main() {

	int t; scanf("%d", &t); while (t--) {
		scanf("%s", str + 1); int n = strlen(str + 1);
		for (int i = 0; i < 26; i++) ord[n + 1][i] = rk[n + 1][i] = i;
		for (int i = n; i; i--) {
			memcpy(ord[i], ord[i + 1], sizeof ord[0]); memcpy(rk[i], rk[i + 1], sizeof rk[0]);
			int p = rk[i][str[i] - 'a']; rk[i][str[i] - 'a'] = 0;
			for (int j = 0; j < p; j++) rk[i][ord[i][j]]++;
			for (int j = p; j; j--) ord[i][j] = ord[i][j - 1];
			ord[i][0] = str[i] - 'a';
		}


		pw[0] = 1; for (int i = 1; i <= n; i++) pw[i] = 131ll * pw[i - 1] % mod;
		for (int c = 0; c < 26; c++) for (int i = 1; i <= n; i++) {
			hsh[c][i] = (131ll * hsh[c][i - 1] + (str[i] - 'a' == c)) % mod;
		}

		int ans = n;
		for (int i = n - 1; i; i--) {
			int l = 0, r = n - ans + 2; while (l + 1 < r) {
				int mid = (l + r) >> 1; bool tag = 1;
				for (int j = 0; j < 26; j++) {
					int h1 = (hsh[ord[i][j]][i + mid - 1] - 1ll * hsh[ord[i][j]][i - 1] * pw[mid] % mod + mod) % mod;
					int h2 = (hsh[ord[ans][j]][ans + mid - 1] - 1ll * hsh[ord[ans][j]][ans - 1] * pw[mid] % mod + mod) % mod;
					tag &= h1 == h2;
				}
				if (tag) l = mid; else r = mid;
			}
			if (l == n - ans + 1) ans = i;
			else {
				assert(rk[i][str[i + l] - 'a'] != rk[ans][str[ans + l] - 'a']);
				if (rk[i][str[i + l] - 'a'] < rk[ans][str[ans + l] - 'a']) ans = i;
			}
		}
		// printf("%d\n", ans);
		for (int i = ans; i <= n; i++) putchar('z' - rk[ans][str[i] - 'a']); puts("");
	}
}