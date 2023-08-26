//Author:cutx64
#include <bits/stdc++.h>
using namespace std;

template<typename _Tp> _Tp &min_eq(_Tp &x, const _Tp &y) {
	return x = min(x, y);
}

template<typename _Tp> _Tp &max_eq(_Tp &x, const _Tp &y) {
	return x = max(x, y);
}
static constexpr int inf = 0x3f3f3f3f;
static constexpr int Maxn = 2e5 + 5;
int n, m, ans, en, head[Maxn], c[Maxn];
int dn, dfn[Maxn], par[Maxn], sz[Maxn], rt[Maxn];

struct Edge {
	int to, nxt;
} e[Maxn * 2];

void add_edge(int u, int v) {
	e[++en] = (Edge) {v, head[u]}, head[u] = en;
}

void dfs(int u, int fa) {
	dfn[u] = ++dn, sz[u] = 1;
	par[u] = fa;

	for (int i = head[u]; i; i = e[i].nxt)
		if (e[i].to != fa)
			dfs(e[i].to, u), sz[u] += sz[e[i].to];
} // dfs
int low[Maxn], stk[Maxn], top;
bool instk[Maxn], inc[Maxn], bad;

void tarjan(int u) {
	dfn[u] = low[u] = ++dn;
	stk[++top] = u, instk[u] = true;

	for (int i = head[u], v; i; i = e[i].nxt)
		if (!dfn[v = e[i].to])
			tarjan(v), min_eq(low[u], low[v]);
		else if (instk[v])
			min_eq(low[u], dfn[v]);

	if (dfn[u] == low[u]) {
		static int t[Maxn], s;
		s = 0, bad = false;

		do
			inc[t[++s] = stk[top]] = true;

		while (stk[top--] != u);

		for (int i = 1; i <= s && !bad; ++i)
			for (int u = t[i], j = head[u]; j && !bad; j = e[j].nxt)
				if (inc[e[j].to] == false)
					bad = true;

		if (!bad)
			ans = min(ans, s - 1);

		for (int i = 1; i <= s; ++i)
			inc[t[i]] = false;
	}
} // tarjan

int main(void) {
	
	freopen("city.in","r",stdin);
	freopen("city.out","w",stdout);
	extern uint32_t readu32(void);
	n = readu32(), m = readu32();
	ans = m - 1;
	en = 0, memset(head, 0, sizeof(head));

	for (int i = 1, u, v; i <= n - 1; ++i)
		u = readu32(), v = readu32(), add_edge(u, v), add_edge(v, u);

	dfn[0] = inf, dfs(1, 0);

	for (int i = 1; i <= n; ++i) {
		int &t = rt[c[i] = readu32()];

		if (dfn[t] > dfn[i])
			t = i;
	}

	en = 0, memset(head, 0, sizeof(head));

	for (int i = 1; i <= n; ++i) {
		int &t = rt[c[i]];

		if (dfn[i] >= dfn[t] + sz[t])
			t = 0;
	}

	dn = 0, memset(dfn, 0, sizeof(dfn));

	for (int i = 1; i <= n; ++i)
		if (i != rt[c[i]])
			add_edge(c[i], c[par[i]]);

	for (int i = 1; i <= m; ++i)
		if (!dfn[i])
			tarjan(i);

	exit(printf("%d\n", ans) & 0);
} // main
// fast io
static const int _BUF_SIZE = 1 << 18;
static char _ibuf[_BUF_SIZE], *iS = _ibuf, *iT = _ibuf;

inline char getch(void) {
	if (__builtin_expect(iS == iT, false))
		iT = (iS = _ibuf) + fread(_ibuf, 1, _BUF_SIZE, stdin);

	if (__builtin_expect(iS == iT, false))
		return EOF;
	else
		return *iS++;
} // getch

uint32_t readu32(void) {
	register uint32_t x = 0;
	register char ch = getch();

	while (ch < '0' || ch > '9')
		ch = getch();

	while (ch >= '0' && ch <= '9')
		((x += (x << 2)) <<= 1) += (ch ^ '0'), ch = getch();

	return x;
} // readu32