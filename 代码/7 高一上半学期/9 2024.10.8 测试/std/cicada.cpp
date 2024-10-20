#include <bits/stdc++.h>
using namespace std;

const int N = 100010;

using i64 = long long;

i64 n, k, ans, a[N], b[N], d[N], f[N];

inline void ins(i64 x) {
	for (int i = 60; i >= 0; i--) {
		if ((x >> i) & 1) {
			if (f[i]) x ^= f[i];
			else { f[i] = x; break; }
		}
	}
}
inline auto get(i64 x) {
	for (int i = 60; i >= 30; i--) if (((x >> i) & 1) == 1) x ^= f[i];
	for (int i = 29; i >=  0; i--) if (((x >> i) & 1) == 0) x ^= f[i];
	return (x >= (1ll << 30) ? -1 : x);
}

int main() {
	
	
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n >> k, ans = -1;
	for (int i = 1; i <= n; i++) {
		cin >> a[i] >> b[i];
	}
	bool flag = 0;
	for (int i = 1; i <= n; i++) {
		i64 x = a[i];
		for (int j = 60; j >= 0; j--) {
			if ((x >> j) & 1) {
				if (f[j]) x ^= f[j];
				else { f[j] = x; break; }
			}
		}
		if (x <= k) flag = 1;
	}
	if (flag == 0) {
		cout << -1 << "\n";
		return 0;
	}
	fill(f, f + 60 + 1, 0);
	for (int i = 29; i >= 0; i--) {
		if ((k >> i) & 1) {
			for (int j = 1; j <= n; j++)
				ins(((a[j] >> i) << i << 30) | b[j]);
			ans = max(ans, get(((k >> i) ^ 1) << i << 30));
			fill(f, f + 60 + 1, 0);
		}
	}
	for (int j = 1; j <= n; j++) {
		ins((a[j] << 30) | b[j]);
	}
	ans = max(ans, get(k << 30));
	cout << ans << "\n";
	return 0;
}