#include <bits/stdc++.h>
using namespace std;
const int N=1e6+10,V=1e6+1;
struct node {
	int val,Min,lazy;
}tree[N<<2];
int ls(int k){return k<<1;}
int rs(int k){return k<<1|1;}
void pushup(int k) {
	if(tree[ls(k)].Min==tree[rs(k)].Min)tree[k].Min=tree[ls(k)].Min,tree[k].val=tree[ls(k)].val+tree[rs(k)].val;
	else if(tree[ls(k)].Min<tree[rs(k)].Min)tree[k].Min=tree[ls(k)].Min,tree[k].val=tree[ls(k)].val;
	else tree[k].Min=tree[rs(k)].Min,tree[k].val=tree[rs(k)].val;
}
void pushdown(int k) {
	if(tree[k].lazy) {
		tree[ls(k)].lazy+=tree[k].lazy;
		tree[rs(k)].lazy+=tree[k].lazy;
		tree[ls(k)].Min+=tree[k].lazy;
		tree[rs(k)].Min+=tree[k].lazy;
		tree[k].lazy=0;
	}
}
void update(int k,int l,int r,int x,int y) {
	if(l==r) {
		tree[k].val+=y;
		return;
	}
	pushdown(k);
	int mid=(l+r)>>1;
	if(x<=mid)update(ls(k),l,mid,x,y);
	else update(rs(k),mid+1,r,x,y);
	pushup(k);
}
void modify(int k,int l,int r,int x,int y,int v) {
	if(x<=l&&y>=r) {
		tree[k].lazy+=v;
		tree[k].Min+=v;
		return;
	}
	pushdown(k);
	int mid=(l+r)>>1;
	if(x<=mid)modify(ls(k),l,mid,x,y,v);
	if(y>mid)modify(rs(k),mid+1,r,x,y,v);
	pushup(k);
}
int query(int k,int l,int r,int x,int y) {
	if(x<=l&&y>=r) {
		if(tree[k].Min==1)return tree[k].val;
		else return 0;
	}
	pushdown(k);
	int mid=(l+r)>>1;
	int sum=0;
	if(x<=mid)sum+=query(ls(k),l,mid,x,y);
	if(y>mid)sum+=query(rs(k),mid+1,r,x,y);
	return sum;
}
int a[N];
int main() {
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int n,q;
	cin>>n>>q;
	for(int i=1;i<=n;i++)cin>>a[i];
	a[0]=V,a[n+1]=0;
	for(int i=0;i<=n;i++)modify(1,0,V,min(a[i],a[i+1]),max(a[i],a[i+1])-1,1);
	for(int i=1;i<=n;i++)update(1,0,V,a[i],1);
	while(q--) {
		int x,y;
		cin>>x>>y;
		modify(1,0,V,min(a[x-1],a[x]),max(a[x-1],a[x])-1,-1);
		modify(1,0,V,min(a[x],a[x+1]),max(a[x],a[x+1])-1,-1);
		update(1,0,V,a[x],-1);
		a[x]=y;
		modify(1,0,V,min(a[x-1],a[x]),max(a[x-1],a[x])-1,1);
		modify(1,0,V,min(a[x],a[x+1]),max(a[x],a[x+1])-1,1);
		update(1,0,V,a[x],1);
		cout<<query(1,0,V,1,V-1)<<"\n";
	}
}