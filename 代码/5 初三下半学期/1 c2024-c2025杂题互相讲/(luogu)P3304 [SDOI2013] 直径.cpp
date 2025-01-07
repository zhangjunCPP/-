#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=4e5+10;
struct node{
	int v,w,nex;
}a[N*2];
int first[N],cnt;
void add(int u,int v,int w){
	a[++cnt]={v,w,first[u]};
	first[u]=cnt;
}
int dis[N];
int val[N];
int fa[N];
void dfs(int u,int dad){
	fa[u]=dad;
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(v==dad) continue;
		val[v]=a[i].w;
		dis[v]=dis[u]+a[i].w;
		dfs(v,u);
	}
}
int l[N],r[N];
bool vis[N];
int len[N];
void solve(int u,int dad){
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(v==dad||fa[u]==v||vis[v]) continue;
		solve(v,u);
		len[u]=max(len[u],len[v]+a[i].w);
	}
}
int ans[N],tot;
signed main(){
	int n;
	cin>>n;
	for(int i=1;i<n;i++) {
		int u,v,w;
		cin>>u>>v>>w;
		add(u,v,w);
		add(v,u,w);
	}
	dfs(1,0);
	int rt1=1;
	for(int i=2;i<=n;i++) if(dis[i]>dis[rt1]) rt1=i;
	dis[rt1]=0;
	dfs(rt1,0);
	int rt2=1;
	for(int i=2;i<=n;i++) if(dis[i]>dis[rt2]) rt2=i;
	int Ans=dis[rt2];
	cout<<Ans<<"\n";

	int tmp1=0,tmp2=dis[rt2];
	for(;;tmp1+=val[rt2],tmp2-=val[rt2],rt2=fa[rt2]){
		ans[++tot]=rt2;
		l[rt2]=tmp1,r[rt2]=tmp2;
		vis[rt2]=true;
		solve(rt2,0);
		if(rt2==rt1) break;
	}
	int L,R;
	for(L=1;L<=tot;L++) if(len[ans[L]]+l[ans[L]]==Ans) break;
	if(L>tot) L--;
	for(R=tot;R;R--) if(len[ans[R]]+r[ans[R]]==Ans) break;
	if(R==0) R++;
	cout<<max(0ll,L-R);
}