#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1e5+10;
ll x[N],y[N],z[N];
vector<int> G[N];
int n;
int fa[N];
void dfs(int u,int dad){
	fa[u]=dad;
	for(int v:G[u]){
		if(v==dad) continue;
		dfs(v,u);
	}
}
__int128 f(__int128 x) {return x*(x+1)/2;}
__int128 calc(__int128 i,__int128 m) {
	if(z[i]>0) return m*y[i]+f(m)*z[i];
	else if(z[i]==0)return m*y[i];
	else {
		__int128 x=min(m,(__int128)((1-y[i])/z[i]));
		return x*y[i]+f(x)*z[i]+(m-x);
	}
}
int id[N];
int t[N];
bool vis[N];
int solve(int x){
	if(vis[x]) return 0;
	vis[x]=true;
	if(fa[x]) return solve(fa[x])+1;
	else return 1;
}
bool check(int mid){
	for(int i=1;i<=n;i++) {
		vis[i]=false;
		__int128 val=calc(i,mid);
		if(val<x[i]) return false;
		int ans=0;
		int l=1,r=mid;
		while(l<=r) {
			int midd=(l+r)>>1;
			if(val-calc(i,midd-1)>=x[i]) l=midd+1,ans=midd;
			else r=midd-1;
		}
		t[i]=ans;
	}
	sort(id+1,id+n+1,[](const int &a,const int &b){return t[a]<t[b];});
	int sum=0;
	for(int i=1;i<=n;i++) {
		sum+=solve(id[i]);
		if(sum>t[id[i]]) return false;
	}
	return true;

}
ll read(){
	ll x=0;
	bool f=true;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') f=false;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=(x<<3)+(x<<1)+(ch^48);
		ch=getchar();
	}
	if(!f) x=-x;
	return x;
}
int main(){
	n=read();
	for(int i=1;i<=n;i++)x[i]=read(),y[i]=read(),z[i]=read(),id[i]=i;
	for(int i=1;i<n;i++) {
		int u,v;
		u=read(),v=read();
		G[u].push_back(v);
		G[v].push_back(u);
	}
	dfs(1,0);
	int ans=0;
	int l=1,r=1e9;
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid)) ans=mid,r=mid-1;
		else l=mid+1;
	}
	cout<<ans;
}