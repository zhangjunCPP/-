#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N=5e5+10;
vector<int> G[N];
int w[N];
int dfn1[N],dfn2[N],tot;
struct FHQ{
	#define ls(x) ch[x][0]
	#define rs(x) ch[x][1]
	int root;
	int ch[N][2],siz[N],fa[N],rd[N];
	ll lazy[N],sum[N],a[N],num[N],p[N];
	int add(int id,int op,int x){
		a[id]=sum[id]=op*x;
		rd[id]=rand();
		p[id]=num[id]=op;
		siz[id]=1;
		return id;
	}
	void up(int x){
		siz[x]=siz[ls(x)]+siz[rs(x)]+1;
		num[x]=num[ls(x)]+num[rs(x)]+p[x];
		sum[x]=sum[ls(x)]+sum[rs(x)]+a[x];
		if(ls(x))fa[ls(x)]=x;
		if(rs(x))fa[rs(x)]=x;
	}
	void pushdown(ll x,ll y){
		if(!x)return;
		lazy[x]+=y;
		a[x]+=y*p[x];
		sum[x]+=y*num[x];
	}
	void push(int x){
		if(lazy[x]){
			pushdown(ls(x),lazy[x]);pushdown(rs(x),lazy[x]);
			lazy[x]=0;
		}
	}
	void split(int now,int k,int &x,int &y){
		if(!now)x=y=0;
		else{
			push(now);
			if(k<=siz[ls(now)]) {y=now;split(ls(now),k,x,ls(now));}
			else {x=now;split(rs(now),k-siz[ls(now)]-1,rs(now),y);}
			up(now);
		}
	}
	int merge(int x,int y){
		if(x==0||y==0)return x!=0?x:y;
		push(x),push(y);
		if(rd[x]<rd[y]){rs(x)=merge(rs(x),y);up(x);return x;}
		else{ls(y)=merge(x,ls(y));up(y);return y;}
	}
	int rk(int x){
		int tmp=siz[ls(x)]+1;
		while (fa[x]){
			if(x==rs(fa[x]))tmp+=siz[ls(fa[x])]+1;
			x=fa[x];
		}
		return tmp;
	}
	void swap(int l,int r,int x){
		int tmp1,tmp2,tmp3,tmp4;
		l=rk(l),r=rk(r),x=rk(x);
		if(x<=l-1){
			split(root,r,tmp1,tmp4);split(tmp1,l-1,tmp1,tmp2);split(tmp1,x,tmp1,tmp3);
			root=merge(merge(merge(tmp1,tmp2),tmp3),tmp4);
		}
		else{
			split(root,x,tmp1,tmp4);split(tmp1,r,tmp1,tmp2);split(tmp1,l-1,tmp1,tmp3);
			root=merge(merge(merge(tmp1,tmp2),tmp3),tmp4);
		}
	}
	void update(int l,int r,int y){
		int tmp1,tmp2,tmp3;
		l=rk(l),r=rk(r);
		split(root,r,tmp1,tmp3);
		split(tmp1,l-1,tmp1,tmp2);
		pushdown(tmp2,y);
		root=merge(merge(tmp1,tmp2),tmp3);
	}
	ll query(int x){
		int tmp1,tmp2;
		split(root,rk(x),tmp1,tmp2);
		ll ans=sum[tmp1];
		root=merge(tmp1,tmp2);
		return ans;
	}
}tree;
void dfs(int x,int fa){
	dfn1[x]=++tot;
	tree.root=tree.merge(tree.root,tree.add(tot,1,w[x]));
	for(int v:G[x]){if(v!=fa)dfs(v,x);}
	dfn2[x]=++tot;
	tree.root=tree.merge(tree.root,tree.add(tot,-1,w[x]));
}
int main(){
	srand(time(0));
	int n;
	scanf("%d",&n);
	for(int i=2;i<=n;i++){
		int u;
		scanf("%d",&u);
		G[u].push_back(i);
	}
	for(int i=1;i<=n;i++)scanf("%d",w+i);
	dfs(1,0);
	int q;
	scanf("%d",&q);
	while(q--){
		char c;
		cin>>c;
		int x,y; 
		if (c=='Q') scanf("%d",&x),printf("%lld\n",tree.query(dfn1[x]));
		else if(c=='C') scanf("%d%d",&x,&y),tree.swap(dfn1[x],dfn2[x],dfn1[y]);
		else scanf("%d%d",&x,&y),tree.update(dfn1[x],dfn2[x],y);
	}
	return 0;
}