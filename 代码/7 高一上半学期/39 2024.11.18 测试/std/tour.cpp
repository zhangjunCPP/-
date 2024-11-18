#include<bits/stdc++.h>
using namespace std;

const int N=1e5+5,MOD=998244353;
int n,q,a[N];
const int E=N<<1;
int tot=0,hd[N],to[E],nxt[E];
inline void Add(int u,int v){to[++tot]=v;nxt[tot]=hd[u];hd[u]=tot;}
#define go(ck) for(int i=hd[u];i;i=nxt[i])if(int v=to[i];ck)

const int B=256;
int fa[N],dep[N],sz[N],sn[N],ct[N];
void dfs1(int u,int f){
	fa[u]=f;dep[u]=dep[f]+1;sz[u]=1;
	for(int x=u,r=10;x&&~r;x=fa[x],r--)ct[x]++;
	for(int i=hd[u];i;i=nxt[i])if(int v=to[i];v^f){
		dfs1(v,u);sz[u]+=sz[v];sz[v]>sz[sn[u]]&&(sn[u]=v);
	}
}
int idx=0,id[N],L[N],R[N],L2[11][N],R2[11][N];
basic_string<int>P[11][N];
void dfs2(int u){
	if(ct[u]>B){
		queue<int>q;q.push(u);
		while(!q.empty()){
			int x=q.front();q.pop();
			if(!id[x]){
				id[x]=++idx;
				for(int r=0,y=x;r<=dep[x]-dep[u];y=fa[y],r++){
					if(!L2[r][y])L2[r][y]=idx;
					R2[r][y]=idx;
				}
			}
			if(dep[x]==dep[u]+10)continue;
			if(sn[x])q.push(sn[x]);
			for(int i=hd[x];i;i=nxt[i])if(int y=to[i];y^fa[x]&&y^sn[x])q.push(y);
		}
	}
	L[u]=idx+1;if(!id[u])id[u]=++idx;
	if(sn[u])dfs2(sn[u]);
	for(int i=hd[u];i;i=nxt[i])if(int v=to[i];v^fa[u]&&v^sn[u])dfs2(v);
	R[u]=idx;
	P[0][u]+=id[u];
	for(int i=hd[u];i;i=nxt[i])if(int v=to[i];v^fa[u])
		for(int j=1;j<=10;j++)P[j][u]+=P[j-1][v];
}
int tp[N];
void dfs3(int u,int t){
	tp[u]=t;if(sn[u])dfs3(sn[u],id[sn[u]]==id[u]+1?t:sn[u]);
	for(int i=hd[u];i;i=nxt[i])if(int v=to[i];v^fa[u]&&v^sn[u])dfs3(v,v);
}

typedef long long ll;
typedef pair<ll,ll> pi;
#define fi first
#define se second
inline ll ksm(ll x){ll r=1;for(int y=MOD-2;y;y>>=1,x=x*x%MOD)if(y&1)r=r*x%MOD;return r;}
inline void operator+=(pi&x,pi y){x.fi=x.fi*y.fi%MOD;x.se=(x.se*y.fi+y.se)%MOD;}
inline ll operator*(ll x,pi y){return(x*y.fi+y.se)%MOD;}
pi tr[N<<2];
#define ls p<<1
#define rs p<<1|1
#define md (l+r>>1)
#define Ls ls,l,md
#define Rs rs,md+1,r
#define al 1,1,n
inline void pd(int p){if(tr[p]!=pi(1,0)){tr[ls]+=tr[p];tr[rs]+=tr[p];tr[p]=pi(1,0);}}
void bld(int p,int l,int r){tr[p]=pi(1,0);if(l==r)return;bld(Ls);bld(Rs);}
void upd(int p,int l,int r,int L,int R,pi k){if(L<=l&&r<=R){tr[p]+=k;return;}pd(p);if(L<=md)upd(Ls,L,R,k);if(R>md)upd(Rs,L,R,k);}
pi qry(int p,int l,int r,int x){if(l==r)return tr[p];pd(p);return x<=md?qry(Ls,x):qry(Rs,x);}
inline void mdf(int u,int r,pi k){
	if(L2[r][u])upd(al,L2[r][u],R2[r][u],k);
	else for(int x:P[r][u])upd(al,x,x,k);
}
int main(){

	scanf("%*d%d%d",&n,&q);
	for(int i=1,u,v;i<n;i++){scanf("%d%d",&u,&v);Add(u,v);Add(v,u);}
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	dfs1(1,0);dfs2(1);dfs3(1,1);bld(al);
	for(int o,x,y,r,k,b;q--;){
		scanf("%d%d",&o,&x);
		if(o==1)
			printf("%lld\n",a[x]*qry(al,id[x]));
		else if(o==2){
			scanf("%d%d%d",&y,&k,&b);pi v=pi(k,b);
			for(;tp[x]^tp[y];x=fa[tp[x]]){
				if(dep[tp[x]]<dep[tp[y]])swap(x,y);
				upd(al,id[tp[x]],id[x],v);
			}
			if(id[x]>id[y])swap(x,y);upd(al,id[x],id[y],v);
		}else if(o==3){
			scanf("%d%d",&k,&b);pi v=pi(k,b);
			for(int i=0;i<=10&&L2[i][x];i++)upd(al,L2[i][x],R2[i][x],v);
			if(L[x]<=R[x])upd(al,L[x],R[x],v);
		}else if(o==4){
			scanf("%d%d%d",&r,&k,&b);pi v=pi(k,b);
			for(;;x=fa[x],r--){
				if(x==1){for(;~r;r--)mdf(x,r,v);break;}
				if(!r){upd(al,id[x],id[x],v);break;}
				mdf(x,r,v);mdf(x,r-1,v);
			}
		}
	}
	return 0;
}