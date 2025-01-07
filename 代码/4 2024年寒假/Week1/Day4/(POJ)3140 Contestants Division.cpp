#include <iostream>
#include <cstring>
#include <climits>
#define ll long long
using namespace std;
const int N=2e5+10,M=2e6+10;
struct node{
	int v,nex;
}a[M];
int cnt,first[N];
void add(int u,int v){
	a[++cnt]={v,first[u]};
	first[u]=cnt;
}
int n,m;
ll sum;
ll ans;
void init(){
	sum=0;
	memset(first,0,sizeof first);
	cnt=0;
	ans=LLONG_MAX;
}
ll siz[N];
ll Abs(ll x) {return x>0?x:-x;}
void dfs(int u,int fa){
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(v==fa) continue;
		dfs(v,u);
		siz[u]+=siz[v];
	}
	ans=min(ans,Abs(sum-2*siz[u]));
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int T=0;
	while(1){
		T++;
		init();
		cin>>n>>m;
		if(n==0&&m==0) break;
		for(int i=1;i<=n;i++) cin>>siz[i],sum+=siz[i];
		for(int i=1;i<=m;i++){
			int u,v;
			cin>>u>>v;
			add(u,v);
			add(v,u);
		}
		dfs(1,0);
		cout<<"Case "<<T<<": "<<ans<<"\n";
	}
}