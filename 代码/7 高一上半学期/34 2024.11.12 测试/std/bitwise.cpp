#include<bits/stdc++.h>
#define Gc() getchar()
#define Me(x,y) memset(x,y,sizeof(x))
#define Mc(x,y) memcpy(x,y,sizeof(x))
#define d(x,y) ((m)*(x-1)+(y))
#define R(n) (rnd()%(n)+1)
#define Pc(x) putchar(x)
#define LB lower_bound
#define UB upper_bound
#define fi first
#define se second
#define eb emplace_back
#define all(x) x.begin(),x.end()
using namespace std;using ll=long long;using db=double;using lb=long db;using ui=unsigned;using ull=unsigned long long;using pii=pair<int,int>;
const int N=(1<<18)+5,M=N*4+5,K=1e7+5,mod=998244353,Mod=mod-1;const db eps=1e-9;const ll INF=1e13+7;mt19937 rnd(263082);
#define Tp template<typename T>
#define Ts template<typename T,typename... Ar>
namespace Debug{
	Tp void _debug(char* f,T t){cerr<<f<<'='<<t<<endl;}
	Ts void _debug(char* f,T x,Ar... y){while(*f!=',') cerr<<*f++;cerr<<'='<<x<<",";_debug(f+1,y...);}
	#ifdef LOCAL
	#define gdb(...) _debug((char*)#__VA_ARGS__,__VA_ARGS__)
	#else
	#define gdb(...) void()
	#endif
}using namespace Debug;
int n,m,A[N];ll ans[M];
using info=vector<tuple<int,int,int> >;
int w1[N],w2[N];
info calc(int l,int r){
	if(l==r){
		return info({make_tuple(A[l],A[l],1)});
	}
	int m=l+r>>1;
	info L=calc(l,m),R=calc(m+1,r);
	info f;
	int mx=0,mi=n+1;
	for(int i=m+1;i<=r;i++) mx=max(mx,A[i]),mi=min(mi,A[i]);
	for(int i=l;i<=m;i++) w1[A[i]]=w2[A[i]]=0;
	for(auto [x,y,z]:L){
		if(x<=mi&&mx<=y) f.emplace_back(x,y,z+(r-l+1>>1));
		else{
			f.emplace_back(x,y,z);
			if(x>mi) w1[y]=max(w1[y],z+(r-l+1>>1));
			if(y<mx) w2[x]=max(w2[x],z+(r-l+1>>1));
		}
	}
	for(int i=l;i<=m;i++){
		if(w1[A[i]]) f.emplace_back(mi,max(A[i],mx),w1[A[i]]);
		if(w2[A[i]]) f.emplace_back(min(A[i],mi),mx,w2[A[i]]);
	}
	mx=0,mi=n+1;
	for(int i=l;i<=m;i++) mx=max(mx,A[i]),mi=min(mi,A[i]);
	for(int i=m+1;i<=r;i++) w1[A[i]]=w2[A[i]]=0;
	for(auto [x,y,z]:R){
		if(x<=mi&&mx<=y) f.emplace_back(x,y,z+(r-l+1>>1));
		else{
			f.emplace_back(x,y,z);
			if(x>mi) w1[y]=max(w1[y],z+(r-l+1>>1));
			if(y<mx) w2[x]=max(w2[x],z+(r-l+1>>1));
		}
	}
	for(int i=m+1;i<=r;i++){
		if(w1[A[i]]) f.emplace_back(mi,max(A[i],mx),w1[A[i]]);
		if(w2[A[i]]) f.emplace_back(min(A[i],mi),mx,w2[A[i]]);
	}
	if(r-l+1>=(1<<16)) gdb(l,r);
	return f;
}
vector<pii> S[N],Q[N];
namespace Tree{
	#define ls v<<1
	#define rs v<<1|1
	int mi[M],mx[M],g[M],siz[M],f[M];
	ll ad[M],sum[M],ans[M];
	void Pf(int v,int w,int pw,ll sw){
		if(~f[v]) sw+=1ll*w*f[v];
		else g[v]+=w,ans[v]+=sum[v]*w;
		if(~pw) f[v]=mi[v]=mx[v]=pw,sum[v]=1ll*pw*siz[v];
		ad[v]+=sw;ans[v]+=sw*siz[v];
	}
	void P(int v){
		if(g[v]||~f[v]||ad[v]) Pf(ls,g[v],f[v],ad[v]),Pf(rs,g[v],f[v],ad[v]),f[v]=-1,g[v]=ad[v]=0;
	}
	void up(int v){
		sum[v]=sum[ls]+sum[rs];ans[v]=ans[ls]+ans[rs];
		mi[v]=min(mi[ls],mi[rs]);mx[v]=max(mx[ls],mx[rs]);
	}
	void build(int l=1,int r=n,int v=1){
		g[v]=-1;siz[v]=r-l+1;
		if(l==r) return;
		int m=l+r>>1;build(l,m,ls);build(m+1,r,rs);up(v);
	}
	void add(int x,int y,int l=1,int r=n,int v=1){
		if(x<=l&&r<=y) return Pf(v,1,-1,0);int m=l+r>>1;P(v);
		x<=m&&(add(x,y,l,m,ls),0);y>m&&(add(x,y,m+1,r,rs),0);up(v);
	}
	void modify(int x,int y,int w,int l=1,int r=n,int v=1){
		if(mi[v]>=w) return;
		if(x<=l&&r<=y&&mx[v]<=w) return Pf(v,0,w,0);
		int m=l+r>>1;P(v);
		x<=m&&(modify(x,y,w,l,m,ls),0);y>m&&(modify(x,y,w,m+1,r,rs),0);up(v);
	}
	ll qry(int x,int y,int l=1,int r=n,int v=1){
		if(x<=l&&r<=y) return ans[v];int m=l+r>>1;P(v);
		return (x<=m?qry(x,y,l,m,ls):0)+(y>m?qry(x,y,m+1,r,rs):0);
	}
	#undef ls
	#undef rs
}
void Solve(){
	scanf("%d%d",&n,&m);n=(1<<n);
	for(int i=1;i<=n;i++){
		int x;scanf("%d",&x);
		A[x]=i;
	}
	auto p=calc(0,n-1);gdb(p.size());
	for(auto [x,y,z]:p) S[y].emplace_back(x,z);
	for(int i=1;i<=m;i++){
		int x,y;scanf("%d%d",&x,&y);
		Q[y].emplace_back(x,i);
	}
	Tree::build();
	for(int i=1;i<=n;i++){
		for(auto j:S[i]) Tree::modify(1,j.fi,j.se);
		Tree::add(1,i);
		for(auto j:Q[i]) ans[j.se]=Tree::qry(j.fi,i);
	}
	for(int i=1;i<=m;i++) printf("%lld\n",ans[i]);
}
int main(){
	int t=1;
	// scanf("%d",&t);
	while(t--) Solve();
	cerr<<clock()*1.0/CLOCKS_PER_SEC<<'\n';
}