#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
struct node{
	int v,w,nex;
}a[N];
int first[N],cnt;
void add(int u,int v,int w){
	a[++cnt]={v,w,first[u]};
	first[u]=cnt;
}
int n,m;

int mid;
int sum;
int vis[N];
int dp[N];
int q[N],tot;
void check(int u,int fa){
	for(int i=first[u];i;i=a[i].nex) {
		int v=a[i].v;
		if(v==fa) continue;
		check(v,u);
	}
	tot=0;
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(v==fa) continue;
		q[++tot]=dp[v]+a[i].w;
	}
	sort(q+1,q+tot+1);
	for(int i=tot;i>=1&&q[i]>=mid;i--) tot--,sum++;
	for(int i=1;i<=tot;i++) {
		if(vis[i]!=u) {  //避免频繁清空
			int l=i+1,r=tot,ans=tot+1;
			while(l<=r){
				int Mid=(l+r)>>1;
				if(q[i]+q[Mid]>=mid) ans=Mid,r=Mid-1;
				else l=Mid+1;
			}
			while(vis[ans]==u&&ans<=tot) ans++;
			if(ans<=tot) {
				vis[i]=vis[ans]=u;
				sum++;
			}
		}
	}
	dp[u]=0;
	for(int i=tot;i>=1;i--) {
		if(vis[i]!=u) {
			dp[u]=q[i];
			break;
		}
	}
	return;
}	
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<n;i++){
		int u,v,w;
		cin>>u>>v>>w;
		add(u,v,w);
		add(v,u,w);
	}
	int ans=0;
	int l=0,r=0x3f3f3f3f;
	while(l<=r){
		sum=0;
		memset(vis,0,sizeof(vis));
		mid=(l+r)>>1;
		check(1,0);
		if(sum>=m)ans=mid,l=mid+1;
		else r=mid-1;
	}
	cout<<ans<<endl;
}