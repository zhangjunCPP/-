#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=7e5+10;
int n,a[N];
int id[N];

int root[N],tot;
struct node{
	int ls,rs,val;
}tree[N<<5];


int clone(int k){
	++tot;
	tree[tot]=tree[k];
	return tot;
}

int build(int l,int r,int k,int x){
	k=clone(k);
	tree[k].val++;
	if(l==r)return k;
	int mid=(l+r)>>1;
	if(x<=mid)tree[k].ls=build(l,mid,tree[k].ls,x);
	else tree[k].rs=build(mid+1,r,tree[k].rs,x);
	return k;
}

int query(int l,int r,int x,int y,int val){
	if(l==r)return l;
	int mid=(l+r)>>1;
	int tmp=tree[tree[y].ls].val-tree[tree[x].ls].val;
	if(val<=tmp) return query(l,mid,tree[x].ls,tree[y].ls,val);
	else return query(mid+1,r,tree[x].rs,tree[y].rs,val-tmp);
}


int ans;
void solve(int l,int r){
	if(l>=r)return;
	int len=r-l+1;
	ans+=len;
	int tmp=query(1,n,root[l-1],root[r],(len+1)/2);
	int mid=a[tmp];
	solve(l,mid-1),solve(mid+1,r);
}


signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		id[a[i]]=i;
	}
	for(int i=1;i<=n;i++) root[i]=build(1,n,root[i-1],id[i]);
	solve(1,n);
	cout<<ans;
	return 0;
}
