#include<bits/stdc++.h>

using namespace std;
typedef long long ll;

int main() {
	freopen("game.in", "r", stdin);
	freopen("game.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int n;
	cin >> n;
	vector<int> v(n), a(n);
	int mx = 0;
	ll ans = 0;
	for (int i = 0; i < n; i++) {
		cin >> v[i];
		ans += mx;
		if (v[i] >= mx) {
			a[i] = true;
			mx = v[i];
		}
	}

	cout << ans << endl;
	function<void(int)> dfs = [&dfs, &a, &n](int u) {
		if (u == n) return;
		if (!a[u]) cout << u + 1 << ' ';
		dfs(u + 1);
		if (a[u]) cout << u + 1 << ' ';
	};
	dfs(0);
	return 0;
}
