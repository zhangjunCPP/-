#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=5e4+10;
const int INF=1e9;
ll n,m;
int Max;
int a[N];
struct node2{
	int ls,rs;
	ll sum,val1,val2;
}tree[N*32];
int tot;
void pushup(int k){
	tree[k].sum=tree[tree[k].ls].sum+tree[tree[k].rs].sum;
	tree[k].val1=tree[tree[k].ls].val1+tree[tree[k].rs].val1;
	tree[k].val2=tree[tree[k].ls].val2+tree[tree[k].rs].val2;
}
void insert(int rtt,int &k,int l,int r,int x){
	k=++tot;
	tree[k]=tree[rtt];
	if(l==r){
		tree[k].sum++;
		tree[k].val1+=l;
		tree[k].val2+=n-l;
		return;
	}
	int mid=(l+r)>>1;
	if(x<=mid)insert(tree[rtt].ls,tree[k].ls,l,mid,x);
	else insert(tree[rtt].rs,tree[k].rs,mid+1,r,x);
	pushup(k);
}
int query(int rt1,int rt2,int l,int r,int x){
	if(l==r)return l;
	int sum=tree[tree[rt1].ls].sum-tree[tree[rt2].ls].sum;
	// cout<<"l="<<l<<" r="<<r<<" sum="<<sum<<"\n";
	int mid=(l+r)>>1;
	if(x<=sum)return query(tree[rt1].ls,tree[rt2].ls,l,mid,x);
	return query(tree[rt1].rs,tree[rt2].rs,mid+1,r,x-sum);
}
ll ask(int rt1,int rt2,int l,int r,int x){
	if(l==r)return 0;
	int mid=(l+r)>>1;
	if(x<=mid){
		ll sum=(n-x)*(tree[tree[rt1].rs].sum-tree[tree[rt2].rs].sum)-(tree[tree[rt1].rs].val2-tree[tree[rt2].rs].val2);
		return sum+ask(tree[rt1].ls,tree[rt2].ls,l,mid,x);
	}
	else{
		ll sum=x*(tree[tree[rt1].ls].sum-tree[tree[rt2].ls].sum)-(tree[tree[rt1].ls].val1-tree[tree[rt2].ls].val1);
		return sum+ask(tree[rt1].rs,tree[rt2].rs,mid+1,r,x);
	}
}
const ll mod=4294967296;
int rt[N];
signed main(){	
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i],Max=max(Max,a[i]);
	for(int i=1;i<=n;i++)insert(rt[i-1],rt[i],1,Max,a[i]);
	for(int i=1;i<=m;i++){
		int l,r;
		cin>>l>>r;
		int mid=query(rt[r],rt[l-1],1,Max,(r-l+2)/2);
		cout<<ask(rt[r],rt[l-1],1,Max,mid)%mod<<"\n";
	}
}