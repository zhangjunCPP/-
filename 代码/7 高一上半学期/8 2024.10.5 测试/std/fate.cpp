#include <bits/stdc++.h>
#define F(i, j, k) for(int i = (j); i <= (k); ++i)
using namespace std;
const int N = 2e6 + 10;
int n, p[N], nxt[N], h[N], ans[N];
set <int> st;
int main() {
	freopen("fate.in", "r", stdin);
	freopen("fate.out", "w", stdout);
	ios :: sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> n;
	F(i, 1, n * 2) cin >> p[i], nxt[h[p[i]]] = i, h[p[i]] = i;
	F(i, 1, n) st.insert(i * 2 - 1);
	F(i, 1, n * 2) 
		if(nxt[i]) {
			if(st.size() && * st.rbegin() >= nxt[i]) {
				st.erase(st.lower_bound(nxt[i]));
				auto p = st.lower_bound(i);
				if(p == st.end()) return puts(":("), 0;
				st.erase(p), ans[i] = ans[nxt[i]] = 1;
			}
		}
	if (st.size()) return puts(":("), 0;
	F(i, 1, n * 2) cout << (ans[i] ? '(' : ')');
	return 0;
}