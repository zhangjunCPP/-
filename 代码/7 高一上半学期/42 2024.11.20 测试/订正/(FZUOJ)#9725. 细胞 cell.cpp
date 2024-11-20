#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
int n,m;
struct node{
	int v,nex;
}a[N];
int first[N],cnt;
int deg[N];
void add(int u,int v){
	a[++cnt]={v,first[u]};
	first[u]=cnt;
	deg[v]++;
}
int tree[N];
int lowbit(int x){return x&-x;}
void modify(int x,int val){
	for(int i=x;i;i-=lowbit(i))tree[i]+=val;
}
int query(int x){
	int ans=0;
	for(int i=x;i<=n+m;i+=lowbit(i))ans+=tree[i];
	return ans;
}
vector<pair<int,int>>G[N];
vector<int>Q[N];
int ans[N];
void dfs(int u,int dad,int dep){
	for(auto it:G[u]){
		if(it.second==-1){
			if(n==1||(deg[u]==1&&dad))ans[it.first]=query(dep-it.first+m);
			else ans[it.first]=query(dep-it.first+m)-query(dep-it.first+m+1);
		}
		else modify(dep-it.first+m,it.second);
	}
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(v==dad)continue;
		dfs(v,u,dep+1);
	}
	for(auto it:G[u])if(it.second!=-1)modify(dep-it.first+m,-it.second);
}
bool flag[N];
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	cin>>n>>m;
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		add(u,v);
		add(v,u);
	}
	for(int i=1;i<=n;i++){
		int x;
		cin>>x;
		G[i].push_back({0,x});
	}
	for(int i=1;i<=m;i++){
		string opt;
		cin>>opt;
		if(opt=="+"){
			int v,k;
			cin>>v>>k;
			G[v].push_back({i,k});
		}
		else{
			flag[i]=true;
			int v;
			cin>>v;
			G[v].push_back({i,-1});
		}
	}
	dfs(1,0,1);
	for(int i=1;i<=m;i++)if(flag[i])cout<<ans[i]<<"\n";
}