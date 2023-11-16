#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e6+10;
int n,k;
int u[N],v[N];
int sum[N],fa[N];
bool vis[N];
int find(int x){
	if(x!=fa[x]) fa[x]=find(fa[x]);
	return fa[x];
}
void merge(int x,int y){
	if(find(x)!=find(y)) {
		fa[x]=y;
	}
}
void dfs(int now){
	if(now==n){
		for(int i=1;i<=n;i++) fa[i]=i,sum[i]=0;
		for(int i=1;i<n;i++)if(vis[i])merge(u[i],v[i]);
		for(int i=1;i<=n;i++) sum[find(i)]++;
		bool flag=true;
		for(int i=1;i<=n;i++){
			if(sum[i]&&sum[i]!=k){flag=false;break;}
		}
		if(flag) {cout<<"Yes";exit(0);}
		return;
	}
	vis[now]=true;
	dfs(now+1);
	vis[now]=false;
	dfs(now+1);
}
signed main(){
	freopen("cut.in","r",stdin);
	freopen("bf.out","w",stdout);
	cin>>n>>k;
	for(int i=1;i<n;i++) cin>>u[i]>>v[i];
	dfs(1);
	cout<<"No";
	return 0;

}
