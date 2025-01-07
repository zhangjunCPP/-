#include<bits/stdc++.h>
#define ls (k<<1)
#define rs (k<<1|1)
using namespace std;
const int N=1e6+10,INF=1e9;
int a[N];
struct node{
	int mx,p;
}tree[N];
int query(int k,int l,int r,int x){
	if(l==r)return tree[k].mx>x?x+l:INF;
	int mid=(l+r)>>1;
	return tree[rs].mx>x?min(tree[k].p,query(rs,mid+1,r,x)):query(ls,l,mid,x);
}
void pushup(int k,int l,int r){
	tree[k].mx=max(tree[ls].mx,tree[rs].mx);
	int mid=(l+r)>>1;
	tree[k].p=query(ls,l,mid,tree[rs].mx);
}
void build(int k,int l,int r){
	if(l==r){tree[k].mx=a[l]-l;return;}
	int mid=(l+r)>>1;
	build(ls,l,mid);
	build(rs,mid+1,r);
	pushup(k,l,r);
}
void update(int k,int l,int r,int x,int y){
	if(l==r){tree[k].mx=y-l;return;}
	int mid=(l+r)>>1;
	if(x<=mid)update(ls,l,mid,x,y);
	else update(rs,mid+1,r,x,y);
	pushup(k,l,r);
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr),cout.tie(nullptr);
	int n,m,p;
	cin>>n>>m>>p;
	for(int i=1;i<=n;i++)cin>>a[i];
	build(1,1,n);
	int lastans;		
	cout<<(lastans=query(1,1,n,tree[1].mx-n)+n)<<"\n";
	while(m--){
		int x,y;
		cin>>x>>y;
		if(p)x^=lastans,y^=lastans;
		update(1,1,n,x,y);
		cout<<(lastans=query(1,1,n,tree[1].mx-n)+n)<<"\n";
	}
}