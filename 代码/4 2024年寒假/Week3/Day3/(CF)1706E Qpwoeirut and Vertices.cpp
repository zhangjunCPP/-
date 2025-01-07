#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
struct node{
	int v,nex;
}a[N];
int first[N],cnt;
void add(int u,int v){
	a[++cnt]={v,first[u]};
	first[u]=cnt;
}
struct node2{int u,v,w;}G[N];
bool cmp(const node2&x,const node2&y){return x.w<y.w;}
int fa[N];
int find(int x){
	if(fa[x]!=x)fa[x]=find(fa[x]);
	return fa[x];
}
int dep[N];
int fa2[N][20];
void dfs(int u,int dad){
	dep[u]=dep[dad]+1;
	fa2[u][0]=dad;
	for(int i=1;i<20;i++)fa2[u][i]=fa2[fa2[u][i-1]][i-1];
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(v==dad)continue;
		dfs(v,u);
	}
}
int lca(int x,int y){
	if(dep[x]<dep[y])swap(x,y);
	for(int i=19;i>=0;i--)if(dep[fa2[x][i]]>=dep[y])x=fa2[x][i];
	if(x==y)return x;
	for(int i=19;i>=0;i--)if(fa2[x][i]!=fa2[y][i])x=fa2[x][i],y=fa2[y][i];
	return fa2[x][0];
}
int tree[N];
void init(){
	memset(first,0,sizeof first);
	cnt=0;
	memset(tree,0,sizeof tree);
}
void update(int k,int l,int r,int x,int y){
	if(l==r){tree[k]=y;return;}
	int mid=(l+r)>>1;
	if(x<=mid)update(k<<1,l,mid,x,y);
	else update(k<<1|1,mid+1,r,x,y);
	tree[k]=max(tree[k<<1],tree[k<<1|1]);
}
int query(int k,int l,int r,int x,int y){
	if(x<=l&&y>=r)return tree[k];
	if(x>r||y<l)return 0;
	int mid=(l+r)>>1;
	return max(query(k<<1,l,mid,x,y),query(k<<1|1,mid+1,r,x,y));

}
int val[N];
void solve(){
	init();
	int n,m,q;
	cin>>n>>m>>q;
	for(int i=1;i<(n<<1);i++)fa[i]=i;
	for(int i=1;i<=m;i++){
		cin>>G[i].u>>G[i].v;
		G[i].w=i;
	}
	sort(G+1,G+m+1,cmp);
	int tot=n;
	for(int i=1;i<=m;i++){
		int fu=find(G[i].u),fv=find(G[i].v);
		if(fu!=fv){
			val[++tot]=G[i].w;
			add(tot,fu),add(fu,tot);
			add(tot,fv),add(fv,tot);
			fa[fu]=fa[fv]=tot;
			if(tot==(n<<1)-1)break;
		}
	}
	dfs(tot,0);
	for(int i=1;i<n;i++)update(1,1,n,i,val[lca(i,i+1)]);
	while(q--){
		int u,v;
		cin>>u>>v;
		cout<<query(1,1,n,u,v-1)<<" ";
	}
	cout<<"\n";

}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int T;
	cin>>T;
	while(T--)solve();
}