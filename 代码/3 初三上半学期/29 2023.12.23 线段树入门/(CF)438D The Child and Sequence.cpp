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
void update(int k,int l,int r,int x,int y,int val,int opt){
	if(l==r){
		if(opt==0) tree1[k]=tree2[k]=tree1[k]%val;
		else tree1[k]=tree2[k]=val;
		return;
	}
	int mid=(l+r)>>1;
	if(opt==0){
		if(x<=mid&&tree1[ls]>=val) update(ls,l,mid,x,y,val,opt);
		if(y>mid&&tree1[rs]>=val) update(rs,mid+1,r,x,y,val,opt);
	}
	else{
		if(x<=mid) update(ls,l,mid,x,y,val,opt);
		else update(rs,mid+1,r,x,y,val,opt);
	}
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
	int n,q;
	cin>>n>>q;
	for(int i=1;i<=n;i++)cin>>a[i];
	build(1,1,n);
	while(q--){
		int opt;
		cin>>opt;
		if(opt==1){
			int l,r;
			cin>>l>>r;
			cout<<query(1,1,n,l,r)<<"\n";
		}
		else if(opt==2){
			int l,r,x;
			cin>>l>>r>>x;
			update(1,1,n,l,r,x,0);
		}
		else {
			int k,x;
			cin>>k>>x;
			update(1,1,n,k,k,x,1);
		}
	}
}