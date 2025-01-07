#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
int a[N];
int tree[N*4];
void build(int k,int l,int r){
	if(l==r){tree[k]=a[l];return;}
	int mid=(l+r)>>1;
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
	tree[k]=min(tree[k<<1],tree[k<<1|1]);
}
int query(int k,int l,int r,int x,int y,int val){
	if(l>y||r<x) return -1;
	if(tree[k]>=val) return -1;
	if(l==r) return l;
	int mid=(l+r)>>1;
	int tmp=query(k<<1|1,mid+1,r,x,y,val);
	if(tmp!=-1) return tmp;
	else return query(k<<1,l,mid,x,y,val);
}
signed main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	build(1,1,n);
	for(int i=1;i<=n;i++){
		int ans=query(1,1,n,i,n,a[i]);
		if(ans!=-1) ans=ans-i-1;
		cout<<ans<<" ";
	}
	return 0;
}