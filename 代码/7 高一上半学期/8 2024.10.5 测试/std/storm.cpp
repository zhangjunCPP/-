#include <bits/stdc++.h>
#define debug cerr << "[" << __LINE__ << "] "
#define SZ(x) (int) x.size() - 1
#define all(x) x.begin(), x.end()
#define ms(x, y) memset(x, y, sizeof x)
#define F(i, x, y) for (int i = (x); i <= (y); i++)
#define DF(i, x, y) for (int i = (x); i >= (y); i--)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
template <typename T> inline void chkmax(T& x, T y) { x = max(x, y); }
template <typename T> inline void chkmin(T& x, T y) { x = min(x, y); }
template <typename T> inline void read(T &x) {
	x = 0; int f = 1; char c = getchar();
	for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
	for (; isdigit(c); c = getchar()) x = (x << 1) + (x << 3) + (c ^ 48);
	x *= f;
}
const int N = 1010, M = 1e5 + 10;
int n, m, k, a[N][N], l[M], r[M], u[M], d[M];
signed main() {
	freopen("storm.in", "r", stdin);
	freopen("storm.out", "w", stdout);
	read(n), read(m), read(k);
	ms(l, 0x3f), ms(u, 0x3f);
	F(i, 1, n)
		F(j, 1, m) {
			read(a[i][j]);
			chkmin(l[a[i][j]], j);
			chkmin(u[a[i][j]], i);
			chkmax(r[a[i][j]], j);
			chkmax(d[a[i][j]], i);
		}
	F(i, 1, k) {
		if (!r[i]) {
			puts("0");
			continue;
		}
		int e = max(r[i] - l[i] + 1, d[i] - u[i] + 1);
		cout << e * e << '\n';
	}
	return 0;
}