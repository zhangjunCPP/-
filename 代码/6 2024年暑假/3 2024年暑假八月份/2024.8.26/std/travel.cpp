#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int n,q,t,a[N],lst[N];multiset<int> s;
int head[N],cnt;struct node{int to,nxt;}e[N<<1];
void add(int u,int v){e[++cnt]={v,head[u]},head[u]=cnt;}
struct NODE{int mx[N<<2],tr[N<<2],tag[N<<2];
	int tot,id[N],d[N],fa[N],sz[N],top[N],son[N],dfn[N];
	void dfs(int u){sz[u]=1;
		for(int i=head[u],v;i;i=e[i].nxt)if((v=e[i].to)!=fa[u]){
			fa[v]=u,d[v]=d[u]+1,dfs(v),sz[u]+=sz[v];
			if(sz[v]>sz[son[u]])son[u]=v;
		} 
	}
	void dfs2(int u,int tp){
		dfn[u]=++tot,id[tot]=u,top[u]=tp;
		if(son[u])dfs2(son[u],tp);
		for(int i=head[u],v;i;i=e[i].nxt)if((v=e[i].to)!=fa[u]&&v!=son[u])dfs2(v,v);
	}
	void build(int o,int l,int r){
		if(l==r)return tr[o]=2*d[id[l]],void();
		int mid=(l+r)>>1;
		build(o<<1,l,mid),build(o<<1|1,mid+1,r);
		tr[o]=max(tr[o<<1],tr[o<<1|1]);
	}
	void addtag(int o,int z){mx[o]=max(mx[o],z+tr[o]),tag[o]=max(tag[o],z);}
	void downtag(int o){if(tag[o])addtag(o<<1,tag[o]),addtag(o<<1|1,tag[o]),tag[o]=0;} 
	void update(int o,int l,int r,int x,int y,int z){
		if(x<=l&&r<=y)return addtag(o,z),void();
		int mid=(l+r)>>1;downtag(o);
		if(x<=mid)update(o<<1,l,mid,x,y,z);
		if(y>mid)update(o<<1|1,mid+1,r,x,y,z);
		mx[o]=max(mx[o<<1],mx[o<<1|1]);
	}
	void insert(int u){int x=a[u]-d[u];
		while(u)update(1,1,n,dfn[top[u]],dfn[u],x),u=fa[top[u]];
	}
	int query(int o,int l,int r,int x,int y){
		if(x<=l&&r<=y)return mx[o];
		int mid=(l+r)>>1,s=0;downtag(o);
		if(x<=mid)s=max(s,query(o<<1,l,mid,x,y));
		if(y>mid)s=max(s,query(o<<1|1,mid+1,r,x,y));
		return s;
	} 
	int lca(int u,int v){
		while(top[u]!=top[v]){
			if(d[top[u]]<d[top[v]])swap(u,v);
			u=fa[top[u]];
		}
		return d[u]<d[v]?u:v;
	}
	int qry(int x){int u=x,s=0;
		while(u)s=max(s,query(1,1,n,dfn[top[u]],dfn[u])),u=fa[top[u]];
		return s-d[x];
	} 
	void init(){dfs(1),dfs2(1,1),build(1,1,n);
		for(int i=1;i<=n;i++)insert(i);
	}
}T1;
int main(){
	freopen("travel.in", "r", stdin);
	freopen("travel.out", "w", stdout);
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1,x,y;i<n;i++)scanf("%d%d",&x,&y),add(x,y),add(y,x); 
	T1.init();
	for(int i=1,ty,x,ct=0;i<=q;i++){
		scanf("%d%d%d",&ty,&t,&x);
		if(ty==1){
			s.insert(a[x]-t);
			lst[x]=t;
		}else if(ty==2){
			auto it=s.lower_bound(a[x]-lst[x]);
			s.erase(it),a[x]+=t-lst[x],T1.insert(x);
		}else {
			int ans=T1.qry(x)-t;
			if(s.size()){
				auto it=s.end();
				it--,ans=max(ans,*it);
			}
			printf("%d\n",max(ans,0));
		}
	}
	return 0;
}
