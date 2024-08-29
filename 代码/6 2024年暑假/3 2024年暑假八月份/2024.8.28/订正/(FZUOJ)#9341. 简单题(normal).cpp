#include <bits/stdc++.h>
using namespace std;
const int N=5e6+10;
int n,m;
struct node {
	int v,w,nex;
}a[N];
int first[N],cnt;
void add(int u,int v,int w) {
	a[++cnt]={v,w,first[u]};
	first[u]=cnt;
}
vector<int>tree[N];
#define ls (k<<1)
#define rs (k<<1|1)
void insert(int k,int l,int r,int x,int y,int val) {
	if(x<=l&&y>=r){tree[k].push_back(val);return;}
	int mid=(l+r)>>1;
	if(x<=mid)insert(ls,l,mid,x,y,val);
	if(y>mid)insert(rs,mid+1,r,x,y,val);
}
void query(int k,int l,int r,int x,int val) {
	if(!tree[k].empty()) {
		for(int it:tree[k])add(it,k+m,0),add(k+m,it,0);
		tree[k].clear();tree[k].push_back(k+m);
		add(val,k+m,1),add(k+m,val,1);
	}
	if(l==r)return;
	int mid=(l+r)>>1;
	if(x<=mid)query(ls,l,mid,x,val);
	else query(rs,mid+1,r,x,val);
}
struct node2 {int l,r;}seq[N];
vector<int> G[N];
int ans[N];
bool dfs(int u,int col) {
	ans[u]=col;
	for(int i=first[u];i;i=a[i].nex) {
		int v=a[i].v;
		if(ans[v]==-1){if(!dfs(v,col^a[i].w))return false;}
		else {if(ans[v]!=(col^a[i].w))return false;}
	}
	return true;
}
int main() {
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	cin>>n>>m;
	for(int i=1;i<=m;i++) {
		cin>>seq[i].l>>seq[i].r;
		G[seq[i].r].push_back(i);
	}
	for(int i=1;i<=n;i++) {
		for(int it:G[i])query(1,1,n,seq[it].l,it);
		for(int it:G[i])insert(1,1,n,seq[it].l+1,seq[it].r-1,it);
	}
	memset(ans,-1,sizeof ans);
	for(int i=1;i<=m;i++)if(ans[i]==-1&&!dfs(i,1)){puts("IMPOSSIBLE");return 0;}
	for(int i=1;i<=m;i++)cout<<(ans[i]?'N':'S')<<"\n";
}