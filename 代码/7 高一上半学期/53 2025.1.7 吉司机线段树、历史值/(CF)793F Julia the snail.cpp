#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10,INF=1e9;
struct node{
	int max1,max2;
	int lazy;
}tree[N<<2];
#define ls (k<<1)
#define rs (k<<1|1)
void pushup(int k){
	tree[k].max1=max(tree[ls].max1,tree[rs].max1);
	tree[k].max2=max(tree[ls].max2,tree[rs].max2);
	if(tree[ls].max1!=tree[k].max1)tree[k].max2=max(tree[k].max2,tree[ls].max1);
	if(tree[rs].max1!=tree[k].max1)tree[k].max2=max(tree[k].max2,tree[rs].max1);
}
void update(int k,int v){tree[k].max1=tree[k].lazy=v;}
void pushdown(int k){
	if(tree[k].lazy){
		int tmp=max(tree[ls].max1,tree[rs].max1);
		if(tree[ls].max1==tmp)update(ls,tree[k].lazy);
		if(tree[rs].max1==tmp)update(rs,tree[k].lazy);
		//这里不能写tree[ls].max1==tree[k].max1，因为tree[k].max1已经被更改，而ls,rs的max1未被更改
		tree[k].lazy=0;
	}
}
void build(int k,int l,int r){
	if(l==r){
		tree[k]={l,-INF,0};
		return;
	}
	int mid=(l+r)>>1;
	build(ls,l,mid),build(rs,mid+1,r);
	pushup(k);
}
void modify(int k,int l,int r,int x,int y,int v,int w){
	if(tree[k].max1<v)return;
	if(x<=l&&y>=r&&tree[k].max2<v&&tree[k].max1>=v){update(k,w);return;}
	pushdown(k);
	int mid=(l+r)>>1;
	if(x<=mid)modify(ls,l,mid,x,y,v,w);
	if(y>mid)modify(rs,mid+1,r,x,y,v,w);
	pushup(k);
}
int query(int k,int l,int r,int x){
	if(l==r)return tree[k].max1;
	pushdown(k);
	int mid=(l+r)>>1;
	if(x<=mid)return query(ls,l,mid,x);
	else return query(rs,mid+1,r,x);
}
int a[N];
vector<pair<int,int>> q[N];
int ans[N];
int main(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int l,r;
		cin>>l>>r;
		a[r]=l;
	}
	int T;
	cin>>T;
	for(int i=1;i<=T;i++){
		int x,y;
		cin>>x>>y;
		q[y].push_back({x,i});
	}
	build(1,1,n);
	for(int i=1;i<=n;i++){
		if(a[i])modify(1,1,n,1,a[i],a[i],i);
		for(auto it:q[i])ans[it.second]=query(1,1,n,it.first);
	}
	for(int i=1;i<=T;i++)cout<<ans[i]<<"\n";
}