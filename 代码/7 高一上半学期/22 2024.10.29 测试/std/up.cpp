#include <bits/stdc++.h>
#define MAXM ((int) 1e5)
using namespace std;
typedef pair<int, int> pii;

int n, m;
long long ans;

// 缩点后图上的一个节点
struct Vert {
	// spec == true：特殊点；spec == false：连续点
	bool spec;
	// 对于特殊点，L = R = 点的编号；对于连续点，L 是所代表区间的左端点，R 是右端点
	int L, R;
	// 只对特殊点有用，记录与该特殊点相邻的所有特殊边，key 是终点编号，value 是权值
	unordered_map<int, int> e;
};
vector<Vert> V;

int root[MAXM * 4 + 10], pre[MAXM * 4 + 10], nxt[MAXM * 4 + 10];

int findroot(int x) {
	if (root[x] != x) root[x] = findroot(root[x]);
	return root[x];
}

void solve() {
	scanf("%d%d", &n, &m);
	map<int, vector<pii>> e;
	for (int i = 1; i <= m; i++) {
		int x, y, z; scanf("%d%d%d", &x, &y, &z);
		e[x].push_back(pii(y, z)); e[y].push_back(pii(x, z));
	}

	// 用特殊点把一般点分成一段段区间
	V.clear();
	int last = 0;
	for (auto &entry : e) {
		int pos = entry.first;
		if (last + 1 != pos) V.push_back(Vert{false, last + 1, pos - 1, {}});
		V.push_back(Vert{true, pos, pos, {}});
		last = pos;
	}
	if (last != n) V.push_back(Vert{false, last + 1, n, {}});
	n = V.size();

	// 把原图的点编号转换成缩点后图的点编号
	unordered_map<int, int> mp;
	for (int i = 0; i < n; i++) if (V[i].spec) mp[V[i].L] = i;
	auto it = e.begin();
	for (auto &v : V) if (v.spec) {
		for (auto &[fn, val] : it->second) v.e[mp[fn]] = val;
		it++;
	}

	// 把每个连续点内部连起来
	ans = 0;
	for (auto &v : V) if (!v.spec) ans += v.R - v.L;

	for (int i = 0; i < n; i++) root[i] = i;
	int comp = n;
	// boruvka
	while (comp > 1) {
		// pre[i] 表示点 i 左边最近的，且和它不在同一连通块的点是哪个
		pre[0] = -1;
		for (int i = 1; i < n; i++) pre[i] = (findroot(i - 1) == findroot(i) ? pre[i - 1] : i - 1);
		// nxt[i] 表示点 i 右边最近的，且和它不在同一连通块的点是哪个
		nxt[n - 1] = n;
		for (int i = n - 2; i >= 0; i--) nxt[i] = (findroot(i + 1) == findroot(i) ? nxt[i + 1] : i + 1);

		vector<int> best(n, -1), len(n, 2e9);
		for (int i = 0; i < n; i++) {
			int r = findroot(i);
			if (V[i].spec) {
				// 考虑与该特殊点相连的所有特殊边
				// 特殊边一共 m 条，所以每一轮 boruvka 这一段总共执行 m 次
				for (auto &[fn, val] : V[i].e)
					if (r != findroot(fn) && val < len[r]) best[r] = fn, len[r] = val;
				// 寻找左边第一个和它没有连特殊边，且不在同一连通块内的点
				//
				// 简单分析一下这段代码的复杂度。找的时候共有 3 种情况：
				//   1. 碰到有特殊边相连的点，直接继续往前考虑一个点。
				//   2. 碰到同一连通块内的点，通过 pre[j] 直接跳到前一个不在同一连通块内的点。
				//   3. 找到了，直接退出。
				//
				// 情况 1 可能会跳到情况 1, 2, 3 的任意一种。情况 2 只会跳到情况 1 和 3。
				// 因为情况 1 每轮 boruvka 最多出现 m 次，而情况 2 只能从情况 1 跳过去，
				// 因此情况 2 每轮也最多出现 m 次。
				// 所以这一段代码的复杂度也是每轮 O(m) 的。
				for (int j = pre[i]; j >= 0; ) {
					// 同一连通块内的点，通过 pre[j] 直接跳
					if (r == findroot(j)) j = pre[j];
					// 和 j 有特殊边相连，不能考虑这个点
					else if (V[i].e.count(j)) j--;
					else {
						// 找到了
						int val = V[i].L - V[j].R;
						if (val < len[r]) best[r] = j, len[r] = val;
						break;
					}
				}
				// 寻找右边第一个和它没有连特殊边，且不在同一连通块内的点，与上面类似的逻辑
				for (int j = nxt[i]; j < n; ) {
					if (r == findroot(j)) j = nxt[j];
					else if (V[i].e.count(j)) j++;
					else {
						int val = V[j].L - V[i].R;
						if (val < len[r]) best[r] = j, len[r] = val;
						break;
					}
				}
			} else {
				// 连续点，考虑 pre[i] 和 nxt[i] 哪个更好即可
				int j = pre[i];
				if (j >= 0) {
					int val = V[i].L - V[j].R;
					if (val < len[r]) best[r] = j, len[r] = val;
				}
				j = nxt[i];
				if (j < n) {
					int val = V[j].L - V[i].R;
					if (val < len[r]) best[r] = j, len[r] = val;
				}
			}
		}

		// 把这一轮我们选上的边连接一下
		for (int i = 0; i < n; i++) if (best[i] >= 0) {
			int x = findroot(i), y = findroot(best[i]);
			if (x == y) continue;
			root[x] = y;
			ans += len[i];
			comp--;
		}
	}
	printf("%lld\n", ans);
}

int main() {
	int tcase; scanf("%d", &tcase);
	while (tcase--) solve();
	return 0;
}