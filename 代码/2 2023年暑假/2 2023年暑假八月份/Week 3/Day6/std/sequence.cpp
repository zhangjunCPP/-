#include <bits/stdc++.h>
using namespace std;
const int p = 998244353;
const int maxn = 255;
int f[2][maxn][maxn][maxn][2][2];
int n, k;

int md(int x) {
	return x > p ? x - p : x;
}

int main() {
	freopen("sequence.in","r",stdin);
	freopen("sequence.out","w",stdout);
	
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n >> k;
	f[1][1][0][0][1][0] = 1;
	f[1][1][0][0][0][1] = 1;
	int now = 0, lst = 1;
	for (int i = 1; i < n; ++i) {
		for (int j = 1; j <= k; ++j) {
			for (int u = j; u >= 0; --u) {
				for (int v = j; v >= 0; --v) {
					if (j * 2 - u > k && j * 2 - v > k)
						break;
					if (j * 2 + 1 <= k)
						f[now][j * 2 + 1][j][v][1][1] = (f[now][j * 2 + 1][j][v][1][1] + f[lst][j][u][v][0][1]);
					if (j * 2 - u <= k)
						f[now][j * 2 - u][j][v][1][1] = (f[now][j * 2 - u][j][v][1][1] + f[lst][j][u][v][1][1]);
					if (j * 2 - u <= k)
						f[now][j * 2 - u][j][v][1][0] = (f[now][j * 2 - u][j][v][1][0] + f[lst][j][u][v][1][0]);
					if (j * 2 + 1 <= k)
						f[now][j * 2 + 1][u][j][1][1] = (f[now][j * 2 + 1][u][j][1][1] + f[lst][j][u][v][1][0]);
					if (j * 2 - v <= k)
						f[now][j * 2 - v][u][j][1][1] = (f[now][j * 2 - v][u][j][1][1] + f[lst][j][u][v][1][1]);
					if (j * 2 - v <= k)
						f[now][j * 2 - v][u][j][0][1] = (f[now][j * 2 - v][u][j][0][1] + f[lst][j][u][v][0][1]);
				}
			}
		}
		for (int j = 1; j <= k; ++j)
			for (int u = j; u >= 0; --u)
				for (int v = j; v >= 0; --v)
					f[lst][j][u][v][0][1] = f[lst][j][u][v][1][0] = f[lst][j][u][v][1][1] = 0;
		swap(now, lst);
	}
	for (int x = 1; x <= k; ++x) {
		int ans = 0;
		for (int i = 0; i <= x; ++i)
			for (int j = 0; j <= x; ++j) {
				ans = (ans + f[lst][x][i][j][0][0]);
				ans = (ans + f[lst][x][i][j][1][0]);
				ans = (ans + f[lst][x][i][j][0][1]);
				ans = (ans + f[lst][x][i][j][1][1]);
			}
		cout << ans << ' ';
	}
	cout << '\n';
}