#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+10;

vector<int> G[N];
int w[N];
int tot;
int dfn1[N],dfn2[N];

struct FHQ{
	#define ls(x) ch[x][0]
	#define rs(x) ch[x][1]
	int root;
	int ch[N][2];
	int a[N],b[N];
	int lazy[N];
	int siz[N];
	int fa[N];
	int num[N],sum[N];
	int p[N];
	int add(int id,int opt,int x){
		p[id]=num[id]=opt;
		a[id]=sum[id]=opt*x;
		b[id]=rand();
		siz[id]=1; 
		return id; 
	}
	void up(int x){
		siz[x]=siz[ls(x)]+siz[rs(x)]+1;
		num[x]=num[ls(x)]+num[rs(x)]+p[x];
		sum[x]=sum[ls(x)]+sum[rs(x)]+a[x]; 
		if (ls(x)) fa[ls(x)]=x;
		if (rs(x)) fa[rs(x)]=x;
	}
	void pushdown(int x,int y){
		if(!x)return; 
		lazy[x]+=y;
		a[x]+=y*p[x];
		sum[x]+=y*num[x]; 
	}
	void push(int x){
		if(lazy[x]){
			pushdown(ls(x),lazy[x]);
			pushdown(rs(x),lazy[x]);
			lazy[x]=0;
		}
	}
	void split(int now,int k,int &x,int &y){
		if(!now)x=y=0;
		else{
			push(now);
			if(k<=siz[ls(now)]){ 
				y=now;
				split(ls(now),k,x,ls(now));
			}
			else{ 
				x=now;
				split(rs(now),k-siz[ls(now)]-1,rs(now),y);
			}
			up(now);
		}
	}
	int merge(int x,int y){
		if(x==0||y==0)return x!=0?x:y;
		push(x);
		push(y);
		if(b[x]<b[y]){
			rs(x)=merge(rs(x),y);
			up(x);
			return x;
		}
		else{
			ls(y)=merge(x,ls(y));
			up(y);
			return y;
		}
	}
	int rank(int x){
		int tmp=siz[ls(x)]+1;
		while (fa[x]) {
			if(x==rs(fa[x]))tmp+=siz[ls(fa[x])]+1;
			x=fa[x];
		}
		return tmp;
	}
	int query(int x){
		int A,B;
		split(root,rank(x),A,B);
		int ans=sum[A];
		root=merge(A,B);
		return ans;
	}
	void swap(int l,int r,int x){
		int A,B,C,D;
		l=rank(l),r=rank(r),x=rank(x);
		if (x<=l-1){
			split(root,r,A,D);
			split(A,l-1,A,B);
			split(A,x,A,C);
			root=merge(merge(merge(A,B),C),D);
		}
		else{
			split(root,x,A,D);
			split(A,r,A,B);
			split(A,l-1,A,C);
			root=merge(merge(merge(A,B),C),D);
		}
	}
	void update(int l,int r,int y){
		int A,B,C;
		l=rank(l),r=rank(r);
		split(root,r,A,C);
		split(A,l-1,A,B);
		pushdown(B,y);
		root=merge(merge(A,B),C);
	}
}tree;

void dfs(int x,int fa){
	dfn1[x]=++tot;
	tree.root=tree.merge(tree.root,tree.add(tot,1,w[x]));
	for (int v:G[x]){
		if(v==fa)continue;
		dfs(v,x);
	}
	dfn2[x]=++tot;
	tree.root=tree.merge(tree.root,tree.add(tot,-1,w[x]));
}
signed main(){
	srand(time(0));
	int n;
	cin>>n;
	for(int i=2;i<=n;i++){
		int u;
		cin>>u;
		G[u].push_back(i);
	}
	for(int i=1;i<=n;i++)cin>>w[i];
	dfs(1,0);
	int q;
	cin>>q;
	while(q--){
		char c; 
		cin>>c;
		int x,y; 
		if (c=='Q') cin>>x,cout<<tree.query(dfn1[x])<<"\n";
		else if(c=='C') cin>>x>>y,tree.swap(dfn1[x],dfn2[x],dfn1[y]);
		else cin>>x>>y,tree.update(dfn1[x],dfn2[x],y);
	}
	return 0;
}