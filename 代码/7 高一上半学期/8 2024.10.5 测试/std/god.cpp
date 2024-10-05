// MagicDark
#include <bits/stdc++.h>
#define debug cerr << "\33[32m[" << __LINE__ << "]\33[m "
#define SZ(x) ((int) x.size() - 1)
#define all(x) x.begin(), x.end()
#define ms(x, y) memset(x, y, sizeof x)
#define F(i, x, y) for (int i = (x); i <= (y); i++)
#define DF(i, x, y) for (int i = (x); i >= (y); i--)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
template <typename T> T& chkmax(T& x, T y) {return x = max(x, y);}
template <typename T> T& chkmin(T& x, T y) {return x = min(x, y);}
template <typename T> T& read(T &x) {
	x = 0; int f = 1; char c = getchar();
	for (; !isdigit(c); c = getchar()) if (c == '-') f = - f;
	for (; isdigit(c); c = getchar()) x = (x << 1) + (x << 3) + (c ^ 48);
	return x *= f;
}
const int N = 5010, MOD = 1e9 + 7;
inline int& add(int &x, ll y) {return x = (x + y) % MOD;}
inline int power(int x, int y = MOD - 2) {
	int ans = 1;
	for (; y; x = (ll) x * x % MOD, y >>= 1)
		if (y & 1) ans = (ll) ans * x % MOD;
	return ans;
}
int n, p, a[N], dp[N][N * 2], ans;
signed main() {
	freopen("god.in", "r", stdin);
	freopen("god.out", "w", stdout);
	read(n), read(p);
	p = (ll) p * power(100) % MOD;
	int ip = (1 - p + MOD) % MOD;
	F(i, 1, n) read(a[i]);
	dp[0][n] = 1;
	F(i, 1, n) {
		F(j, n - (i - 1), n + (i - 1)) {
			add(dp[i][j], (ll) p * dp[i - 1][j]);
			add(dp[i][j + a[n - i + 1]], (ll) ip * dp[i - 1][j]);
		}
		dp[i][n] = 1;
	}
	F(i, 0, 2 * n) cout << dp[n][i] << ' ';
	return 0;
}
/* why?
*/