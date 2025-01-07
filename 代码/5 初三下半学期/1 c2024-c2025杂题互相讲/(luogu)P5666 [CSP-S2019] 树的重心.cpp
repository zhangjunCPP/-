#include <bits/stdc++.h>

using namespace std;
const int N=3e5+10;
struct node{
	int v,nex;
}a[N*2];
int first[N],cnt;
void add(int u,int v){
	a[++cnt]={v,first[u]};
	first[u]=cnt;
}
int fa[N];
int siz[N];
int son1[N],son2[N];
int son[N][20];
void dfs(int u,int dad){
	fa[u]=dad;
	siz[u]=1;
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(v==dad)continue;
		dfs(v,u);
		siz[u]+=siz[v];
		if(siz[v]>siz[son1[u]])son2[u]=son1[u],son1[u]=v;
		else if(siz[v]>siz[son2[u]])son2[u]=v;
	}
	son[u][0]=son1[u];
	for(int i=1;i<20;i++)son[u][i]=son[son[u][i-1]][i-1];
}



long long ans;
int fa2[N],son3[N],siz2[N];
void dfs2(int u,int dad){
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(v==dad)continue;
		fa2[u]=fa2[v]=0;
		siz2[u]=siz[1]-siz[v];
		if(v==son1[u])son3[u]=son2[u];
		else son3[u]=son1[u];
		if(siz2[dad]>siz2[son3[u]])son3[u]=dad;
		son[u][0]=son3[u];
		for(int j=1;j<20;j++)son[u][j]=son[son[u][j-1]][j-1];
		int now=u;
		for(int j=19;j>=0;j--)if(siz2[son[now][j]]*2>=siz2[u])now=son[now][j];
		ans+=now;
		if(max(siz2[son3[fa2[now]]],siz2[u]-siz2[fa2[now]])*2<=siz2[u])ans+=fa2[now];
		now=v;
		for(int j=19;j>=0;j--)if(siz2[son[now][j]]*2>=siz2[v])now=son[now][j];
		ans+=now;
		if(max(siz2[son3[fa2[now]]],siz2[v]-siz2[fa2[now]])*2<=siz2[v])ans+=fa2[now];
		fa2[u]=v;
		dfs2(v,u);
	}
	fa2[u]=fa[u];
	siz2[u]=siz[u];
	son3[u]=son1[u];
	son[u][0]=son1[u];
	for(int i=1;i<20;i++)son[u][i]=son[son[u][i-1]][i-1];
}
void init(){
	memset(first,0,sizeof first);
	cnt=0;
	memset(son1,0,sizeof son1);
	ans=0;
}
void solve(){
	init();
	int n;
	cin>>n;
	for(int i=1;i<n;i++) {
		int u,v;
		cin>>u>>v;
		add(u,v);
		add(v,u);
	}
	dfs(1,0);
	for(int i=1;i<=n;i++) fa2[i]=fa[i],siz2[i]=siz[i],son3[i]=son1[i];
	dfs2(1,0);
	cout<<ans<<"\n";
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr),cout.tie(nullptr);
	int T;
	cin>>T;
	while(T--)solve();
}