#include <bits/stdc++.h>
#define ms(x, v) memset(x, v, sizeof(x))
#define il __attribute__((always_inline)) static
#define U(i,l,r) for(int i(l),END##i(r);i<=END##i;++i)
#define D(i,r,l) for(int i(r),END##i(l);i>=END##i;--i)
using namespace std;
using ll = long long;

#define IC isdigit(c)
#define GC c=getchar()
void rd(auto &x) { x = 0; char GC; bool f = 0;
	for (; !IC; GC) f |= c == '-';
	for (; IC; GC) x = x * 10 + c - 48;
	if (f) x = -x;
}
void rd(auto &x, auto &...y) { rd(x); rd(y...); }
#define meow(...) fprintf(stderr, __VA_ARGS__)
#define Assert(e) if (!(e)) { meow("AF@%d\n", __LINE__); exit(__LINE__); }

#define vc vector
#define pb push_back
#define eb emplace_back

const int N = 500005, M = 90;
const ll P = 1000000007;
int n, Q, ch[N][2];

int f0[N][2][2]; // 当前点选/不选 右链底选/不选
void dfs(int u) {
	U (c, 0, 1) if (ch[u][c])
		dfs(ch[u][c]);
	ms(f0[u], 0xc0);
	if (!ch[u][0] && !ch[u][1]) {
		f0[u][0][0] = 0;
		f0[u][1][1] = 1;
		return;
	}
	U (c, 0, 1) { // 当前点选/不选
		int rl = 0, rr = 1; if (!ch[u][1]) rl = rr = c;
		U (r, rl, rr) {
			U (x, 0, 1 - c) U (t, 0, 1) U (y, 0, 1 - c)
				f0[u][c][r] = max(f0[u][c][r], f0[ch[u][0]][x][t] + f0[ch[u][1]][y][r] + c);
		}
	}
}

// dp of dp
// 当前状态：A=x, B=x-1, C=x-2

using info = array<int, 5>;
void shrink(info &t) {
	int mx = -1e9; U (s, 0, 3) mx = max(mx, t[s]);
	U (s, 0, 3) t[s] -= mx;
	t[4] = mx;
	U (s, 0, 3) if (t[s] < -2)
		t[s] = -3;
}
info gen_trans(info f) {
	info res; res.fill(-1e9);
	U (s1, 0, 3) if (f[s1] != -3) U (s2, 0, 3) if (f[s2] != -3) U (s3, 0, 3) if (f[s3] != -3) U (s4, 0, 3) if (f[s4] != -3) {
		U (rt, 0, 1 - ((s1 & 1) | (s2 & 1))) U (r2, 0, 1 - ((s2 >> 1) | (s3 & 1) | (s4 & 1))) {
			int s = rt | (s4 & 2);
			res[s] = max(res[s], f[s1] + f[s2] + f[s3] + f[s4] + rt + r2);
		}
	}

	info org = res;
	shrink(res);
	return res;
}
info init(info f) { // G1 一次
	info res; res.fill(-1e9);
	U (s1, 0, 3) U (s2, 0, 3) if (!((s1 & 2) && (s2 & 1))) {
		int s = (s1 & 1) | (s2 & 2);
		res[s] = max(res[s], f[s1] + f[s2]);
	}

	shrink(res);
	return res;
}

map<info, int> id;
int m;
pair<int, int> to[M];
ll init_v[N]; info inital[N];

void pre() {
	queue<info> q;
	U (u, 1, n) {
		info t {}; int mx = -1;
		U (x, 0, 1) U (y, 0, 1)
			t[x | (y << 1)] = f0[u][x][y], mx = max(mx, f0[u][x][y]);

		shrink(t);
		t[4] = 0;
		info s = init(t);
		init_v[u] = 2 * mx + s[4];
		s[4] = 0;
		inital[u] = s;
		q.push(s);
	}
	while (q.size()) {
		info s = q.front(); q.pop();
		if (id[s]) continue;
		id[s] = id.size();
		info t = gen_trans(s);
		t[4] = 0;
		q.push(t);
	}

	m = id.size();
	for (auto &[s, i] : id) {
		info t = gen_trans(s), w = t; w[4] = 0;
		int j = id[w];
		to[i] = {j, t[4]};
	}
}

struct F {
	ll k, b;
	void comp(ll kx, ll bx) {
		ll nk = kx * k %P, nb = (kx * b + bx) %P;
		k = nk, b = nb;
	}
};
F qpow(F x, ll t) { F v{1, 0};
	for (; t; x.comp(x.k, x.b), t >>= 1) if (t & 1)
		v.comp(x.k, x.b);
	return v;
}

int main() {

	rd(n, Q);
	U (i, 1, n) rd(ch[i][0], ch[i][1]);
	dfs(1);

	pre();

	while (Q--) {
		int u; ll x; rd(x, u);

		--x;
		int i = id[inital[u]]; ll v = init_v[u];
		F f{1, 0};
		if (x <= m * 2) {
			U (j, 1, x) {
				f.comp(4, to[i].second);
				i = to[i].first;
			}
		} else {
			bool vis[M * 2] {}; int stk[M * 2] {}, sp = 0;
			while (!vis[i]) {
				vis[i] = 1;
				stk[++sp] = i;
				f.comp(4, to[i].second);
				--x;
				i = to[i].first;
			}
			int b = sp, a = sp;
			while (stk[a] != i) --a;
			int l = b - a + 1;
			F g{1, 0};
			U (t, a, b) {
				g.comp(4, to[stk[t]].second);
			}
			g = qpow(g, x / l);
			x %= l;
			f.comp(g.k, g.b);
			while (x) {
				f.comp(4, to[i].second);
				--x;
				i = to[i].first;
			}
		}
		ll ans = (f.k * v + f.b) %P;
		printf("%lld\n", ans);
	}
}