#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAX_N = 100000 + 5;
const int MAX_M = 1000000 + 5;

int N, M, a[MAX_N], b[MAX_N];
int simul[MAX_N << 1], tot;
char vis[MAX_M], cardTy[MAX_N];
int lastpos[MAX_M], endpos[MAX_N << 1], ans[MAX_N];

int main() {
	
	freopen("marketplace.in","r",stdin);
	freopen("marketplace.out","w",stdout);
	scanf("%d%d", &N, &M);
	for (int i = 1; i <= N; i ++) {
		scanf("%d%d", a + i, b + i);
		if (tot == i - 1) {
			if (!vis[a[i]]) {
				vis[a[i]] = 1;
				simul[++ tot] = a[i];
			}else if (!vis[b[i]]) {
				vis[b[i]] = 1;
				simul[++ tot] = b[i];
				cardTy[i] = 1;
			}
		}
	}
	if (tot == N) {
		for (int i = 1; i <= N; i ++) {
			if (cardTy[i] || vis[b[i]]) {
				break;
			}
			vis[b[i]] = 1;
			simul[++ tot] = b[i];
		}
	}
	fprintf(stderr, "N = %d, tot = %d\n", N, tot);
	for (int i = tot; i > 0; i --) {
		lastpos[simul[i]] = i;
		if (i > N || cardTy[i] || vis[b[i]]) {
			ans[i > N ? i - N : i] ++;
			endpos[i] = i > N ? i - N : i;
		}else {
			endpos[i] = endpos[lastpos[b[i]]];
			int p = endpos[i];
			ans[p] ++;
		}
		vis[simul[i]] = 0;
	}
	ans[tot % N + 1] += ans[0] + M - tot;
	for (int i = 1; i <= N; i ++) printf("%d\n", ans[i]);
	return 0;
}
