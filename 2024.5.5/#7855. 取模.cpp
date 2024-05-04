#include <bits/stdc++.h>
#define pb emplace_back
#define fst first
#define scd second
#define mkp make_pair
#define mems(a, x) memset((a), (x), sizeof(a))

using namespace std;
typedef long long ll;
typedef double db;
typedef unsigned long long ull;
typedef long double ldb;
typedef pair<ll, ll> pii;

const int maxn = 100100;

ll n, a[maxn];

namespace SGT {
	pii mn[maxn << 2], mx[maxn << 2];
	ll tag[maxn << 2];
	
	inline void pushup(int x) {
		mn[x] = min(mn[x << 1], mn[x << 1 | 1]);
		mx[x] = max(mx[x << 1], mx[x << 1 | 1]);
	}
	
	inline void pushdown(int x) {
		if (!tag[x]) {
			return;
		}
		mn[x << 1].fst += tag[x];
		mn[x << 1 | 1].fst += tag[x];
		mx[x << 1].fst += tag[x];
		mx[x << 1 | 1].fst += tag[x];
		tag[x << 1] += tag[x];
		tag[x << 1 | 1] += tag[x];
		tag[x] = 0;
	}
	
	void build(int rt, int l, int r) {
		if (l == r) {
			mn[rt] = mx[rt] = mkp(a[l], l);
			return;
		}
		int mid = (l + r) >> 1;
		build(rt << 1, l, mid);
		build(rt << 1 | 1, mid + 1, r);
		pushup(rt);
	}
	
	void update(int rt, int l, int r, int x, ll y) {
		if (l == r) {
			mn[rt] = mx[rt] = mkp(y, l);
			return;
		}
		pushdown(rt);
		int mid = (l + r) >> 1;
		(x <= mid) ? update(rt << 1, l, mid, x, y) : update(rt << 1 | 1, mid + 1, r, x, y);
		pushup(rt);
	}
	
	inline void add(ll x) {
		tag[1] += x;
		mn[1].fst += x;
		mx[1].fst += x;
	}
}

void solve() {
	scanf("%lld", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%lld", &a[i]);
	}
	vector<pii> ans;
	ll m = *max_element(a + 1, a + n + 1) + 1;
	ans.pb(2, m);
	for (int i = 1; i <= n; ++i) {
		a[i] += m * (i - 1);
	}
	SGT::build(1, 1, n);
	for (int _ = 0; _ < n; ++_) {
		pii p = SGT::mn[1];
		ans.pb(1, p.fst);
		SGT::add(-p.fst);
		pii q = SGT::mx[1];
		ans.pb(2, q.fst + 1);
		SGT::update(1, 1, n, p.scd, q.fst + 1);
	}
	reverse(ans.begin(), ans.end());
	printf("%d\n", (int)ans.size());
	for (pii p : ans) {
		printf("%lld %lld\n", p.fst, p.scd);
	}
}

int main() {
	int T = 1;
	// scanf("%d", &T);
	while (T--) {
		solve();
	}
	return 0;
}

