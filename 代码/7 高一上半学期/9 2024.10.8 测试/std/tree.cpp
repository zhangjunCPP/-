/*
	! 如果没有天赋，那就一直重复
	! Created: 2024/08/02 16:24:49
*/
#include <bits/stdc++.h>
using namespace std;

#define x first
#define y second
// #define int long long
#define mp(x, y) make_pair(x, y)
#define eb(...) emplace_back(__VA_ARGS__)
#define fro(i, x, y) for (int i = (x); i <= (y); i++)
#define pre(i, x, y) for (int i = (x); i >= (y); i--)
inline void JYFILE19();

using i64 = long long;
using PII = pair<int, int>;

bool ST;
const int N = 1e6 + 10;
const int mod = 998244353;

int n, m, ct, p[N], head[N];
vector<int> ji;
vector<int> ou;
struct edge {
	int to, nxt;
} e[N << 1];

inline void add(int x, int y) {
	e[++ct] = {y, head[x]}, head[x] = ct;
	e[++ct] = {x, head[y]}, head[y] = ct;
}
inline void dfs(int x, int f, int d) {
	if (d == 0) ji.eb(x);
	if (d == 1) ou.eb(x);
	for (int i = head[x]; i; i = e[i].nxt) {
		if (e[i].to == f) continue;
		dfs(e[i].to, x, d ^ 1);
	}
}
inline void sol() {
	cin >> n;
	fro(i, 1, n - 1) {
		int x, y;
		cin >> x >> y, add(x, y);
	}
	dfs(1, 0, 0);
	int o1 = (n + 2) / 3;
	int o2 = (n + 1) / 3;
	int o3 = n / 3;
	if (ji.size() <= o3) {
		for (auto i : ji) p[i] = 3, o3--;
		for (auto i : ou) if (o3) p[i] = 3, o3--; else if (o1) p[i] = 1, o1--; else p[i] = 2, o2--;
	} else if (ou.size() <= o3) {
		for (auto i : ou) p[i] = 3, o3--;
		for (auto i : ji) if (o3) p[i] = 3, o3--; else if (o1) p[i] = 1, o1--; else p[i] = 2, o2--;
	} else {
		for (auto i : ji) p[i] = (o1 ? 1 : 3), (p[i] == 1 ? o1-- : o3--);
		for (auto i : ou) p[i] = (o2 ? 2 : 3), (p[i] == 2 ? o2-- : o3--);
	}
	cout << "Yes\n";
	fro(i, 1, n) {
		if (p[i] == 1) cout << o1 * 3 + 1, o1++;
		if (p[i] == 2) cout << o2 * 3 + 2, o2++;
		if (p[i] == 3) cout << o3 * 3 + 3, o3++;
		if (i != n) cout << " ";
	}
	cout << "\n";
	ct = 0;
	ji.clear();
	ou.clear();
	fro(i, 1, n) p[i] = head[i] = 0;
}

signed main() {
	JYFILE19();
	int t;
	cin >> t;
	while (t--) sol();
	return 0;
}

bool ED;
inline void JYFILE19() {
	
	
	srand(random_device{}());
	ios::sync_with_stdio(0), cin.tie(0);
	double MIB = fabs((&ED - &ST) / 1048576.), LIM = 32;
	cerr << "MEMORY: " << MIB << endl, assert(MIB <= LIM);
}