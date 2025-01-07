#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10,INF=1e18;
int a[N];
#define ls (k<<1)
#define rs (k<<1|1)
struct node{
	int sum,Min,Max,lazy;
}tree[N<<2];
void pushup(int k){
	tree[k].Min=min(tree[ls].Min,tree[rs].Min);
	tree[k].Max=max(tree[ls].Max,tree[rs].Max);
	tree[k].sum=tree[ls].sum+tree[rs].sum;
}
void update(int k,int l,int r,int x){
	tree[k].Min+=x,tree[k].Max+=x;
	tree[k].sum+=(r-l+1)*x;
	tree[k].lazy+=x;
}
void pushdown(int k,int l,int r){
	if(tree[k].lazy){
		int mid=(l+r)>>1;
		update(ls,l,mid,tree[k].lazy);
		update(rs,mid+1,r,tree[k].lazy);
		tree[k].lazy=0;
	}
}
void build(int k,int l,int r){
	if(l==r){
		tree[k].Min=tree[k].Max=tree[k].sum=a[l];
		tree[k].lazy=0;
		return;
	}
	int mid=(l+r)>>1;
	build(ls,l,mid);build(rs,mid+1,r);
	pushup(k);
}
void modify_add(int k,int l,int r,int x,int y,int val){
	if(x<=l&&y>=r){update(k,l,r,val);return;}
	pushdown(k,l,r);
	int mid=(l+r)>>1;
	if(x<=mid)modify_add(ls,l,mid,x,y,val);
	if(y>mid)modify_add(rs,mid+1,r,x,y,val);
	pushup(k);
}
int f(int x,int val){return floor(x*1.0/val)-x;}
void modify_divide(int k,int l,int r,int x,int y,int val){
	if(x<=l&&y>=r&&f(tree[k].Max,val)==f(tree[k].Min,val)){
		update(k,l,r,f(tree[k].Max,val));
		return;
	}
	pushdown(k,l,r);
	int mid=(l+r)>>1;
	if(x<=mid)modify_divide(ls,l,mid,x,y,val);
	if(y>mid)modify_divide(rs,mid+1,r,x,y,val);
	pushup(k);
}
int query_min(int k,int l,int r,int x,int y){
	if(x<=l&&y>=r)return tree[k].Min;
	pushdown(k,l,r);
	int mid=(l+r)>>1;
	if(y<=mid)return query_min(ls,l,mid,x,y);
	if(x>mid)return query_min(rs,mid+1,r,x,y);
	return min(query_min(ls,l,mid,x,y),query_min(rs,mid+1,r,x,y));
}
int query_sum(int k,int l,int r,int x,int y){
	if(x<=l&&y>=r)return tree[k].sum;
	pushdown(k,l,r);
	int mid=(l+r)>>1;
	if(y<=mid)return query_sum(ls,l,mid,x,y);
	if(x>mid)return query_sum(rs,mid+1,r,x,y);
	return query_sum(ls,l,mid,x,y)+query_sum(rs,mid+1,r,x,y);
}
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int n,q;
	cin>>n>>q;
	for(int i=1;i<=n;i++)cin>>a[i];
	build(1,1,n);
	while(q--){
		int opt;
		cin>>opt;
		int l,r,c;
		cin>>l>>r;
		l++,r++;
		if(opt==1){cin>>c;modify_add(1,1,n,l,r,c);}
		if(opt==2){cin>>c;modify_divide(1,1,n,l,r,c);}
		if(opt==3)cout<<query_min(1,1,n,l,r)<<"\n";
		if(opt==4)cout<<query_sum(1,1,n,l,r)<<"\n";
	}
}