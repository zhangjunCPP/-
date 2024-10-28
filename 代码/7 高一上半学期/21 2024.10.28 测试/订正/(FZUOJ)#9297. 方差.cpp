#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+10,INF=1e18;
int a[N];
struct node2{
	int f[2];
	int lazy[2];
}tree[N<<2];
#define ls (k<<1)
#define rs (k<<1|1)
void build(int k,int l,int r){
	if(l==r){
		tree[k].f[0]=tree[k].f[1]=-INF;
		if(l>=2)tree[k].f[0]=a[l]+a[l-1];
		if(l>=3)tree[k].f[1]=a[l]+a[l-1]+a[l-2];
		return;
	}
	int mid=(l+r)>>1;
	build(ls,l,mid);
	build(rs,mid+1,r);
	tree[k].f[0]=max(tree[ls].f[0],tree[rs].f[0]);
	tree[k].f[1]=max(tree[ls].f[1],tree[rs].f[1]);
}
void update(int k,int val,bool opt){
	tree[k].f[opt]+=val;
	tree[k].lazy[opt]+=val;
}
void pushdown(int k){
	for(int opt=0;opt<2;opt++){
		if(tree[k].lazy[opt]){
			update(ls,tree[k].lazy[opt],opt);
			update(rs,tree[k].lazy[opt],opt);
			tree[k].lazy[opt]=0;
		}
	}
}
void modify(int k,int l,int r,int x,int y,int val,bool opt){
	if(x>y)return;
	if(x<=l&&y>=r){update(k,val,opt);return;}
	pushdown(k);
	int mid=(l+r)>>1;
	if(x<=mid)modify(ls,l,mid,x,y,val,opt);
	if(y>mid)modify(rs,mid+1,r,x,y,val,opt);
	tree[k].f[0]=max(tree[ls].f[0],tree[rs].f[0]);
	tree[k].f[1]=max(tree[ls].f[1],tree[rs].f[1]);
}
int query(int k,int l,int r,int x,int y,bool opt){
	if(x>y)return -INF;
	if(x<=l&&y>=r)return tree[k].f[opt];
	pushdown(k);
	int mid=(l+r)>>1;
	int ans=-INF;
	if(x<=mid)ans=max(ans,query(ls,l,mid,x,y,opt));
	if(y>mid)ans=max(ans,query(rs,mid+1,r,x,y,opt));
	return ans;
}
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int n,q;
	cin>>n>>q;
	for(int i=1;i<=n;i++)cin>>a[i];
	build(1,1,n);
	while(q--){
		int opt,l,r;
		cin>>opt>>l>>r;
		if(opt==1){
			int x;
			cin>>x;
			if(l>=2)modify(1,1,n,l,l,x,0);
			if(l>=3)modify(1,1,n,l,l,x,1);
			if(l+1>=3&&l+1<=n&&r-l+1>=2)modify(1,1,n,l+1,l+1,2*x,1);
			modify(1,1,n,l+1,r,2*x,0);
			modify(1,1,n,l+2,r,3*x,1);
			if(r+1<=n)modify(1,1,n,r+1,r+1,x,0);
			if(r+1<=n&&r-l+1>=2)modify(1,1,n,r+1,r+1,2*x,1);
			if(r+2<=n)modify(1,1,n,r+2,r+2,x,1);
		}
		else{
			int ans1=query(1,1,n,l+1,r,0);
			int ans2=query(1,1,n,l+2,r,1);
			int ans3,ans4;
			if((__int128)ans1*3>(__int128)ans2*2)ans3=ans1,ans4=2;
			else ans3=ans2,ans4=3;
			if(ans3==0){cout<<"1 0 1\n";}
			else{
				int gcd=__gcd(llabs(ans3),llabs(ans4));
				ans3/=gcd,ans4/=gcd;
				if(ans4<0)ans3=-ans3,ans4=-ans4;
				cout<<"1 "<<ans3<<" "<<ans4<<"\n";
			}
		}
	}
}