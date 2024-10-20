#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1e5+10;
const ll INF=1e18;
int n,T;
int d[N],m[N];
struct node{
	int opt,p,f,v;
}q[N];
void solve1(){
	for(int j=1;j<=T;j++){
		int opt=q[j].opt,p=q[j].p,f=q[j].f,v=q[j].v;
		if(opt==1)d[p]=f;
		else m[p]=f;
		ll ans=INF;
		ll s=0;
		for(int i=1;i<=n;i++){
			s+=d[i];
			ans=min(ans,s+(ll)m[i]*v);
		}
		cout<<ans<<"\n";
	}
}
namespace solve2{
	struct node2{
		ll Min,lazy;
	}tree[N<<2];
	#define ls k<<1
	#define rs k<<1|1
	void update(int k,ll val){
		tree[k].lazy+=val;
		tree[k].Min+=val;
	}
	void pushdown(int k){
		if(tree[k].lazy){
			update(ls,tree[k].lazy);
			update(rs,tree[k].lazy);
			tree[k].lazy=0;
		}
	}
	void pushup(int k){
		tree[k].Min=min(tree[ls].Min,tree[rs].Min);
	}
	void modify(int k,int l,int r,int x,int y,ll val){
		if(x<=l&&y>=r){update(k,val);return;}
		pushdown(k);
		int mid=(l+r)>>1;
		if(x<=mid)modify(ls,l,mid,x,y,val);
		if(y>mid)modify(rs,mid+1,r,x,y,val);
		pushup(k);
	}
	ll query(){return tree[1].Min;}
	void solve2(){//区间加，区间查询最小值
		int v=q[1].v;
		for(int i=1;i<=n;i++){
			modify(1,1,n,i,n,d[i]);
			modify(1,1,n,i,i,(ll)m[i]*v);
		}
		for(int j=1;j<=T;j++){
			int opt=q[j].opt,p=q[j].p,f=q[j].f;
			if(opt==1)modify(1,1,n,p,n,(ll)(f-d[p])),d[p]=f;
			else modify(1,1,n,p,p,(ll)(f-m[p])*(ll)v),m[p]=f;
			cout<<query()<<"\n";
		}
	}
};
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	freopen("bus.in","r",stdin);
	freopen("bus.out","w",stdout);
	cin>>n>>T;
	for(int i=1;i<=n;i++)cin>>d[i];
	for(int i=1;i<=n;i++)cin>>m[i];
	bool flag=true;
	int v=-1;
	for(int i=1;i<=T;i++){
		cin>>q[i].opt>>q[i].p>>q[i].f>>q[i].v;
		if(v==-1)v=q[i].v;
		else if(q[i].v!=v)flag=false;
	}
	if(flag)solve2::solve2();
	else solve1();

}