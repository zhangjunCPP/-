#include<bits/stdc++.h>
using namespace std;
const int N=5e6+10,V=1e5+5;
struct node{
	int ls,rs;
	int val;
}tree[N];
int tot;
int clone(int k){
	tree[++tot]=tree[k];
	return tot;
}
void update(int &k1,int k2,int l,int r,int x,int y){
	k1=clone(k2);
	if(l==r){
		tree[k1].val+=y;
		return;
	}
	int mid=(l+r)>>1;
	if(x<=mid)update(tree[k1].ls,tree[k2].ls,l,mid,x,y);
	else update(tree[k1].rs,tree[k2].rs,mid+1,r,x,y);
	tree[k1].val=tree[tree[k1].ls].val+tree[tree[k1].rs].val;
}
int query(int k1,int k2,int l,int r,int x,int y){
	int sum=tree[k2].val-tree[k1].val;
	if(x>r||y<l)return 0;
	if(x<=l&&y>=r)return sum;
	int mid=(l+r)>>1;
	return query(tree[k1].ls,tree[k2].ls,l,mid,x,y)+query(tree[k1].rs,tree[k2].rs,mid+1,r,x,y);
}
int rt[N];
int a[N];
int main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)update(rt[i],rt[i-1],0,V,a[i],1);
	for(int i=1;i<=m;i++){
		int b,x,l,r;
		cin>>b>>x>>l>>r;
		int ans=0;
		for(int j=18;j>=0;j--){
			int tmp=(b>>j)&1;
			if(tmp&&!(query(rt[l-1],rt[r],0,V,ans-x,ans-x+(1<<j)-1)))ans+=1<<j;
			if(!tmp&&query(rt[l-1],rt[r],0,V,ans-x+(1<<j),ans-x+(1<<(j+1))-1))ans+=1<<j;
		}
		cout<<(ans^b)<<"\n";
	}
}