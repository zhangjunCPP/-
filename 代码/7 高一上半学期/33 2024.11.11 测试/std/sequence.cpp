#include<bits/stdc++.h>
using namespace std;
#ifdef DEBUG
#include"debug.h"
#else
#define debug(...) void()
#endif
#define all(x) (x).begin(),(x).end()
template<class T>
auto ary(T *a,int l,int r){
	return vector<T>{a+l,a+1+r};
}
using ll=long long;
using ull=unsigned long long;
const int N=2e5+10;
int T,n,k,m,a[N],b[N];
vector<int>pos[N];
int mx[N<<2],sum[N<<2],laz[N<<2];
void pushup(int rt){
	mx[rt]=max(mx[rt<<1],mx[rt<<1|1]);
	sum[rt]=(mx[rt]==mx[rt<<1]?sum[rt<<1]:0)+(mx[rt]==mx[rt<<1|1]?sum[rt<<1|1]:0);
	mx[rt]+=laz[rt];
}
void build(int l=1,int r=n,int rt=1){
	laz[rt]=0;
	if(l==r)return mx[rt]=0,sum[rt]=1,void();
	int mid=(l+r)>>1;
	build(l,mid,rt<<1);
	build(mid+1,r,rt<<1|1);
	pushup(rt);
}
void update(int L,int R,int x,int l=1,int r=n,int rt=1){
	if(L>R)return;
	if(L<=l&&r<=R)return mx[rt]+=x,laz[rt]+=x,void();
	int mid=(l+r)>>1;
	if(L<=mid)update(L,R,x,l,mid,rt<<1);
	if(mid<R)update(L,R,x,mid+1,r,rt<<1|1);
	pushup(rt);
}
void modify(int x,int y,int l=1,int r=n,int rt=1){
	if(l==r)return mx[rt]=y,void();
	int mid=(l+r)>>1;
	y-=laz[rt];
	if(x<=mid)modify(x,y,l,mid,rt<<1);
	else modify(x,y,mid+1,r,rt<<1|1);
	pushup(rt);
}
int p[N];
int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]),b[i]=a[i];
	sort(b+1,b+1+n),m=unique(b+1,b+1+n)-b-1;
	for(int i=1;i<=n;i++)a[i]=lower_bound(b+1,b+1+m,a[i])-b;
	for(int i=1;i<=n;i++){
		p[i]=pos[a[i]].size(),pos[a[i]].push_back(i);
	}
	build();
	ll ans=0;
	for(int i=1;i<=n;i++){
		int c=a[i],t=p[i];
		update(t>0?pos[c][t-1]+1:1,i,-1);
		if(t>=k)update(t>k?pos[c][t-k-1]+1:1,pos[c][t-k],-1);
		if(t+1>=k)update(t>=k?pos[c][t-k]+1:1,pos[c][t-k+1],1);
		modify(i,m-(k>1));
		if(mx[1]==m)ans+=sum[1];
	}
	printf("%lld\n",ans);
	return 0;
}
#ifdef DEBUG
#include"debug.hpp"
#endif