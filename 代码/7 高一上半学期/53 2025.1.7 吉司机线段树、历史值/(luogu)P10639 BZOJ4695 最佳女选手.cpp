#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+10,INF=1e18;
int a[N];
struct node{
	int sum;
	int max1,max2,min1,min2;
	int max_cnt,min_cnt;
	int lazy_add,lazy_max,lazy_min;
}tree[N<<2];
#define ls (k<<1)
#define rs (k<<1|1)
void pushup(int k){
	tree[k].sum=tree[ls].sum+tree[rs].sum;
	
	tree[k].max1=max(tree[ls].max1,tree[rs].max1);
	tree[k].max2=-INF;
	if(tree[ls].max1<tree[k].max1)tree[k].max2=max(tree[k].max2,tree[ls].max1);
	if(tree[ls].max2<tree[k].max1)tree[k].max2=max(tree[k].max2,tree[ls].max2);
	if(tree[rs].max1<tree[k].max1)tree[k].max2=max(tree[k].max2,tree[rs].max1);
	if(tree[rs].max2<tree[k].max1)tree[k].max2=max(tree[k].max2,tree[rs].max2);
	tree[k].max_cnt=0;
	if(tree[ls].max1==tree[k].max1)tree[k].max_cnt+=tree[ls].max_cnt;
	if(tree[rs].max1==tree[k].max1)tree[k].max_cnt+=tree[rs].max_cnt;

	tree[k].min1=min(tree[ls].min1,tree[rs].min1);
	tree[k].min2=INF;
	if(tree[ls].min1>tree[k].min1)tree[k].min2=min(tree[k].min2,tree[ls].min1);
	if(tree[ls].min2>tree[k].min1)tree[k].min2=min(tree[k].min2,tree[ls].min2);
	if(tree[rs].min1>tree[k].min1)tree[k].min2=min(tree[k].min2,tree[rs].min1);
	if(tree[rs].min2>tree[k].min1)tree[k].min2=min(tree[k].min2,tree[rs].min2);
	tree[k].min_cnt=0;
	if(tree[ls].min1==tree[k].min1)tree[k].min_cnt+=tree[ls].min_cnt;
	if(tree[rs].min1==tree[k].min1)tree[k].min_cnt+=tree[rs].min_cnt;

}
void update_add(int k,int l,int r,int v){
	tree[k].sum+=(r-l+1)*v;
	tree[k].lazy_add+=v;
	if(tree[k].max1!=-INF)tree[k].max1+=v;
	if(tree[k].max2!=-INF)tree[k].max2+=v;
	if(tree[k].min1!=INF)tree[k].min1+=v;
	if(tree[k].min2!=INF)tree[k].min2+=v;
	if(tree[k].lazy_max!=-INF)tree[k].lazy_max+=v;
	if(tree[k].lazy_min!=INF)tree[k].lazy_min+=v;
}
void update_max(int k,int l,int r,int v){
	if(tree[k].min1>=v)return;
	tree[k].sum+=(v-tree[k].min1)*tree[k].min_cnt;
	if(tree[k].max1==tree[k].min1)tree[k].max1=v;//区间只有一种权值时，最大和最小一样
	if(tree[k].max2==tree[k].min1)tree[k].max2=v;//区间只有两种权值时，次大和最小一样
	tree[k].min1=v;
	tree[k].lazy_max=v;
	tree[k].lazy_min=max(tree[k].lazy_min,v);
}
void update_min(int k,int l,int r,int v){
	if(tree[k].max1<=v)return;
	tree[k].sum+=(v-tree[k].max1)*tree[k].max_cnt;
	if(tree[k].min1==tree[k].max1)tree[k].min1=v;//区间只有一种权值时，最大和最小一样
	if(tree[k].min2==tree[k].max1)tree[k].min2=v;//区间只有两种权值时，最大和次小一样
	tree[k].max1=v;
	tree[k].lazy_max=min(tree[k].lazy_max,v);
	tree[k].lazy_min=v;
}
void pushdown(int k,int l,int r){
	int mid=(l+r)>>1;
	if(tree[k].lazy_add){
		update_add(ls,l,mid,tree[k].lazy_add);
		update_add(rs,mid+1,r,tree[k].lazy_add);
		tree[k].lazy_add=0;
	}
	if(tree[k].lazy_max!=-INF){
		update_max(ls,l,mid,tree[k].lazy_max);
		update_max(rs,mid+1,r,tree[k].lazy_max);
		tree[k].lazy_max=-INF;
	}
	if(tree[k].lazy_min!=INF){
		update_min(ls,l,mid,tree[k].lazy_min);
		update_min(rs,mid+1,r,tree[k].lazy_min);
		tree[k].lazy_min=INF;
	}
}
void build(int k,int l,int r){
	tree[k].lazy_add=0,tree[k].lazy_max=-INF,tree[k].lazy_min=INF;
	if(l==r){
		tree[k].max1=tree[k].min1=tree[k].sum=a[l];
		tree[k].max2=-INF,tree[k].min2=INF;
		tree[k].max_cnt=tree[k].min_cnt=1;
		return;
	}
	int mid=(l+r)>>1;
	build(ls,l,mid),build(rs,mid+1,r);
	pushup(k);
}
void modify_add(int k,int l,int r,int x,int y,int val){
	if(x<=l&&y>=r){update_add(k,l,r,val);return;}
	pushdown(k,l,r);
	int mid=(l+r)>>1;
	if(x<=mid)modify_add(ls,l,mid,x,y,val);
	if(y>mid)modify_add(rs,mid+1,r,x,y,val);
	pushup(k);
}
void modify_max(int k,int l,int r,int x,int y,int val){
	if(tree[k].min1>=val)return;
	if(x<=l&&y>=r&&tree[k].min2>val){update_max(k,l,r,val);return;}
	pushdown(k,l,r);
	int mid=(l+r)>>1;
	if(x<=mid)modify_max(ls,l,mid,x,y,val);
	if(y>mid)modify_max(rs,mid+1,r,x,y,val);
	pushup(k);
}
void modify_min(int k,int l,int r,int x,int y,int val){
	if(tree[k].max1<=val)return;
	if(x<=l&&y>=r&&tree[k].max2<val){update_min(k,l,r,val);return;}
	pushdown(k,l,r);
	int mid=(l+r)>>1;
	if(x<=mid)modify_min(ls,l,mid,x,y,val);
	if(y>mid)modify_min(rs,mid+1,r,x,y,val);
	pushup(k);
}
int query_sum(int k,int l,int r,int x,int y){
	if(x<=l&&y>=r)return tree[k].sum;
	pushdown(k,l,r);
	int mid=(l+r)>>1;
	if(y<=mid)return query_sum(ls,l,mid,x,y);
	if(x>mid)return query_sum(rs,mid+1,r,x,y);
	return query_sum(ls,l,mid,x,y)+query_sum(rs,mid+1,r,x,y);
}
int query_max(int k,int l,int r,int x,int y){
	if(x<=l&&y>=r)return tree[k].max1;
	pushdown(k,l,r);
	int mid=(l+r)>>1;
	if(y<=mid)return query_max(ls,l,mid,x,y);
	if(x>mid)return query_max(rs,mid+1,r,x,y);
	return max(query_max(ls,l,mid,x,y),query_max(rs,mid+1,r,x,y));
}
int query_min(int k,int l,int r,int x,int y){
	if(x<=l&&y>=r)return tree[k].min1;
	pushdown(k,l,r);
	int mid=(l+r)>>1;
	if(y<=mid)return query_min(ls,l,mid,x,y);
	if(x>mid)return query_min(rs,mid+1,r,x,y);
	return min(query_min(ls,l,mid,x,y),query_min(rs,mid+1,r,x,y));
}
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	build(1,1,n);
	int m;
	cin>>m;
	while(m--){
		int opt,l,r;
		cin>>opt>>l>>r;
		if(opt==1){int val;cin>>val;modify_add(1,1,n,l,r,val);}
		if(opt==2){int val;cin>>val;modify_max(1,1,n,l,r,val);}
		if(opt==3){int val;cin>>val;modify_min(1,1,n,l,r,val);}
		if(opt==4)cout<<query_sum(1,1,n,l,r)<<"\n";
		if(opt==5)cout<<query_max(1,1,n,l,r)<<"\n";
		if(opt==6)cout<<query_min(1,1,n,l,r)<<"\n";
	}
}