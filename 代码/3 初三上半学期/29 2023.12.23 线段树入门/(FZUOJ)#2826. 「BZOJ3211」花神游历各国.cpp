#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
int tree1[N<<2],tree2[N<<2];
int a[N];
#define ls k<<1
#define rs k<<1|1
void build(int k,int l,int r){
	if(l==r){
		tree1[k]=tree2[k]=a[l];
		return;
	}
	int mid=(l+r)>>1;
	build(ls,l,mid);
	build(rs,mid+1,r);
	tree1[k]=max(tree1[ls],tree1[rs]);
	tree2[k]=tree2[ls]+tree2[rs];
	return;
}
void update(int k,int l,int r,int x,int y){
	if(l==r){
		tree1[k]=tree2[k]=sqrt(tree1[k]);
		return;
	}
	int mid=(l+r)>>1;
	if(x<=mid&&tree1[ls]>1) update(ls,l,mid,x,y);
	if(y>mid&&tree1[rs]>1) update(rs,mid+1,r,x,y);
	tree1[k]=max(tree1[ls],tree1[rs]);
	tree2[k]=tree2[ls]+tree2[rs];
	return;
}
int query(int k,int l,int r,int x,int y){
	if(x<=l&&y>=r) return tree2[k];
	int mid=(l+r)>>1;
	int ans=0;
	if(x<=mid)ans+=query(ls,l,mid,x,y);
	if(y>mid)ans+=query(rs,mid+1,r,x,y);
	return ans; 
}
signed main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	build(1,1,n);
	int q;
	cin>>q;
	while(q--){
		int x,l,r;
		cin>>x>>l>>r;
		if(x==1) cout<<query(1,1,n,l,r)<<"\n";
		else update(1,1,n,l,r);
	}
}