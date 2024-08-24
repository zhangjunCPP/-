#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e5+10;
struct node {
	int l,r,val;
}a[N];
struct node2 {
	int Max,lazy;
}tree[N<<2];
int ls(int k){return k<<1;}
int rs(int k){return k<<1|1;}

void pushup(int k){tree[k].Max=max(tree[ls(k)].Max,tree[rs(k)].Max);}
void update(int k,int lazy){tree[k].Max+=lazy,tree[k].lazy+=lazy;}
void pushdown(int k) {
	if(tree[k].lazy) {
		update(ls(k),tree[k].lazy);
		update(rs(k),tree[k].lazy);
		tree[k].lazy=0;
	}
}
void modify(int k,int l,int r,int x,int y,int val) {
	if(x>r||y<l)return;
	if(x<=l&&y>=r) {
		update(k,val);
		return;
	}
	pushdown(k);
	int mid=(l+r)>>1;
	if(x<=mid)modify(ls(k),l,mid,x,y,val);
	if(y>mid)modify(rs(k),mid+1,r,x,y,val);
	pushup(k);
}
int query(int k,int l,int r,int x) {
	if(l==r)return tree[k].Max;
	pushdown(k);
	int mid=(l+r)>>1;
	if(x<=mid)return query(ls(k),l,mid,x);
	else return query(rs(k),mid+1,r,x);
}
vector<int>G[N];
signed main() {
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	freopen("hard.in","r",stdin);
	freopen("hard.out","w",stdout);
	int n,m,w;
	cin>>n>>m>>w;
	for(int i=1;i<=m;i++) {
		cin>>a[i].l>>a[i].r>>a[i].val;
		if(a[i].val!=-1)modify(1,1,n,a[i].l,a[i].r,a[i].val);
		else G[a[i].l].push_back(i),G[a[i].r+1].push_back(i),a[i].val=w;
	}
	for(int i=1;i<=n;i++) {
		for(auto it:G[i])modify(1,1,n,a[it].l,a[it].r,a[it].val),a[it].val=-a[it].val;
		cout<<(query(1,1,n,i)>=tree[1].Max);
	}
}
/*
 *第i个知识点的考察范围为l~r
 *那我们可以在l处加贡献，在r+1处减贡献，而不需要每次单独算
 *现需要单点求值，区间加，区间max
 */