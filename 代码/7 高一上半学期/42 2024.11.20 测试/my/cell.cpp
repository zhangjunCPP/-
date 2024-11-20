#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
struct node{
	int v,nex;
}a[N];
int first[N],cnt;
void add(int u,int v){
	a[++cnt]={v,first[u]};
	first[u]=cnt;
}
int val[N];
int fa[N][20],sum[N][20];
int dep[N];
int Sum[N];
void dfs(int u,int dad,int tot){
	dep[u]=dep[dad]+1;
	fa[u][0]=dad;
	sum[u][0]=val[dad];
	for(int i=1;i<20;i++) fa[u][i]=fa[fa[u][i-1]][i-1],sum[u][i]=sum[u][i-1]+sum[fa[u][i-1]][i-1];
	int son=0;
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(v==dad) continue;
		son++;
		dfs(v,u,tot+val[u]);
	}
	if(!son)Sum[u]=tot+val[u];
}
int find_kth(int u,int k){
	for(int i=19;i>=0;i--)if(k>=(1<<i))u=fa[u][i],k-=(1<<i);
	return u;
}
int find_ksum(int u,int k){
	int ans=val[u];
	for(int i=19;i>=0;i--)if(k>=(1<<i)){
		ans+=sum[u][i];
		u=fa[u][i],k-=(1<<i);
	}
	return ans;
}
void dfs_update(int u,int dad,int val_dad){
	int son=0;
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(v==dad)continue;
		son++;
		dfs_update(v,u,val[u]);
	}
	if(!son)val[u]+=val_dad;
	else val[u]=val_dad;
}
struct node2{
	int opt,v,k;
}q[N];
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int n,m;
	cin>>n>>m;
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		add(u,v);
		add(v,u);
	}
	for(int i=1;i<=n;i++)cin>>val[i];
	dfs(1,0,0);
	for(int i=1;i<=m;i++){
		string s;
		cin>>s;
		if(s=="+")cin>>q[i].v>>q[i].k,q[i].opt=1;
		else cin>>q[i].v,q[i].opt=2;
	}
	if(n<=1000){
		for(int i=1;i<=m;i++){
			dfs_update(1,0,0);
			if(q[i].opt==1)val[q[i].v]+=q[i].k;
			else cout<<val[q[i].v]<<"\n";
		}
		return 0;
	}
	for(int i=1;i<=m;i++){
		if(i>=dep[q[i].v]){
			if(Sum[q[i].v])cout<<Sum[q[i].v]<<"\n";
			else cout<<"0\n";
		}
		else{
			if(Sum[q[i].v])cout<<find_ksum(q[i].v,i)<<"\n";
			else cout<<val[find_kth(q[i].v,i)]<<"\n";
		}
	}
}