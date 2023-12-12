#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
const int mod=998244353;
int a[N];
int tree[N<<2];
int add[N<<2],mul[N<<2];
void build(int k,int l,int r){
	mul[k]=1;
	add[k]=0;
	if(l==r){
		tree[k]=a[l]%mod;
		return;
	}
	int mid=(l+r)>>1;
	build(k<<1,l,mid);build(k<<1|1,mid+1,r);
	tree[k]=(tree[k<<1]+tree[k<<1|1])%mod;
}
void pushdown(int k,int l,int r){
	int mid=(l+r)>>1;
	tree[k<<1]=(tree[k<<1]*mul[k]+(mid-l+1)*add[k])%mod;
	tree[k<<1|1]=(tree[k<<1|1]*mul[k]+(r-mid)*add[k])%mod;
	mul[k<<1]=(mul[k<<1]*mul[k])%mod;
	mul[k<<1|1]=(mul[k<<1|1]*mul[k])%mod;
	add[k<<1]=(add[k<<1]*mul[k]+add[k])%mod;
	add[k<<1|1]=(add[k<<1|1]*mul[k]+add[k])%mod;
	mul[k]=1;add[k]=0;
}
void update(int k,int l,int r,int x,int y,int val,int opt){
	if(x<=l&&r<=y){
		if(opt==1){
			tree[k]=tree[k]*val%mod;
			add[k]=add[k]*val%mod;
			mul[k]=mul[k]*val%mod;
		}
		else{
			tree[k]=(tree[k]+(r-l+1)*val)%mod;
			add[k]=(add[k]+val)%mod;
		}
		return;
	}
	int mid=(l+r)>>1;
	pushdown(k,l,r);
	if(x<=mid)update(k<<1,l,mid,x,y,val,opt);
	if(y>mid)update(k<<1|1,mid+1,r,x,y,val,opt);
	tree[k]=(tree[k<<1]+tree[k<<1|1])%mod;
}
int query(int k,int l,int r,int x,int y){
	if(x<=l&&r<=y)return tree[k];
	int mid=(l+r)>>1;
	pushdown(k,l,r);
	int sum=0;
	if(x<=mid)sum=(sum+query(k<<1,l,mid,x,y))%mod;
	if(y>mid)sum=(sum+query(k<<1|1,mid+1,r,x,y))%mod;
	return sum;
}
int qpow(int x,int y){
	int ans=1;
	while(y){
		if(y&1)ans=ans*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return ans;
}
signed main(){
	int n,q;
	cin>>n>>q;
	for(int i=1;i<=n;++i)cin>>a[i];
	build(1,1,n);
	while(q--){
		int l,r,k;
		cin>>l>>r>>k;
		update(1,1,n,l,r,((r-l)*qpow(r-l+1,mod-2))%mod,1);
		update(1,1,n,l,r,k*qpow(r-l+1,mod-2),0);
	}
	for(int i=1;i<=n;++i)cout<<query(1,1,n,i,i)<<" ";
	return 0;
}
