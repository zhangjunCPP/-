#include <bits/stdc++.h>
#define mid ((l + r) >> 1)
#define lson l,mid,ls[rt]
#define rson mid+1,r,rs[rt]
#define ll  __int128
using namespace std;
const int N=1e5+5,M=5e6+5,inf=0x3f3f3f3f;
const ll INF=1e30;
int fa[N],n;
ll w[N],a[N],L[N],C[N],ans[N],res;
vector<int> e[N];

void file(){
	freopen("brain.in","r",stdin);
	freopen("brain.out","w",stdout);
}
struct line {
	ll k,b;
}d[N];
struct seg {
	int opt, idx,ls[M],rs[M],root[N],tr[M];
	int cmp(line x,line y,int v) {
		if(opt==0) return x.k*v+x.b<y.k*v+y.b;
		return x.k*v+x.b>y.k*v+y.b;
	}
	int check(line x,line y) {
		if(opt==0) return x.k>y.k;
		return x.k<y.k;
	}
	void insert(int l,int r,int &rt,int newline) {
		if (!rt) {
			tr[rt=++idx]=newline;
			return;
		}
		int now=tr[rt];
		if (cmp(d[newline],d[now],mid))swap(now,newline);//更新lazy
		tr[rt]=now;
		if (d[now].k==d[newline].k||l==r) return;
		if (check(d[newline],d[now]))insert(lson, newline);//往某一边递归更新lazy
		else insert(rson, newline);
	}
	ll query(int l,int r,int rt,int x) {
		if (!rt) return opt?-INF:INF;
		ll now=d[tr[rt]].k*x+d[tr[rt]].b;
		if (l==r) return now;
		ll newline;
		if(x<=mid) newline=query(lson,x);
		else newline=query(rson,x);
		if(opt==0) now=min(now,newline);
		else now=max(now,newline);
		return now;
	}
	int merge(int l,int r,int x,int y) {
		if (!x||!y) return x+y;
		insert(l,r,x,tr[y]);
		if (l==r) return x;
		ls[x]=merge(l,mid,ls[x],ls[y]);
		rs[x]=merge(mid+1,r,rs[x],rs[y]);
		return x;
	}
} t0,t1;
void dfs1(int u) {
	for(auto v:e[u]) dfs1(v),a[u]+=a[v];
}
void dfs2(int u) {
	L[u]=L[fa[u]]+w[u];//路径和
	C[u]=C[fa[u]]+w[u]*a[u];//路径siwi和
	res+=a[u]*(a[1]-a[u])*w[u];
	for(auto v:e[u])dfs2(v);
}
void dfs(int u) {
	d[u]={L[u],-2*C[u]};
	t0.insert(-inf,inf,t0.root[u],u);
	t1.insert(-inf,inf,t1.root[u],u);
	for (int v: e[u]) {
		dfs(v);
		t0.root[u]=t0.merge(-inf, inf, t0.root[u], t0.root[v]);
		t1.root[u]=t1.merge(-inf, inf, t1.root[u], t1.root[v]);
	}
	ll v=a[1]-a[u];
	if(v>0) ans[u]=v*t1.query(-inf,inf,t1.root[u],a[u]);
	else ans[u]=v*t0.query(-inf,inf,t0.root[u],a[u]);
	ans[u]=ans[u]-v*(a[u]*L[u]-2*C[u])+res;
}
void print(ll x) {
	if(x<0) printf("-"),x=-x;
	if(!x)return;
	print(x/10);
	printf("%d",(int)(x%10));
}
int main() {
	file();
	scanf("%d",&n);
	for(int i=1,Cin;i<=n;i++) scanf("%d",&Cin),a[i]=Cin;
	for (int i=2,Cin;i<=n;i++) {
		scanf("%d%d",&fa[i],&Cin);
		w[i]=Cin;
		e[fa[i]].push_back(i);
	}
	t0.opt=0,t1.opt=1;
	dfs1(1);
	dfs2(1);
	dfs(1);
	for (int i=2;i<=n;i++) {
		if(!ans[i]) printf("0");
		else print(ans[i]);
		printf("\n");
	}
	return 0;
}
