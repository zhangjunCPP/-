#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int maxn=5e5+5;
const ll INF=1e18;
ll val[maxn];
int n,m;
vector<int> T[maxn<<2],T2[maxn<<2];
#define lc (rt<<1)
#define rc (rt<<1|1)
inline void add(int rt,int l,int r,int Ll,int Rr,int id){
	T2[rt].push_back(id);
	if(Ll<=l && r<=Rr){
		T[rt].push_back(id);
		return ;
	}
	int mid=(l+r)>>1;
	if(Ll<=mid) add(lc,l,mid,Ll,Rr,id);
	if(Rr>mid) add(rc,mid+1,r,Ll,Rr,id);
}
int vis[maxn];
inline int query(int rt,int l,int r,int pos){
	int ret=-1;
	while(T[rt].size() && vis[T[rt].back()]) T[rt].pop_back();
	if(T[rt].size()) ret=T[rt].back();
	if(l==r) return ret;
	int mid=(l+r)>>1;
	if(pos<=mid) return max(ret,query(lc,l,mid,pos));
	return max(ret,query(rc,mid+1,r,pos));
}
inline int query2(int rt,int l,int r,int L,int R){
	while(T2[rt].size() && vis[T2[rt].back()]) T2[rt].pop_back();
	if(L<=l && r<=R){
		if(T2[rt].size()) return T2[rt].back();
		return -1;
	}
	int ret=-1;
	int mid=(l+r)>>1;
	if(L<=mid) ret=max(ret,query2(lc,l,mid,L,R));
	if(R>mid) ret=max(ret,query2(rc,mid+1,r,L,R));
	return ret;
}
int L[maxn],R[maxn];
int main(){
	scanf("%d%d",&n,&m);
	val[0]=INF;
	L[0]=1,R[0]=n;
	add(1,1,n,1,n,0);
	for(int i=1,op,l,r;i<=m;i++){
		ll d;
		scanf("%d%d%d%lld",&op,&l,&r,&d);
		if(op==1){
			L[i]=l,R[i]=r,val[i]=d;
			add(1,1,n,L[i],R[i],i);
		}
		else{
			while(d){
				int x=max({query(1,1,n,l),query(1,1,n,r),query2(1,1,n,l,r)});
				ll ret=min(val[x],d);
				d-=ret;
				val[x]-=ret;
				printf("%d ",x);
				if(val[x]==0) vis[x]=1;
			}
			printf("\n");
		}
	}
	return 0;
}