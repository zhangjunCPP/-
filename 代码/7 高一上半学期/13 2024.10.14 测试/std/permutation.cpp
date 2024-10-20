#include <cmath>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <queue>
#define N 400005
using namespace std;
typedef long long ll;

int T, n, m, dfid[N], in[N], tot, ans[N], res[N];
vector <int> to[N], num[N];
bool vst[N];
struct Pnt {
	int l, r, id;
	bool operator< (const Pnt &x) const { return r>x.r; }
} p[N];
priority_queue <Pnt> q;

void dfs (int u)
{
	if (vst[u]) { return; }
	vst[u]=1;
	for (int i=0; i<(int)to[u].size(); i++) {
		int v=to[u][i]; dfs(v);
	}
	dfid[++tot]=u;
}

void clr ()
{
	tot=0;
	while (!q.empty()) { q.pop(); }
	for (int i=1; i<=n+1; i++) { to[i].clear(); num[i].clear(); in[i]=0; vst[i]=0; }
}

int main ()
{

	scanf("%d %d", &n, &m);
	clr();
	for (int i=1; i<=n; i++) {
		scanf("%d", &p[i].l);
		if (!p[i].l) { p[i]=(Pnt){ 1, n, 0 }; }
		else { p[i].r=p[i].l; }
	}

	for (int i=1; i<=m; i++) {
		int u, v; scanf("%d %d", &u, &v);
		to[u].push_back(v); in[v]++;
	}

	for (int u=1; u<=n; u++) if (!in[u]) { dfs(u); }

	for (int i=tot; i>=1; i--) {
		int u=dfid[i];
		for (int j=0; j<(int)to[u].size(); j++) {
			int v=to[u][j];
			p[v].l=max(p[v].l, p[u].l+1);
		}
	}
	for (int i=1; i<=tot; i++) {
		int u=dfid[i];
		for (int j=0; j<(int)to[u].size(); j++) {
			int v=to[u][j];
			p[u].r=min(p[u].r, p[v].r-1);
		}
	}
	for (int i=1; i<=n; i++) { p[i].id=i; num[p[i].l].push_back(i); }
	
	int cur=1;
	for (int i=0; i<(int)num[cur].size(); i++) { q.push(p[num[cur][i]]); }

	while (!q.empty()) {
		int id=q.top().id; q.pop();
		if (p[id].r<cur) { break; }
		res[cur]=id; cur++;
		for (int i=0; i<(int)num[cur].size(); i++) { q.push(p[num[cur][i]]); }
	}
	if (cur!=n+1) { printf("-1\n"); }
	else {
		for (int i=1; i<=n; i++) { ans[res[i]]=i; }
		for (int i=1; i<=n; i++) { printf("%d ", ans[i]); } printf("\n");
	}

	return 0;
}