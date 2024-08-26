#include <bits/stdc++.h>
using namespace std;
const int N=2e5+10;
struct node {
	int v,nex;
}a[N];
int first[N],cnt;
void add(int u,int v) {
	a[++cnt]={v,first[u]};
	first[u]=cnt;
}
int siz[N],fa[N],dep[N],son[N];
void dfs1(int u,int dad){
	fa[u]=dad;
	dep[u]=dep[dad]+1;
	siz[u]=1;
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(v==dad)continue;
		dfs1(v,u);
		siz[u]+=siz[v];
		if(siz[v]>siz[son[u]])son[u]=v;
	}
}
int top[N];
void dfs2(int u){
	if(son[u]){
		int v=son[u];
		top[v]=top[u];
		dfs2(v);
	}
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(top[v])continue;
		top[v]=v;
		dfs2(v);
	}
}
int lca(int x,int y){
	int fx=top[x],fy=top[y];
	while(fx!=fy){
		if(dep[fx]<dep[fy])swap(x,y),swap(fx,fy);
		x=fa[fx];
		fx=top[x];
	}
	if(dep[x]>dep[y])swap(x,y);
	return x;
}
int dis(int x,int y) {return dep[x]+dep[y]-2*dep[lca(x,y)];}
struct node2 {
	int val,time;
	bool opt;
}city[N];
int main() {
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	freopen("travel.in","r",stdin);
	freopen("travel.out","w",stdout);
	int n,q;
	cin>>n>>q;
	for(int i=1;i<=n;i++) {
		cin>>city[i].val;
		city[i].time=city[i].opt=0;
	}
	for(int i=1;i<n;i++) {
		int u,v;
		cin>>u>>v;
		add(u,v);add(v,u);
	}
	dfs1(1,0);
	top[1]=1;
	dfs2(1);
	// for(int i=1;i<=n;i++)cout<<dis(1,i)<<" ";
	// cout<<"\n";
	while(q--) {
		int opt,t,x;
		cin>>opt>>t>>x;
		if(opt==1) {
			city[x].val-=t-city[x].time;
			city[x].val=max(0,city[x].val);
			city[x].opt=true;
			city[x].time=t;
		}
		else if(opt==2){
			city[x].opt=false;
			city[x].time=t;
		}
		else {
			int ans=city[x].opt?city[x].val:city[x].val-(t-city[x].time);
			ans=max(ans,0);
			for(int i=1;i<=n;i++) {
				if(city[i].opt)ans=max(ans,city[i].val);
				else ans=max(ans,max(city[i].val-(t-city[i].time)-dis(x,i),0));
				// if(city[i].opt)cout<<city[i].val<<" ";
				// else cout<<max(city[i].val-(t-city[i].time)-dis(x,i),0)<<" ";
			}
			// cout<<"      ans=";
			cout<<ans<<"\n";
		}
	}
}