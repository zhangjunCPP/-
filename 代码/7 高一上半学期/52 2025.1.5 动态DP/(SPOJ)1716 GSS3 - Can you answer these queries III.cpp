#include<bits/stdc++.h>
using namespace std;
const int N=5e4+10;
int a[N];
struct node{
	int sum,ans;
	int lans,rans;
	node operator+(const node&oth)const{
		node Ans;
		Ans.sum=sum+oth.sum;
		Ans.ans=max({ans,oth.ans,rans+oth.lans});
		Ans.lans=max(lans,sum+oth.lans);
		Ans.rans=max(oth.rans,rans+oth.sum);
		return Ans;
	}
}tree[N<<2];
#define ls (k<<1)
#define rs (k<<1|1)
void build(int k,int l,int r){
	if(l==r){
		tree[k]={a[l],a[l],a[l],a[l]};
		return;
	}
	int mid=(l+r)>>1;
	build(ls,l,mid);build(rs,mid+1,r);
	tree[k]=tree[ls]+tree[rs];
}
void modify(int k,int l,int r,int x,int val){
	if(l==r){
		tree[k]={val,val,val,val};
		return;
	}
	int mid=(l+r)>>1;
	if(x<=mid)modify(ls,l,mid,x,val);
	else modify(rs,mid+1,r,x,val);
	tree[k]=tree[ls]+tree[rs];
}
node query(int k,int l,int r,int x,int y){
	if(x<=l&&y>=r)return tree[k];
	int mid=(l+r)>>1;
	if(y<=mid)return query(ls,l,mid,x,y);
	if(x>mid)return query(rs,mid+1,r,x,y);
	return query(ls,l,mid,x,mid)+query(rs,mid+1,r,mid+1,y);
}
int main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	build(1,1,n);
	int q;
	cin>>q;
	while(q--){
		int opt,x,y;
		cin>>opt>>x>>y;
		if(opt==0)modify(1,1,n,x,y);
		else{
			node ans=query(1,1,n,x,y);
			cout<<ans.ans<<"\n";
		}
	}
}