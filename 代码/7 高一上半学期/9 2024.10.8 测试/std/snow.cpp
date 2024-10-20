#include <bits/stdc++.h>
using namespace std;

#define eb(...) emplace_back(__VA_ARGS__)
#define fro(i, x, y) for (int i = (x); i <= (y); i++)
#define pre(i, x, y) for (int i = (x); i >= (y); i--)

const int N = 1e6 + 10;
const int mod = 998244353;

int n, m, t, k, ans, d[N], R[N], sm[N];
int dp1[1010][100010];
int dp2[1010][100010];
vector<int> to[N];

inline void dfs(int x, int f) {
	d[x] = d[f] + 1;
	for (auto i : to[x])
		if (i != f) dfs(i, x);
}
inline void add(int&x, int y) {
	x = (x + y >= mod ? x + y - mod : x + y);
}

signed main() {
	
	
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n >> m >> t >> k;
	fro(i, 1, n - 1) {
		int u, v;
		cin >> u >> v;
		to[u].eb(v);
		to[v].eb(u);
	}
	dfs(1, 0);
	sort(d + 1, d + n + 1);
	dp1[0][R[0] = 0] = dp2[0][R[0] = 0] = 1;
	fro(i, 1, t) {
		fro(j, 0, R[i - 1]) {
			add(dp1[i][max(0, j - m)], dp1[i - 1][j]);
			add(dp1[i][j + m + 1], mod - dp1[i - 1][j]);
			add(dp2[i][max(0, j - m)], dp2[i - 1][j]);
			add(dp2[i][j + m + 1], mod - dp2[i - 1][j]);
		}
		R[i] = R[i - 1] + m;
		fro(j, 1, R[i] + 1) add(dp1[i][j], dp1[i][j - 1]);
		fro(j, 1, R[i] + 1) add(dp2[i][j], dp2[i][j - 1]);
		fro(j, 0, R[i - 1]) if (m - j > 0) add(dp2[i][0], 1ll * (m - j) * dp2[i - 1][j] % mod);
	}
	fro(i, 1, t) fro(j, 1, R[i]) add(dp2[i][j], dp2[i][j - 1]);
	fro(i, 1, n) {
		int v = k / i, p = min(t + 2, d[i]);
		if (i == 1) {
			sm[i] = dp2[t][min(v, R[t])];
		} else if (v != k / (i - 1) || p != min(t + 2, d[i - 1])) {
			int l = p - 2;
			int r = t - p + 2;
			fro(j, 0, R[l]) add(sm[i], 1ll * dp1[l][j] * dp2[r][min(v + j, R[r])] % mod);
		} else sm[i] = sm[i - 1];
		add(ans, sm[i]);
	}
	cout << ans << "\n";
	return 0;
}