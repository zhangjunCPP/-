#include<bits/stdc++.h>
using namespace std;
const int N=5e6+10;
struct node{
	int ls,rs;
	int sum;
}tree[N];
int tot;
int ls(int k){return tree[k].ls;}
int rs(int k){return tree[k].rs;}
void pushup(int k){tree[k].sum=tree[ls(k)].sum+tree[rs(k)].sum;}
void build(int &k,int l,int r){
	k=++tot;
	if(l==r)return;
	int mid=(l+r)>>1;
	build(tree[k].ls,l,mid);
	build(tree[k].rs,mid+1,r);
}
int clone(int k){
	tree[++tot]=tree[k];
	return tot;
}
void update(int &k1,int k2,int l,int r,int x,int y){
	k1=clone(k2);
	if(l==r){
		tree[k1].sum+=y;
		return;
	}
	int mid=(l+r)>>1;
	if(x<=mid)update(tree[k1].ls,tree[k2].ls,l,mid,x,y);
	else update(tree[k1].rs,tree[k2].rs,mid+1,r,x,y);
	pushup(k1);
}
int query(int k1,int k2,int l,int r,int k){
	if(l==r)return l;
	int sum=tree[ls(k2)].sum-tree[ls(k1)].sum;
	int mid=(l+r)>>1;
	if(k<=sum)return query(ls(k1),ls(k2),l,mid,k);
	else return query(rs(k1),rs(k2),mid+1,r,k-sum);
}
int rt[N];
int a[N];
int tmp[N];
int main(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i],tmp[i]=a[i];
	sort(tmp+1,tmp+n+1);
	for(int i=1;i<=n;i++)a[i]=lower_bound(tmp+1,tmp+n+1,a[i])-tmp;
	build(rt[0],1,n);
	for(int i=1;i<=n;i++)update(rt[i],rt[i-1],1,n,a[i],1);
	for(int i=1;i<=m;i++){
		int l,r,k;
		cin>>l>>r>>k;
		cout<<tmp[query(rt[l-1],rt[r],1,n,k)]<<"\n";
	}
}