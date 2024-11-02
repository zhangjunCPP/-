#include <bits/stdc++.h>

using namespace std;

typedef long long LL;
const int N = 5e5 + 10;
const LL P = 998244353ll;

LL qpow(LL a, LL b, LL p) {
	LL res = 1;
	for (; b; a = a * a % p, b >>= 1)
		if (b & 1) res = res * a % p;
	return res;
}

vector<int> G[N];
int col[N][2];
int n;

int siz[N], dep[N], fa[N][20];
int dfn[N], low[N], tot;
void dfs(int x, int f) {
	dfn[x] = ++tot;
	siz[x] = 1;
	dep[x] = dep[f] + 1;
	fa[x][0] = f;
	for (int i = 1; i < 20; i++)
		fa[x][i] = fa[fa[x][i - 1]][i - 1];
	for (int y : G[x])
		if (y != f) {
			dfs(y, x);
			siz[x] += siz[y];
		}
	low[x] = tot;
	return ;
}

int getchild(int x, int y) {
	for (int i = 19; ~i; i--)
		if (dep[fa[y][i]] > dep[x])
			y = fa[y][i];
	return y;
}
int lca(int x, int y) {
	if (dep[x] > dep[y]) swap(x, y);
	int d = dep[y] - dep[x];
	for (int i = 19; ~i; i--)
		if ((d >> i) & 1) y = fa[y][i];
	if (y == x) return x;
	for (int i = 19; ~i; i--)
		if (fa[x][i] != fa[y][i]) {
			x = fa[x][i];
			y = fa[y][i];
		}
	return fa[x][0];
}

int C[N];
void update(int x, int d) {
	for (; x <= 2 * n; x += x & -x)
		(C[x] += d) %= P;
}
int query(int x) {
	int res = 0;
	for (; x > 0; x -= x & -x)
		(res += C[x]) %= P;
	return res;
}
int query(int l, int r) {
	return (query(r) - query(l - 1)) % P;
}

vector<pair<int, int>> q[N];
int oth[N];
int ans;

void add_query(int l, int u, int v, int c, int x) {
	if (l != u) {
		q[u].push_back(make_pair(c, x));
		q[v].push_back(make_pair(c, x));
		q[fa[l][0]].push_back(make_pair(c, -2ll * x % P));
	} else {
		q[v].push_back(make_pair(c, x));
		q[u].push_back(make_pair(c, -x));
	}
	// printf("%d %d %d\n", u, v, c);
}
void solve(int x, int f) {
	update(dfn[oth[x]], siz[oth[x]]);
	for (auto p : q[x]) {
		int u = p.first, c = p.second;
		(ans += (LL)query(dfn[u] + 1, low[u]) * c % P) %= P;
	}
	for (auto y : G[x])
		if (y != f) solve(y, x);
	update(dfn[oth[x]], -siz[oth[x]]);
	return ;
}

int main() {
	scanf("%d", &n);
	for (int i = 1, x; i <= 2 * n; i++) {
		scanf("%d", &x);
		if (!col[x][0]) col[x][0] = i;
		else col[x][1] = i;
	}
	for (int i = 1, u, v; i < 2 * n; i++) {
		scanf("%d%d", &u, &v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	dfs(1, 0);

	int res = 0;
	for (int i = 1; i <= n; i++) {
		if (dfn[col[i][0]] > dfn[col[i][1]])
			swap(col[i][0], col[i][1]);
		if (low[col[i][0]] >= low[col[i][1]]) {
			int c = getchild(col[i][0], col[i][1]);
			(res += (LL)siz[col[i][1]] * (2ll * n - siz[c]) % P) %= P;
			add_query(col[i][0], col[i][0], col[i][1], col[i][1], 2ll * (2ll * n - siz[c]));
		} else {
			int l = lca(col[i][0], col[i][1]);
			(res += (LL)siz[col[i][0]] * siz[col[i][1]] % P) %= P;
			add_query(l, col[i][0], col[i][1], col[i][0], siz[col[i][1]]);
			add_query(l, col[i][0], col[i][1], col[i][1], siz[col[i][0]]);
			add_query(l, l, col[i][0], col[i][0], siz[col[i][1]]);
			add_query(l, l, col[i][1], col[i][1], siz[col[i][0]]);
		}
	}
	for (int i = 1; i <= n; i++) {
		oth[col[i][0]] = col[i][1];
		oth[col[i][1]] = col[i][0];
	}
	solve(1, 0);

	printf("%d\n", ((res + qpow(2ll, P - 2, P) * ans % P) % P + P) % P);

	return 0;
}