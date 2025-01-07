#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e5+10,M=1e7+10;
int a[N];
int prime[N*10],tot;
bool flag[M];
int phi[M];
void init(){
	for(int i=2;i<M;i++){
		if(!flag[i])prime[++tot]=i,phi[i]=i-1;
		for(int j=1;j<=tot&&i*prime[j]<M;j++){
			flag[i*prime[j]]=true;
			if(i%prime[j])phi[i*prime[j]]=phi[i]*(prime[j]-1);
			else {phi[i*prime[j]]=phi[i]*prime[j];break;}
		}
	}
}
#define ls (k<<1)
#define rs (k<<1|1)
struct node{
	int sum,lazy;
}tree[N<<2];
void pushup(int k){
	tree[k].sum=tree[ls].sum+tree[rs].sum;
}
void update(int k,int l,int r,int x){
	tree[k].sum=(r-l+1)*x;
	tree[k].lazy=x;
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
	tree[k].lazy=0;
	if(l==r){
		tree[k].sum=a[l];
		return;
	}
	int mid=(l+r)>>1;
	build(ls,l,mid);build(rs,mid+1,r);
	pushup(k);
}
void modify_cover(int k,int l,int r,int x,int y,int val){
	if(x<=l&&y>=r){update(k,l,r,val);return;}
	pushdown(k,l,r);
	int mid=(l+r)>>1;
	if(x<=mid)modify_cover(ls,l,mid,x,y,val);
	if(y>mid)modify_cover(rs,mid+1,r,x,y,val);
	pushup(k);
}
void modify_phi(int k,int l,int r,int x,int y){
	if(tree[k].sum==r-l+1)return;
	if(l==r){update(k,l,r,phi[tree[k].sum]);return;}
	if(x<=l&&y>=r&&tree[k].lazy){
		update(k,l,r,phi[tree[k].lazy]);
		return;
	}
	pushdown(k,l,r);
	int mid=(l+r)>>1;
	if(x<=mid)modify_phi(ls,l,mid,x,y);
	if(y>mid)modify_phi(rs,mid+1,r,x,y);
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
void solve(){
	int n,q;
	cin>>n>>q;
	for(int i=1;i<=n;i++)cin>>a[i];
	build(1,1,n);
	while(q--){
		int opt,l,r;
		cin>>opt>>l>>r;
		if(opt==1)modify_phi(1,1,n,l,r);
		if(opt==2){int x;cin>>x;modify_cover(1,1,n,l,r,x);}
		if(opt==3)cout<<query_sum(1,1,n,l,r)<<"\n";
	}
}
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	init();
	int T;
	cin>>T;
	while(T--)solve();
}