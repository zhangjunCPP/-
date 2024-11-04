#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int n,m,q;
bool a[N];
struct node{
	int dp[25];
	node operator+(const node&oth)const{
		node ans;
		for(int i=1;i<=m+1;i++)ans.dp[i]=dp[oth.dp[i]];
		return ans;
	}
};
#define ls (k<<1)
#define rs (k<<1|1)
struct node2{
	node val1,val2;
	int lazy;
}tree[N*4];
void pushup(int k){
	tree[k].val1=tree[ls].val1+tree[rs].val1;
	tree[k].val2=tree[ls].val2+tree[rs].val2;
}
void update(int k){
	swap(tree[k].val1,tree[k].val2);
	tree[k].lazy^=1;
}
void pushdown(int k){
	if(tree[k].lazy){
		update(ls);
		update(rs);
		tree[k].lazy=0;
	}
}
void build(int k,int l,int r){
	if(l==r){
		for(int i=1;i<=m;i++)tree[k].val1.dp[i]=tree[k].val2.dp[i]=i+1;
		if(a[l])tree[k].val1.dp[m+1]=1,tree[k].val2.dp[m+1]=m+1;
		else tree[k].val1.dp[m+1]=m+1,tree[k].val2.dp[m+1]=1;
		return;
	}
	int mid=(l+r)>>1;
	build(ls,l,mid);build(rs,mid+1,r);
	pushup(k);
}
void modify(int k,int l,int r,int x,int y){
	if(x<=l&&y>=r){update(k);return;}
	pushdown(k);
	int mid=(l+r)>>1;
	if(x<=mid)modify(ls,l,mid,x,y);
	if(y>mid)modify(rs,mid+1,r,x,y);
	pushup(k);
}
node query(int k,int l,int r,int x,int y){
	if(x<=l&&y>=r)return tree[k].val2;
	pushdown(k);
	int mid=(l+r)>>1;
	if(x>mid)return query(rs,mid+1,r,x,y);
	if(y<=mid)return query(ls,l,mid,x,y);
	return query(ls,l,mid,x,y)+query(rs,mid+1,r,x,y);
}
int main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	cin>>n>>m>>q;
	for(int i=1;i<=n;i++){
		long long x;
		cin>>x;
		x&=1;
		a[i]=x^1;
	}
	build(1,1,n);
	while(q--){
		int opt,x,y;
		cin>>opt>>x>>y;
		if(opt==1){
			long long d;
			cin>>d;
			if(d&1)modify(1,1,n,x,y);
		}
		else{
			node ans=query(1,1,n,x,y);
			if(ans.dp[m+1]==1)cout<<"2\n";
			else cout<<"1\n";
		}
	}
}