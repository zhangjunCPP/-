#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long
const int N = 2e5+5;
int n,m,c,tot,top,dcc,siz[N],cnt[N],rt[N],sum[N],dfn[N],bel[N],stk[N],low[N];
vector<int> e[N],g[N],d[N];
bitset<50005> dp[2][2];
int find(int u){
	if(u == rt[u]) return u;
	return rt[u] = find(rt[u]);
}
void merge(int u,int v){
	u = find(u),v = find(v);
	if(u == v) return ;
	sum[v] += sum[u],rt[u] = v;
}
void clear(){
	tot = dcc = 0;
	for(int i=1;i<=n;i++) rt[i] = i,siz[i] = sum[i] = 1,dfn[i] = low[i] = bel[i] = 0,e[i].clear(),g[i].clear(),d[i].clear();
	dp[0][0].reset(),dp[1][0].reset(),dp[1][1].reset(),dp[0][1].reset();
}
void tarjan(int u,int fa){
	dfn[u] = low[u] = ++tot,stk[++top] = u;
	for(int v:e[u]){
		if(v == fa) continue;
		if(!dfn[v]){
			tarjan(v,u);
			low[u] = min(low[u],low[v]);
		}else{
			low[u] = min(low[u],dfn[v]);
		}
	}
	if(dfn[u] == low[u]){
		dcc++,cnt[dcc] = 0;
		while(1){
			int v = stk[top--];
			bel[v] = dcc,cnt[dcc]++;
			if(v == u) break;
		}
	}
}
void get_siz(int u,int fa,int rt){
	siz[u] = cnt[u];
	for(int v:g[u]){
		if(v==fa) continue;
		get_siz(v,u,rt);
		siz[u] += siz[v];
		d[rt].pb(siz[v]),d[rt].pb(sum[rt]-siz[v]);
	}
}
void solve(){
	cin >> n >> m >> c;
	clear();
	for(int i=1,u,v;i<=m;i++){
		cin >> u >> v;
		e[u].pb(v),e[v].pb(u);
		merge(u,v);
	}
	vector<int> vec;int k = 0;
	for(int i=1;i<=n;i++) if(find(i)==i) tarjan(i,0),vec.pb(i),k++;
	if(dcc==1){
		cout << -1 << '\n';
		return ;
	}
	for(int u=1;u<=n;u++){
		for(int v:e[u]){
			if(bel[u] == bel[v]) continue;
			g[bel[u]].pb(bel[v]);
		}
	}
	for(int x:vec) get_siz(bel[x],0,x);
	dp[0][0].set(0);
	for(int i=1;i<=k;i++){
		int now = i&1,rt = vec[i-1];
		dp[now][0] = dp[now^1][0],dp[now][1] = dp[now^1][1];
		dp[now][0] |= (dp[now^1][0]<<sum[rt]),dp[now][1] |= (dp[now^1][1]<<sum[rt]);
		for(int sz:d[rt]) dp[now][1] |= (dp[now^1][0]<<sz);
	}
	ll ans = 1e18;
	for(int i=0;i<=n/2;i++){
		if(dp[k&1][0][i] || dp[k&1][1][i]){
			ans = min(ans,1ll*i*i+1ll*(n-i)*(n-i)+1ll*(k-1)*c);
		}
	}
	cout << ans << '\n';
}
int main(){
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);
	solve();
	return 0;
}