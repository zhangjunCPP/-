#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e6+10;
int n;
struct node{
	int v,nex;
}a[N];
int first[N],cnt;
void add(int u,int v){
	a[++cnt]={v,first[u]};
	first[u]=cnt;
}
int tree[N];
int lowbit(int x){return x&-x;}
void modify(int x,int val){for(int i=x;i<=n;i+=lowbit(i))tree[i]+=val;}
int query(int x){
	int ans=0;
	for(int i=x;i;i-=lowbit(i))ans+=tree[i];
	return ans;
}
void update(int x,int val){for(int i=x;i<=n;i+=lowbit(i))tree[i]=val;}
int fa[N];
vector<int> G[N];
int dfn[N],tot;
int siz[N];
void dfs(int u){
	dfn[u]=++tot;
	siz[u]=1;
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		dfs(v);
		siz[u]+=siz[v];
	}
}
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	cin>>n;
	for(int i=2;i<=n;i++){
		int col;
		cin>>fa[i]>>col;
		add(fa[i],i);
		G[col].push_back(i);
	}
	dfs(1);
	int ans=0;
	for(int i=1;i<=n;i++){
		sort(G[i].begin(),G[i].end(),[](const int&x,const int&y){return dfn[x]>dfn[y];});
		G[i].push_back(1);
		for(int it:G[i]){
			int val=siz[it]-query(dfn[it]+siz[it]-1)+query(dfn[it]-1);
			ans+=val*(val-1)/2;
			if(it!=1)modify(dfn[fa[it]],val);
		}
		for(int it:G[i])if(it!=1)update(dfn[fa[it]],0);
	}
	ans=n*n*(n-1)/2-ans;
	cout<<ans;
}