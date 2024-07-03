#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
struct node{
	int v,nex;
}a[N];
int first[N],cnt;
void add(int u,int v){
	a[++cnt]={v,first[u]};
	first[u]=cnt;
}
int ban[N];
int lab[N];
void dfs(int u,int fa){
	int S=0;
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(v==fa)continue;
		dfs(v,u);
		S|=ban[u]&ban[v];
		ban[u]|=ban[v];
	}
	int tmp=S?32-__builtin_clz(S):0;
	lab[u]=__builtin_ctz((ban[u]|((1<<tmp)-1))+1);
	ban[u]=(((ban[u]>>lab[u])|1)<<lab[u]);
}
int main(){
	int n;
	cin>>n;
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		add(u,v);
		add(v,u);
	}
	dfs(1,0);
	int ans=-1;
	for(int i=1;i<=n;i++)ans=max(ans,lab[i]);
	cout<<ans;
}