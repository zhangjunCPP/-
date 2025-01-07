#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e6+10;
int a[N];
struct node{
	int ls,rs;
	int val,lazy;
}tree[N];
int tot;
int ls(int k){return tree[k].ls;}
int rs(int k){return tree[k].rs;}
void build(int &k,int l,int r){
	k=++tot;
	if(l==r){tree[k].val=a[l];return;}
	int mid=(l+r)>>1;
	build(tree[k].ls,l,mid);
	build(tree[k].rs,mid+1,r);
	tree[k].val=tree[ls(k)].val+tree[rs(k)].val;
}
int clone(int k){
	tree[++tot]=tree[k];
	return tot;
}
void update(int &k1,int k2,int l,int r,int x,int y,int val){
	k1=clone(k2);
	if(x<=l&&y>=r){
		tree[k1].lazy+=val;
		tree[k1].val+=val*(r-l+1);
		return;
	}
	tree[k1].val+=val*(min(r,y)-max(l,x)+1);
	int mid=(l+r)>>1;
	if(x<=mid)update(tree[k1].ls,tree[k2].ls,l,mid,x,y,val);
	if(y>mid)update(tree[k1].rs,tree[k2].rs,mid+1,r,x,y,val);
}
int query(int k,int l,int r,int x,int y,int sum){
	if(x>r||y<l)return 0;
	if(x<=l&&y>=r)return tree[k].val+(r-l+1)*sum;
	int mid=(l+r)>>1;
	int tmp=query(tree[k].ls,l,mid,x,y,sum+tree[k].lazy)+query(tree[k].rs,mid+1,r,x,y,sum+tree[k].lazy);
	return tmp;
}
int rt[N];
int now;
int tmp[N],cnt;

signed main(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i];
	build(rt[0],1,n);
	for(int i=1;i<=m;i++){
		string opt;
		cin>>opt;
		if(opt=="C"){
			int l,r,d;
			cin>>l>>r>>d;
			now++;tmp[++cnt]=now;
			update(rt[now],rt[now-1],1,n,l,r,d);
		}
		else if(opt=="Q"){
			int l,r;
			cin>>l>>r;
			cout<<query(rt[now],1,n,l,r,0)<<"\n";
		}
		else if(opt=="H"){
			int l,r,t;
			cin>>l>>r>>t;
			cout<<query(rt[tmp[t]],1,n,l,r,0)<<"\n";
		}
		else{
			int t;
			cin>>t;
			rt[++now]=rt[tmp[t]];
			cnt=t;
		}
	}
}