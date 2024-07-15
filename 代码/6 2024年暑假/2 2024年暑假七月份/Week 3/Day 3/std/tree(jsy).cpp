#include<bits/stdc++.h>
using namespace std;
using i64=long long;
constexpr i64 mod=998244353;
namespace ds{
constexpr int N=5000010;
int tot;
struct T_{
   i64 x,y;
   void apply(T_ o){
      (y+=x*o.y)%=mod,(x*=o.x)%=mod;
   }
}tag[N];
struct N_{
   i64 s,hs;
   void apply(T_ o){
      (hs+=s*o.y)%=mod,(s*=o.x)%=mod;
   }
}info[N];
int ls[N],rs[N];
inline void apply(int u,T_ x){
   tag[u].apply(x),info[u].apply(x);
}
inline void pushdown(int u){
   apply(ls[u],tag[u]),apply(rs[u],tag[u]);
   tag[u]={1,0};
}
inline void pushup(int u){
   info[u].s=(info[ls[u]].s+info[rs[u]].s)%mod;
}
int merge(int x,int y,i64 sx,i64 sy){
   if(!x&&!y)return 0;
   if(x&&!y)return apply(x,{sy+1,0}),x;
   if(!x&&y)return apply(y,{sx+1,0}),y;
   if(!ls[x]&&!rs[x]){
      (info[x].hs+=info[y].hs)%=mod;
      info[x].s=(info[x].s*(sy+info[y].s+1)+info[y].s*(sx+info[x].s+1)+(mod-info[x].s)*info[y].s)%mod;
      return x;
   }
   pushdown(x),pushdown(y);
   rs[x]=merge(rs[x],rs[y],(sx+info[ls[x]].s)%mod,(sy+info[ls[y]].s)%mod);
   ls[x]=merge(ls[x],ls[y],sx,sy);
   pushup(x);
   return x;
}
i64 dfs(int u,int l,int r,int R){
   if(r<=R){
      i64 res=info[u].s;
      apply(u,{0,0});
      return res;
   }
   int mid=l+r>>1;
   pushdown(u);
   i64 res=(dfs(ls[u],l,mid,R)+(R>mid?dfs(rs[u],mid+1,r,R):0))%mod;
   pushup(u);
   return res;
}
void mdf(int&u,int l,int r,int p,i64 v){
   if(!u)u=++tot;
   if(l==r)return info[u].s=v,void();
   int mid=l+r>>1;
   pushdown(u);
   if(p<=mid)mdf(ls[u],l,mid,p,v);
   else mdf(rs[u],mid+1,r,p,v);
   pushup(u);
}
void print(int u,int l,int r){
   if(l==r)return printf("%lld ",info[u].hs),void();
   int mid=l+r>>1;
   pushdown(u);
   print(ls[u],l,mid),print(rs[u],mid+1,r);
}
}
int n,m,val[200010],rt[200010];
vector<int>G[200010];
void dfs(int u,int fa){
   for(int v:G[u])if(v!=fa){
      dfs(v,u),rt[u]=ds::merge(rt[u],rt[v],0,0);
   }
   ds::mdf(rt[u],1,m,val[u],(ds::dfs(rt[u],1,m,val[u])+1)%mod);
   ds::apply(rt[u],{1,1});
}
int main(){
   freopen("tree.in","r",stdin);
   freopen("tree.out","w",stdout);
   cin>>n>>m;
   for(int i=1;i<=n;i++)scanf("%d",&val[i]);
   for(int i=1,u,v;i<n;i++){
      scanf("%d%d",&u,&v);
      G[u].push_back(v),G[v].push_back(u);
   }
   dfs(1,0),ds::print(rt[1],1,m);
   return 0;
}