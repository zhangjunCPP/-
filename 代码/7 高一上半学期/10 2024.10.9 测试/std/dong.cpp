#include <bits/stdc++.h>

constexpr int inf = 2.1e9;

class SegmentTree {
	struct node {
		int val, tag;
		node() : val(inf), tag(inf) {}
		void apply(int x) {
			val = std::min(val, x);
			tag = std::min(tag, x);
		}
	};
	int n;
	std::vector<node> t;

	void pushup(int id) {
		t[id].val = std::min(t[id << 1].val, t[id << 1 | 1].val);
	}
	void pushdown(int id) {
		if (t[id].tag == inf) return;
		t[id << 1].apply(t[id].tag);
		t[id << 1 | 1].apply(t[id].tag);
		t[id].tag = inf;
	}

	void checkmin(int id, int le, int ri, int l, int r, int v) {
		if (l <= le && ri <= r) {
			t[id].apply(v);
		} else {
			pushdown(id);
			int mid = (le + ri) / 2;
			if (l < mid) checkmin(id << 1, le, mid, l, r, v);
			if (r > mid) checkmin(id << 1 | 1, mid, ri, l, r, v);
			pushup(id);
		}
	}
	void assign(int id, int le, int ri, int p, int v) {
		if (le + 1 == ri) {
			t[id].val = v;
		} else {
			pushdown(id);
			int mid = (le + ri) / 2;
			if (p < mid) assign(id << 1, le, mid, p, v);
			else assign(id << 1 | 1, mid, ri, p, v);
			pushup(id);
		}
	}
	int query(int id, int le, int ri, int p) {
		if (le + 1 == ri) {
			return t[id].val;
		} else {
			pushdown(id);
			int mid = (le + ri) / 2;
			if (p < mid) return query(id << 1, le, mid, p);
			else return query(id << 1 | 1, mid, ri, p);
		}
	}

public:
	SegmentTree(int x) : n(x), t(x * 4) {}
	void checkmin(int l, int r, int v) { checkmin(1, 0, n, l, r, v); }
	void assign(int p, int v) { assign(1, 0, n, p, v); }
	int query(int p) { return query(1, 0, n, p); }
};

int main() {
	
	
	std::cin.tie(nullptr)->sync_with_stdio(false);
	int n, m;
	std::cin >> n >> m;

	std::vector<std::tuple<int, int, int>> edge(m);
	for (int i = 0; i < m; i++) {
		int u, v, w;
		std::cin >> u >> v >> w;
		u--, v--;
		edge[i] = std::make_tuple(w, u, v);
	}
	std::sort(edge.begin(), edge.end());
	
	std::vector<bool> inmst(m);
	std::vector<std::vector<std::pair<int, int>>> g(n);
	{
		std::vector<int> dsu(n), siz(n, 1);
		std::iota(dsu.begin(), dsu.end(), 0);
		auto find = [&](int u) {
			auto find_helper = [&](auto &&self, int u) {
				if (u == dsu[u]) return u;
				return dsu[u] = self(self, dsu[u]);
			};
			return find_helper(find_helper, u); 
		};
		auto merge = [&](int u, int v) {
			u = find(u), v = find(v);
			if (u == v) return false;
			if (siz[u] < siz[v]) std::swap(u, v);
			dsu[v] = u;
			siz[u] += siz[v];
			return true;
		};

		for (int i = 0; i < m; i++) {
			int u = std::get<1>(edge[i]), v = std::get<2>(edge[i]), w = std::get<0>(edge[i]);
			if (merge(u, v)) {
				inmst[i] = true;
				g[u].emplace_back(v, w), g[v].emplace_back(u, w);
			}
		}
	}

	std::vector<int> le(n), ri(n), par(n), dep(n), val(n);
	int timer = 0;
	auto dfs = [&](auto &&self, int u) -> void {
		le[u] = timer++;
		for (auto e : g[u]) {
			int v = e.first;
			if (v != par[u]) {
				par[v] = u;
				dep[v] = dep[u] + 1;
				val[v] = e.second;
				self(self, v);
			}
		}
		ri[u] = timer;
	};
	val[0] = inf;
	dfs(dfs, 0);

	std::vector<int> dsu(n), siz(n, 1), high(n);
	std::iota(dsu.begin(), dsu.end(), 0);
	std::iota(high.begin(), high.end(), 0);
	auto find = [&](int u) {
		auto find_helper = [&](auto &&self, int u) {
			if (u == dsu[u]) return u;
			return dsu[u] = self(self, dsu[u]);
		};
		return find_helper(find_helper, u); 
	};
	auto merge = [&](int u, int v) {
		u = find(u), v = find(v);
		if (u == v) return false;
		if (siz[u] < siz[v]) std::swap(u, v);
		dsu[v] = u;
		siz[u] += siz[v];
		if (dep[high[v]] < dep[high[u]]) high[u] = high[v];
		val[u] = std::min(val[u], val[v]);
		return true;
	};

	SegmentTree mn(n), ans(n);
	
	std::vector<bool> vis(n);
	vis[0] = true;
	auto dfsnew = [&](auto &&self, int u, int cur) -> void {
		vis[u] = true;
		ans.assign(le[u], cur + mn.query(le[u]));
		for (auto e : g[u]) {
			int v = e.first, w = e.second;
			if (dep[v] > dep[u] && w <= cur) self(self, v, cur);
		}
	};

	for (int i = 0; i < m; i++) {
		int u = std::get<1>(edge[i]), v = std::get<2>(edge[i]), w = std::get<0>(edge[i]);
		if (inmst[i]) {
			if (dep[u] > dep[v]) std::swap(u, v);
			mn.checkmin(le[v], ri[v], w);
			if (vis[u] && !vis[v]) dfsnew(dfsnew, v, w);
		} else {
			while (true) {
				u = high[find(u)], v = high[find(v)];
				if (u == v) break;
				if (dep[u] > dep[v]) std::swap(u, v);
				merge(par[v], v);
			}
			int cur = val[find(u)];
			mn.checkmin(le[u], ri[u], cur);
			ans.checkmin(le[u], ri[u], cur + w);
		}
	}

	for (int i = 1; i < n; i++) std::cout << ans.query(le[i]) << '\n';
}