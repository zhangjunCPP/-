#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
const int N=3e6+10;
struct node{
	int v,nex;
}a[N];
int first[N],cnt;
void add(int u,int v){
	a[++cnt]={v,first[u]};
	first[u]=cnt;
}

int dis[N];
int fa[N][20];
void init(int u,int dad){
	fa[u][0]=dad;
	dis[u]=dis[dad]+1;
	for(int i=1;i<20;i++) fa[u][i]=fa[fa[u][i-1]][i-1];
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(v==dad) continue;
		init(v,u);
	}
}

int LCA(int x,int y){
	if(dis[x]<dis[y]) swap(x,y);
	for(int i=19;i>=0;i--) {
		if(dis[fa[x][i]]>=dis[y]) x=fa[x][i];
	}
	if(x==y) return x;
	for(int i=19;i>=0;i--) {
		if(fa[x][i]!=fa[y][i]) {
			x=fa[x][i];
			y=fa[y][i];
		}
	}
	return fa[x][0];
}
int getdis(int x,int y) {
	return dis[x]+dis[y]-2*dis[LCA(x,y)];
}
int qpow(int x,int y) {
	int ans=1;
	while(y) {
		if(y&1) ans=ans*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return ans;
}
int col[N];
int n;
int ans=0;
void dfs(int now){
	if(now==n+1) {
		int Max=0;
		for(int i=1;i<=n;i++) {
			for(int j=i;j<=n;j++) {
				if(col[i]==col[j]) Max=max(Max,getdis(i,j));
			}
		}
		ans+=Max;
		return ;		
	}
	col[now]=0;
	dfs(now+1);
	col[now]=1;
	dfs(now+1);
}
signed main() {
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	cin>>n;
	bool flag1=true,flag2=true;
	for(int i=1;i<n;i++) {
		int u,v;
		cin>>u>>v;
		if(u!=i||v!=i+1) flag1=false;
		if(u!=1&&v!=1) flag2=false;
		add(u,v);
		add(v,u);
	}
	// if(flag1) {
	//	 ans=0;
	//	 int tmp=(n+1)/2;
	//	 for(int i=n;i>=tmp;i--) {
	//		 ans=(ans+qpow(2,i-2)*(i-1)%mod)%mod;
	//	 }
	//	 for(int i=2;i<tmp;i++){
	//		 ans=(ans+qpow(2,i-2)*(n-i-1)%mod)%mod;
	//	 }
	//	 ans+=n-2;
	//	 cout<<ans*2%mod;
	//	 return 0;
	// }
	if(flag2) {
		cout<<qpow(2,n+1)%mod;
		return 0;
	}
	init(1,0);
	dfs(1);
	cout<<ans;
}