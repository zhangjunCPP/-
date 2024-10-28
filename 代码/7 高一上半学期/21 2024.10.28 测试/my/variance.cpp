#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+10;
int a[N];
struct node{
	int x,y;
	bool opt;
	node(int _x=0,int _y=0,bool _opt):x(_x),y(_y),opt(_opt){
		if(x==0){x=0,y=1;}
		else{
			int gcd=llabs(__gcd(x,y));
			x/=gcd,y/=gcd;
		}
	}
	bool operator<(const node&oth)const{return (__int128)x*oth.y<(__int128)oth.x*y;}
	bool operator==(const node&oth)const{return (__int128)x*oth.y==(__int128)oth.x*y;}
	bool operator>(const node&oth)const{
		if(!x&&!y)return false;
		if(!oth.x&&!oth.y)return true;
		return (__int128)x*oth.y>(__int128)oth.x*y;
	}
};
// struct node2{
// 	int lazy;
// 	int lval1,lval2;
// 	int rval1,rval2;
// 	node ans1,ans2;
// }tree[N<<2];
// #define ls (k<<1)
// #define rs (k<<1|1)
// void build(int k,int l,int r){
// 	if(l==r){
// 		tree[k].lval1=a[l];
// 		tree[k].lval2=a[l];
// 		tree[k].rval1=a[l];
// 		tree[k].rval2=a[l];
// 		tree[k].lazy=0;
// 		return;
// 	}
// 	int mid=(l+r)>>1;
// 	build(ls,l,mid);
// 	build(rs,mid+1,r);
// 	tree[k].lval1=tree[ls].lval1;
// 	tree[k].lval2=tree[ls].lval2;
// 	tree[k].rval1=tree[ls].rval1;
// 	tree[k].rval2=tree[ls].rval2;
// 	if(r==l+1){tree[k].ans1={tree[ls].lval1+tree[rs].lval1,2};return;}
// 	tree[k].ans1=max({tree[ls].ans1,tree[rs].ans1,{tree[ls].rval1+tree[rs].lval1,2}});
// 	tree[k].ans2=max({tree[ls].ans2,tree[rs].ans2,{tree[ls].rval1+tree[ls].rval2+tree[rs].lval1,3},{tree[ls].rval1+tree[rs].lval2+tree[rs].lval1,3}});
// }
// void update(int k,int l,int r,int val){
// 	tree[k].lazy+=val;
// 	tree[k].lval1+=val;
// 	tree[k].lval2+=val;
// 	tree[k].rval1+=val;
// 	tree[k].rval2+=val;
// }
// void pushdown(int k,int l,int r){
// 	if(tree[k].lazy){
// 		int mid=(l+r)>>1;
// 		update(ls,l,mid,tree[k].lazy);
// 		update(rs,mid+1,r,tree[k].lazy);
// 		tree[k].lazy=0;
// 	}
// }
// void modify(int k,int l,int r,int x,int y,int val){
// 	if(x<=l&&y>=r){update(k,l,r,val);return;}
// 	pushdown(k,l,r);
// 	int mid=(l+r)>>1;
// 	if(x<=mid)modify(ls,l,mid,x,y,val);
// 	if(y>mid)modify(rs,mid+1,r,x,y,val);
// 	tree[k].lval1=tree[ls].lval1;
// 	tree[k].lval2=tree[ls].lval2;
// 	tree[k].rval1=tree[ls].rval1;
// 	tree[k].rval2=tree[ls].rval2;
// 	if(r==l+1){tree[k].ans1={tree[ls].lval1+tree[rs].lval1,2};return;}
// 	tree[k].ans1=max({tree[ls].ans1,tree[rs].ans1,{tree[ls].rval1+tree[rs].lval1,2}});
// 	tree[k].ans2=max({tree[ls].ans2,tree[rs].ans2,{tree[ls].rval1+tree[ls].rval2+tree[rs].lval1,3},{tree[ls].rval1+tree[rs].lval2+tree[rs].lval1,3}});
// }
// node query(){
// 	return max(tree[1].ans1,tree[1].ans2);
//
// }
signed main(){
	freopen("variance.in","r",stdin);
	freopen("variance.out","w",stdout);
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int n,q;
	cin>>n>>q;
	for(int i=1;i<=n;i++)cin>>a[i];
	while(q--){
		int opt,l,r;
		cin>>opt>>l>>r;
		if(opt==1){
			int x;
			cin>>x;
			for(int i=l;i<=r;i++)a[i]+=x;
		}
		else{
			node ans={a[l]+a[l+1],2};
			for(int i=l+1;i<=r-1;i++){
				ans=max(ans,{a[i]+a[i+1],2});
				ans=max(ans,{a[i]+a[i-1]+a[i+1],3});
			}
			cout<<"1 "<<ans.x<<" "<<ans.y<<"\n";
		}
	}
}