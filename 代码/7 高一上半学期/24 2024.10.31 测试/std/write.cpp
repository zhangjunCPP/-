#include <cstdio>
#include <cstring>
#include <numeric>
#include <algorithm>
#include <cctype>
#include <queue>
#include <vector>
#include <set>
#include <map>
#include <cmath>

namespace uvu
{
#define LOCAL ________________DONT_DEFINE_ME_______________
// #define ll long long
// #define inf 0x3f3f3f3f
#define int __int128
// #define inf 0x3f3f3f3f3f3f3f3f3f3f3f3f3f3f3f3f
#define inf ((__int128_t)0x3f3f3f3f3f3f3f3fll * 0x3f3f3f3f3f3f3f3fll)
// #define infll 0x3f3f3f3f3f3f3f3fll
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define gline debug("now is #%d\n", __LINE__)
#define pii std::pair <int, int>
#define mkp std::make_pair
#define fi first
#define se second
char _ST_;
const int BUFSIZE = (1 << 20);
char ibuf[BUFSIZE], *iS = ibuf, *iT = ibuf;
char obuf[BUFSIZE], *oS = obuf, *oT = obuf + BUFSIZE;
char getc()
{
#ifdef LOCAL
	return getchar();
#else
	if(iS == iT) iT = (iS = ibuf) + fread(ibuf, 1, BUFSIZE, stdin);
	return (iS == iT) ? EOF : *iS++;
#endif
#define getchar ERR
}
void Flush() { fwrite(obuf, 1, oS - obuf, stdout); oS = obuf; }
struct Flusher { ~Flusher() { Flush(); } }iamflusher;
void putc(char c)
{
#ifdef LOCAL
	putchar(c);
#else
	*oS++ = c;
	if(oS == oT) Flush();
#endif
}
template <typename T = int> T read()
{
	T x = 0, f = 1; char c = getc();
	for(; !isdigit(c); c = getc()) if(c == '-') f = -1;
	for(;  isdigit(c); c = getc()) x = (x << 3) + (x << 1) + (c ^ 48);
	return x * f;
}
template <typename T> void print(T x, char c)
{
static int sta[BUFSIZE], top;
	top = 0;
	if(x < 0) putc('-'), x *= -1;
	if(!x) sta[++top] = 0;
	for(; x; x /= 10) sta[++top] = x % 10;
	for(; top; putc(sta[top--] ^ 48));
	if(c) putc(c);
}
int readstr(char *s, int base)
{
	int idx = base - 1; char c = getc();
	for(; !(isdigit(c) || isalpha(c) || c == '#' || c == '.'); c = getc());
	for(;   isdigit(c) || isalpha(c) || c == '#' || c == '.' ; c = getc()) s[++idx] = c;
	return idx - base + 1;
}
void printf(const char *s) { for(; *s; s++) putc(*s); }
template <typename T, typename ... Args >
void printf(const char *s, T x, Args ... flgt)
{
	for(; *s; s++)
	{
		if(*s != '%') { putc(*s); continue; }
		s++; if(*s == 'd') print(x, 0);
		else if(*s == 'c') putc(x);
		printf(s + 1, flgt ...);
		return;
	}
}
template <typename T> void ckmin(T &x, T y) { x = x < y ? x : y; }
template <typename T> void ckmax(T &x, T y) { x = x > y ? x : y; }
#define mod 998244353
// #define mod 1000000007
int sm(int x) { return x >= mod ? x - mod : x; }
void plus_(int &x, int y) { x = sm(x + y); }
void mul_(int &x, int y) { x = 1ll * x * y % mod; }
int ksm(int a, int b) { int flg = 1; for(; b; b >>= 1, mul_(a, a)) if(b & 1) mul_(flg, a); return flg; }

#define N 1000010
int n, A, B;
int a[N];
int h[N], e[N << 1], ne[N << 1], idx = -1;
void add_edge(int x, int y) { ne[++idx] = h[x], h[x] = idx, e[idx] = y; }
struct Func { int k, b; Func(int k_ = 0, int b_ = inf) { k = k_, b = b_; } int calc(int x) { return k * x + b; } };
bool cmp(Func A, Func B, int x) { return A.calc(x) < B.calc(x); }

#define M N * 3
struct Tree
{
	signed ls, rs;
	int lazy;
	Func f;
	void push(int z) { lazy += z, f.b += z; }
}tr[M];
#define lson(k) tr[k].ls
#define rson(k) tr[k].rs
#define LR 0, (__int128)1100000000000
signed rubbish[M], rubtot, nidx, root[N];
void pushrub(signed x) { rubbish[++rubtot] = x; }
signed newnode()
{
	signed k;
	if(rubtot) k = rubbish[rubtot--];
	k = ++nidx;
	tr[k] = tr[0];
	return k;
}
void pushdown(int k)
{
	if(!tr[k].lazy) return;
	if(lson(k)) tr[lson(k)].push(tr[k].lazy);
	if(rson(k)) tr[rson(k)].push(tr[k].lazy);
	tr[k].lazy = 0;
}
void ins(signed &k, int l, int r, Func z)
{
	if(!k) k = ++nidx;
	int mid = (l + r) >> 1; pushdown(k);
	if(cmp(z, tr[k].f, mid)) std::swap(z, tr[k].f);
	if(cmp(z, tr[k].f, l)) ins(lson(k), l, mid, z);
	if(cmp(z, tr[k].f, r)) ins(rson(k), mid + 1, r, z);
}

int query(signed k, int l, int r, int q)
{
	if(!k) return inf;
	if(l == r) return tr[k].f.calc(q);
	pushdown(k);
	int mid = (l + r) >> 1, res = tr[k].f.calc(q);
	if(q <= mid) return std::min(res, query(lson(k), l, mid, q));
	else return std::min(res, query(rson(k), mid + 1, r, q));
}

void merge(signed &x, signed y, int l, int r)
{
	if(!x || !y) { x |= y; return; }
	int mid = (l + r) >> 1;
	if(l == r) { ins(x, l, r, tr[y].f); return; }
	pushdown(x); pushdown(y);
	pushrub(y); auto f = tr[y].f; int ls = lson(y), rs = rson(y);
	merge(lson(x), ls, l, mid);
	merge(rson(x), rs, mid + 1, r);
	ins(x, l, r, f);
}

int g[N], mxdep, mxg;
int dep[N], dfn[N], fdfn[N];

void dfs(signed k, signed dep)
{
	fdfn[dfn[k] = ++dfn[0]] = k; uvu::dep[k] = dep;
	for(signed i = h[k]; ~i; i = ne[i]) dfs(e[i], dep + 1);
}

void calc(int k)
{
	int dep = uvu::dep[k];
	ckmax(mxdep, dep);
	// debug("k = %lld\n", k);
	for(int i = h[k]; ~i; i = ne[i]) g[k] += g[e[i]];
static int sta[N], top;
	top = 0;
	int sum = 0;
	for(int i = h[k]; ~i; i = ne[i]) sta[++top] = e[i];
#define nx sta[_]
	for(int _ = top, pre = 0; _; _--)
	{
		int v = std::min(g[nx], query(root[nx], LR, A * (dep + 1) + B));
		tr[root[nx]].push(pre);
		// printf("root[%d] += %d (query(root[%d], %d) = %d)\n", nx, pre, nx, A * (dep + 1) + B, query(root[nx], LR, A * (dep + 1) + B));
		pre += v; sum += v;
	}
	for(int _ = 1, pre = 0; _ <= top; _++)
	{
		tr[root[nx]].push(pre);
		// printf("root[%d] += %d\n", nx, pre);
		pre += g[nx];
		tr[root[nx]].push(dep * a[k] * A);
		// printf("root[%d] += %d\n", nx, dep * a[k] * A);
	}
	// printf("ins(root[%d], %dx+%d)\n", k, a[k], g[k]);
	ins(root[k], LR, Func(a[k], sum));
	for(int _ = 1; _ <= top; _++) merge(root[k], root[nx], LR);
	g[k] += dep * a[k] * A;
	ckmax(mxg, g[k]);
#undef nx
}

std::vector <pii> vec[N];
char s[2];

void solve()
{
	memset(h, idx = -1, sizeof(h));
	n = read(), A = read(), B = read();
	for(int i = 1; i <= n; i++) a[i] = read();
	for(int i = 1; i <= n; i++)
	{
		int x = read(); readstr(s, 1);
		vec[x].push_back(mkp(s[1], i));
	}
	for(int i = 0; i <= n; i++)
	{
		std::sort(vec[i].begin(), vec[i].end());
		for(; !vec[i].empty(); vec[i].pop_back()) add_edge(i, vec[i].back().se);
	}
	dfs(0, 0);
	for(int i = dfn[0]; i; i--) calc(fdfn[i]);
	// printf("g = %d, mxdep = %d, nidx = %d, qr = %d, mxg = %d\n", g[0], mxdep, nidx, query(root[0], LR, B), mxg);
	int ans = std::min(g[0], query(root[0], LR, B));
	print(ans, '\n');
}

void init()
{
	// debug("%lld\n", inf);
}
char _ED_;
void mian()
{
	debug("%.3f MB\n", abs(&_ST_ - &_ED_) / 1024.0 / 1024);
	init();
	int T = 1;
	for(; T; solve(), T--);
}
#ifdef int
	#undef int
#endif
}

int main()
{

	uvu::mian(); return 0;
}