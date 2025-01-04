#include<bits/stdc++.h>
using namespace std;
const int N=3e5+10;
int n,q;
int p[N];
struct node{
	int v,nex;
}a[N];
int first[N],cnt;
void add(int u,int v){
	a[++cnt]={v,first[u]};
	first[u]=cnt;
}
int fa[N];
int siz[N],dfn[N],idx;
void dfs(int u,int dad){
	siz[u]=1;
	fa[u]=dad;
	dfn[u]=++idx;
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(v==dad)continue;
		dfs(v,u);
		siz[u]+=siz[v];
	}
}
bool check(int x){
	if(x==1||x>n)return false;
	int u=p[x-1],v=p[x];
	return dfn[fa[v]]<=dfn[u]&&dfn[u]<=dfn[fa[v]]+siz[fa[v]]-1;
}
void solve(){
	memset(first,0,sizeof first);cnt=0;
	cin>>n>>q;
	for(int i=2;i<=n;i++){
		int x;
		cin>>x;
		add(x,i);
	}
	for(int i=1;i<=n;i++)cin>>p[i];
	dfs(1,0);
	int sum=0;
	for(int i=2;i<=n;i++)sum+=check(i);
	while(q--){
		int x,y;
		cin>>x>>y;
		sum-=check(x),sum-=check(x+1);
		if(y!=x+1)sum-=check(y);if(y+1!=x)sum-=check(y+1);
		swap(p[x],p[y]);
		sum+=check(x),sum+=check(x+1);
		if(y!=x+1)sum+=check(y);if(y+1!=x)sum+=check(y+1);
		if(sum==n-1)cout<<"YES\n";
		else cout<<"NO\n";
	}
}
int main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int T;
	cin>>T;
	while(T--)solve();
}