#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=5e4+10;
const int INF=1e9;
ll n,m;
int Max;
int a[N];
int block;
struct node{
	int l,r,id;
}q[N];
bool cmp(node x,node y){
	if(x.l/block!=y.l/block) return x.l<y.l;
	return (x.l/block)&1?x.r<y.r:x.r>y.r;
}
struct node2{
	ll sum,val1,val2;
}tree[N*4];
#define ls (k<<1)
#define rs (k<<1|1)
inline void pushup(int k){
	tree[k].sum=tree[ls].sum+tree[rs].sum;
	tree[k].val1=tree[ls].val1+tree[rs].val1;
	tree[k].val2=tree[ls].val2+tree[rs].val2;
}
void insert(int k,int l,int r,int x,int val){
	if(l==r){
		tree[k].sum+=val;
		tree[k].val1+=val*l;
		tree[k].val2+=(n-l)*val;
		return;
	}
	int mid=(l+r)>>1;
	if(x<=mid)insert(ls,l,mid,x,val);
	else insert(rs,mid+1,r,x,val);
	pushup(k);
}
ll ask(int k,int l,int r,int x){
	if(l==r)return 0;
	int mid=(l+r)>>1;
	if(x<=mid){
		ll sum=(n-x)*tree[rs].sum-tree[rs].val2;
		return sum+ask(ls,l,mid,x);
	}
	else{
		ll sum=x*tree[ls].sum-tree[ls].val1;
		return sum+ask(rs,mid+1,r,x);
	}
}
ll ans[N];
multiset<int>up,down;
inline void update(){
	while(down.size()>up.size()+1){
		auto it=(--down.end());
		up.emplace(*it);
		down.erase(it);
	}
	while(up.size()>down.size()){
		auto it=up.begin();
		down.emplace(*it);
		up.erase(it);
	}
}
inline void add(int x){
	insert(1,1,Max,x,1);
	if(x<=*up.begin())down.emplace(x);
	else up.emplace(x);
}
inline void del(int x){
	insert(1,1,Max,x,-1);
	auto it=down.lower_bound(x);
	if(it!=down.end())down.erase(it);
	else up.erase(up.lower_bound(x));
}
const ll mod=4294967296;
signed main(){	
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i],Max=max(Max,a[i]);
	for(int i=1;i<=m;i++)cin>>q[i].l>>q[i].r,q[i].id=i;
	block=250;
	sort(q+1,q+m+1,cmp);
	int l=1,r=0;
	up.emplace(INF),down.emplace(-INF);
	for(int i=1;i<=m;i++){
		while(l>q[i].l)add(a[--l]);
		while(r<q[i].r)add(a[++r]);
		while(l<q[i].l)del(a[l++]);
		while(r>q[i].r)del(a[r--]);
		update();
		ans[q[i].id]=ask(1,1,Max,*down.rbegin());
	}
	for(int i=1;i<=m;i++)cout<<ans[i]%mod<<"\n";
}