#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e6+10;
int v[N],w[N];
int deg[N];
int f[N],g[N];
int ans;
int solve(int rt){
	int tmp=rt;
	int len=w[rt];
	int Max1=f[rt],Max2=f[rt];
	int ans1=g[rt],ans2=-1e18;
	rt=v[rt];
	while(rt!=tmp){
		deg[rt]=0;
		ans1=max({ans1,g[rt],f[rt]+len+Max1});
		ans2=max(ans2,f[rt]-len+Max2);
		Max1=max(Max1,f[rt]-len);
		Max2=max(Max2,f[rt]+len);
		len+=w[rt];
		rt=v[rt];
	}
	return max(ans1,ans2+len);
}
signed main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>v[i]>>w[i],deg[v[i]]++;
	queue<int> q;
	for(int i=1;i<=n;i++)if(!deg[i])q.push(i);
	while(!q.empty()){
		int u=q.front();
		q.pop();
		int tmp=f[u]+w[u];
		g[v[u]]=max({g[v[u]],f[v[u]]+tmp,g[u]});
		f[v[u]]=max(f[v[u]],tmp);
		deg[v[u]]--;
		if(!deg[v[u]])q.push(v[u]);
	}
	for(int i=1;i<=n;i++)if(deg[i])ans+=solve(i);
	cout<<ans;
}