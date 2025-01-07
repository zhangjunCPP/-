#include <bits/stdc++.h>
using namespace std;
const int N=5e7+10;
struct node{
	int ls,rs;
	int val;
}tree[N];
int a[N];
int tot;
int clone(int k){
	tree[++tot]=tree[k];
	return tot;
}
void build(int &k,int l,int r){
	k=++tot;
	if(l==r){
		tree[k].val=a[l];
		return;
	}
	int mid=(l+r)>>1;
	build(tree[k].ls,l,mid);
	build(tree[k].rs,mid+1,r);
	return;
}
void update(int &k1,int k2,int l,int r,int x,int val){
	k1=clone(k2);
	if(l==r){
		tree[k1].val=val;
		return;
	}
	int mid=(l+r)>>1;
	if(x<=mid)update(tree[k1].ls,tree[k2].ls,l,mid,x,val);
	else update(tree[k1].rs,tree[k2].rs,mid+1,r,x,val);
	return;
}
int query(int k,int l,int r,int x){
	if(l==r)return tree[k].val;
	int mid=(l+r)>>1;
	if(x<=mid)return query(tree[k].ls,l,mid,x);
	else return query(tree[k].rs,mid+1,r,x);
}
int rt[N];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr),cout.tie(nullptr);
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i];
	build(rt[0],1,n);
	for(int i=1;i<=m;i++)  {
		int root,opt,x;
		cin>>root>>opt>>x;
		if(opt==1){
			int y;
			cin>>y;
			update(rt[i],rt[root],1,n,x,y);
		}
		else {
			cout<<query(rt[root],1,n,x)<<"\n";
			rt[i]=rt[root];
		}
	}
}