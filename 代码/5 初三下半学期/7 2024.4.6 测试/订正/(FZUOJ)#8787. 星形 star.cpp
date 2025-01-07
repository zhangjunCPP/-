#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e6+10;
const int mod=998244353;
struct node{
	int v,nex;
}a[N];
int first[N],cnt;
void add(int u,int v){
	a[++cnt]={v,first[u]};
	first[u]=cnt;
}
int n;
int ans;
int siz[N];
void dfs(int u,int fa){
	siz[u]=1;
	int sum1=1,sum2=0,sum3=0;
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(v==fa)continue;
		dfs(v,u);
		siz[u]+=siz[v];
		sum1=sum1*(siz[v]+1)%mod;
		sum2=(sum2+siz[v]*sum3%mod)%mod;
		sum3=(sum3+siz[v])%mod;
	}
	sum1=sum1*(n-siz[u]+1)%mod;
	sum2=(sum2+(n-siz[u])*sum3%mod)%mod;
	sum3=(sum3+(n-siz[u]))%mod;
	ans=(ans+(sum1-sum2-sum3-1)%mod+mod)%mod;
}
signed main(){
	cin>>n;
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		add(u,v);
		add(v,u);
	}
	dfs(1,0);
	cout<<ans<<"\n";
}