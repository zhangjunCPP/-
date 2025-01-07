#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int N=2e6+10;
struct node{
	int v,w,nex;
}a[N];
int first[N],cnt;
void add(int u,int v,int w) {
	a[++cnt]={v,w,first[u]};
	first[u]=cnt;
}
int n;
int dis[N];
int up[N];
void dfs(int u,int dad){
	up[u]=dad;
	for(int i=first[u];i;i=a[i].nex) {
		int v=a[i].v;
		if(v==dad) continue;
		dis[v]=dis[u]+a[i].w;
		dfs(v,u);
	}
}
int f[N];
int fa[N];
int find(int x) {
	if(fa[x]!=x) fa[x]=find(fa[x]);
	return fa[x];
}
int id[N];
bool cmp(const int &x,const int &y) {if(f[x]==f[y]) return x<y;return f[x]<f[y];}
int ans;
int w[N];
void solve(int l) {
	for(int i=1;i<=n;i++) fa[i]=i,w[i]=1;
	for(int i=n,j=n;i>=1;i--){
		while(f[id[j]]-f[id[i]]>l) --w[find(id[j--])];
		ans=max(ans,w[id[i]]);
		fa[id[i]]=up[id[i]];
		w[find(id[i])]+=w[id[i]];
	}
} 
signed main(){
	cin>>n;
	for(int i=1;i<n;i++) {
		int u,v,w;
		cin>>u>>v>>w;
		add(u,v,w);
		add(v,u,w);
	}
	dfs(1,0);
	int s=1;
	for(int i=2;i<=n;i++) if(dis[i]>dis[s]) s=i;
	memset(dis,0,sizeof dis);
	dfs(s,0);
	for(int i=1;i<=n;i++) f[i]=dis[i];
	int t=1;
	for(int i=2;i<=n;i++) if(dis[i]>dis[t]) t=i;
	memset(dis,0,sizeof dis);
	dfs(t,0);
	for(int i=1;i<=n;i++) f[i]=max(f[i],dis[i]);
	int root=1;
	for(int i=2;i<=n;i++) if(f[i]<f[root]) root=i;
	dfs(root,0);
	for(int i=1;i<=n;i++) id[i]=i;
	sort(id+1,id+n+1,cmp);
	int q;
	cin>>q;
	while(q--) {
		int l;
		cin>>l;
		ans=0;
		solve(l);
		cout<<ans<<"\n";
	}
}
