#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
int a[N];
struct node{
	int max1,max2,cnt;
	int sum;
	int lazy;
}tree[N<<2];
#define ls (k<<1)
#define rs (k<<1|1)
void pushup(int k){
	tree[k].max1=max(tree[ls].max1,tree[rs].max1);
	tree[k].sum=tree[ls].sum+tree[rs].sum;
	if(tree[ls].max1==tree[rs].max1){
		tree[k].cnt=tree[ls].cnt+tree[rs].cnt;
		tree[k].max2=max(tree[ls].max2,tree[rs].max2);
	}
	else if(tree[ls].max1>tree[rs].max1){
		tree[k].cnt=tree[ls].cnt;
		tree[k].max2=max(tree[ls].max2,tree[rs].max1);
	}
	else{
		tree[k].cnt=tree[rs].cnt;
		tree[k].max2=max(tree[ls].max1,tree[rs].max2);
	}
}
void update(int k,int v){
	if(tree[k].max1<=v)return;
	tree[k].sum+=(v-tree[k].max1)*tree[k].cnt;
	tree[k].max1=tree[k].lazy=v;
}
void pushdown(int k){
	if(tree[k].lazy!=-1){
		update(ls,tree[k].lazy);
		update(rs,tree[k].lazy);
		tree[k].lazy=-1;
	}
}
void build(int k,int l,int r){
	tree[k].lazy=-1;
	if(l==r){
		tree[k]={a[l],-1,1,a[l],-1};
		return;
	}
	int mid=(l+r)>>1;
	build(ls,l,mid),build(rs,mid+1,r);
	pushup(k);
}
void modify(int k,int l,int r,int x,int y,int val){
	if(tree[k].max1<=val)return;
	if(x<=l&&y>=r&&tree[k].max2<val){update(k,val);return;}
	pushdown(k);
	int mid=(l+r)>>1;
	if(x<=mid)modify(ls,l,mid,x,y,val);
	if(y>mid)modify(rs,mid+1,r,x,y,val);
	pushup(k);
}

int query_max(int k,int l,int r,int x,int y){
	if(x<=l&&y>=r)return tree[k].max1;
	pushdown(k);
	int mid=(l+r)>>1;
	if(y<=mid)return query_max(ls,l,mid,x,y);
	if(x>mid)return query_max(rs,mid+1,r,x,y);
	return max(query_max(ls,l,mid,x,y),query_max(rs,mid+1,r,x,y));
}
int query_sum(int k,int l,int r,int x,int y){
	if(x<=l&&y>=r)return tree[k].sum;
	pushdown(k);
	int mid=(l+r)>>1;
	if(y<=mid)return query_sum(ls,l,mid,x,y);
	if(x>mid)return query_sum(rs,mid+1,r,x,y);
	return query_sum(ls,l,mid,x,y)+query_sum(rs,mid+1,r,x,y);
}
void solve(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i];
	build(1,1,n);
	while(m--){
		int opt,l,r;
		cin>>opt>>l>>r;
		if(opt==0){int val;cin>>val;modify(1,1,n,l,r,val);}
		if(opt==1)cout<<query_max(1,1,n,l,r)<<"\n";
		if(opt==2)cout<<query_sum(1,1,n,l,r)<<"\n";
	}
}
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int T;
	cin>>T;
	while(T--)solve();
}