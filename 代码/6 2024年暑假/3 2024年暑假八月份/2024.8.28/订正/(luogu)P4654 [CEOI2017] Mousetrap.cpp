#include <bits/stdc++.h>
using namespace std;
const int N=2e6+10;
int n,t,s;
struct node {
	int v,nex;
}a[N];
int first[N],cnt;
void add(int u,int v) {
	a[++cnt]={v,first[u]};
	first[u]=cnt;
}
int dp[N];
int fa[N];
int sum[N];
void dfs(int u,int dad) {
	fa[u]=dad;
	int mx1=0,mx2=0;
	int son=0;
	for(int i=first[u];i;i=a[i].nex) {
		int v=a[i].v;
		if(v!=dad)son++;
	}
	if(u!=t)sum[u]=sum[dad]+son-1+(u==s);
	for(int i=first[u];i;i=a[i].nex) {
		int v=a[i].v;
		if(v==dad)continue;
		dfs(v,u);
		if(dp[v]>mx1)mx2=mx1,mx1=dp[v];
		else if(dp[v]>mx2)mx2=dp[v];
	}
	dp[u]=mx2+son;
}
bool flag[N];
bool check(int mid) {
	int tot=1;
	for(int now=s;now!=t;now=fa[now]) {
		int val=0;
		for(int i=first[now];i;i=a[i].nex) {
			int v=a[i].v;
			if(flag[v]||dp[v]+sum[now]<=mid)continue;
			if(!tot)return false;
			val++,tot--;
		}
		tot++;
		mid-=val;
	}
	return mid>=0;
}
int main() {
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	cin>>n>>t>>s;
	for(int i=1;i<n;i++) {
		int u,v;
		cin>>u>>v;
		add(u,v);
		add(v,u);
	}
	dfs(t,0);
	for(int i=s;i;i=fa[i])flag[i]=true;
	int l=0,r=2*n;
	int ans=-1;
	while(l<=r) {
		int mid=(l+r)>>1;
		if(check(mid))ans=mid,r=mid-1;
		else l=mid+1;
	}
	cout<<ans;
}