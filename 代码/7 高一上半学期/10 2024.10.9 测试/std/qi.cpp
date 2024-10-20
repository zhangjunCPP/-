#include <bits/stdc++.h>

int main() {
	
	
	std::cin.tie(nullptr)->sync_with_stdio(false);
	int n, m;
	std::cin >> n >> m;
	
	std::vector<std::vector<std::pair<int, int>>> g(n);
	for (int i = 0; i < m; i++) {
		int op, u, v;
		std::cin >> op >> u >> v;
		u--, v--;
		g[u].emplace_back(v, op);
		g[v].emplace_back(u, op);
	}

	std::vector<int> col(n, -1);
	std::vector<std::array<std::vector<int>, 2>> nodes;
	auto dfs = [&](auto &&self, int u) -> void {
		nodes.back()[col[u]].push_back(u);
		for (auto e : g[u]) {
			if (col[e.first] == -1) {
				col[e.first] = col[u] ^ e.second;
				self(self, e.first);
			} else if (col[e.first] != col[u] ^ e.second) {
				std::cout << "-1\n";
				std::exit(0);
			}
		}
	};
	int base = 0;
	std::vector<int> dif(n + 1);
	for (int i = 0; i < n; i++) {
		if (col[i] == -1) {
			nodes.emplace_back();
			col[i] = 0;
			dfs(dfs, i);
			if (nodes.back()[0].size() > nodes.back()[1].size()) {
				std::swap(nodes.back()[0], nodes.back()[1]);
			}
			base += nodes.back()[0].size();
			dif[nodes.back()[1].size() - nodes.back()[0].size()]++;
		}
	}

	std::vector<std::tuple<std::bitset<(int)1e6 + 1>, int, int>> f(1);
	std::get<0>(f[0]).set(base);
	auto add = [&](int val, int cnt) {
		auto &pre = std::get<0>(f.back());
		f.emplace_back(pre | pre << (val * cnt), val, cnt);
	};
	for (int i = 1; i <= n; i++) {
		int cur = 1;
		while (cur <= dif[i]) {
			add(i, cur);
			dif[i] -= cur;
			cur *= 2;
		}
		if (dif[i] != 0) add(i, dif[i]);
	}

	int best = n + 1, pos = -1;
	for (int i = 0; i <= n; i++) {
		if (std::get<0>(f.back()).test(i)) {
			if (std::max(i, n - i) < best) {
				best = std::max(i, n - i);
				pos = i;
			}
		}
	}
	int total = 2;
	while (2 + (total - 1) * (total - 2) < best) total++;
	std::cout << total << '\n';

	std::vector<int> use(n + 1);
	for (int i = f.size() - 1; i; i--) {
		if (!std::get<0>(f[i - 1]).test(pos)) {
			use[std::get<1>(f[i])] += std::get<2>(f[i]);
			pos -= std::get<1>(f[i]) * std::get<2>(f[i]);
		}
	}

	auto isprime = [&](int x) {
		for (int i = 2; i * i <= x; i++) {
			if (x % i == 0) return false;
		}
		return true;
	};
	std::vector<int> num = {0, 1};
	int cur = 2;
	while (num.size() < total) {
		while (!isprime(cur)) cur++;
		num.push_back(cur);
		cur++;
	}

	int ord[2] = {0, 0};
	std::vector<std::tuple<int, int, int>> ans(n);
	for (int i = 0; i < nodes.size(); i++) {
		if (use[nodes[i][1].size() - nodes[i][0].size()]) {
			use[nodes[i][1].size() - nodes[i][0].size()]--;
			std::swap(nodes[i][0], nodes[i][1]);
		}
		for (int j = 0; j < 2; j++) {
			for (int k : nodes[i][j]) {
				if (ord[j] == 0) {
					ans[k] = std::make_tuple(j, 1, 0);
				} else if (ord[j] == 1) {
					ans[k] = std::make_tuple(j, 1, 1);
				} else {
					int x = ord[j] - 2;
					int fir = x / (total - 2), sec = x % (total - 2);
					if (sec >= fir) sec++;
					ans[k] = std::make_tuple(j, num[fir + 1], num[sec + 1]);
				}
				ord[j]++;
			}
		}
	}

	for (int i = 0; i < n; i++) {
		if (std::get<0>(ans[i]) == 0) {
			std::cout << std::get<1>(ans[i]) << " 0 " << std::get<2>(ans[i]) << '\n';
		} else {
			std::cout << "0 " << std::get<1>(ans[i]) << ' ' << std::get<2>(ans[i]) << '\n';
		}
	}
}