#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
struct node{
	int v,w,nex;
}a[N*2];
int first1[N],cnt1;
void add(int u,int v,int w){
	a[++cnt1]={v,w,first1[u]};
	first1[u]=cnt1;
}
int dep[N];
int fa[N][20];
int dfn[N],tot;
int Min[N];
void dfs(int u,int dad){
	dep[u]=dep[dad]+1;
	fa[u][0]=dad;
	for(int i=1;i<20;i++) fa[u][i]=fa[fa[u][i-1]][i-1];
	dfn[u]=++tot;
	for(int i=first1[u];i;i=a[i].nex){
		int v=a[i].v;
		if(!dfn[v]) {
			Min[v]=min(Min[u],a[i].w);
			dfs(v,u);
		}
	}
} 
int LCA(int x,int y){
	if(dep[x]<dep[y]) swap(x,y);
	for(int i=19;i>=0;i--) if(dep[fa[x][i]]>=dep[y]) x=fa[x][i];
	if(x==y) return x;
	for(int i=19;i>=0;i--) {
		if(fa[x][i]!=fa[y][i]) {
			x=fa[x][i];
			y=fa[y][i];
		}
	}
	return fa[x][0];
}
int h[N];
int sta[N],top;
bool flag[N];
bool cmp(const int &x,const int &y){return dfn[x]<dfn[y];}
struct node2{
	int v,nex;
}b[N*2];
int first2[N],cnt2;
void add2(int u,int v){
	b[++cnt2]={v,first2[u]};
	first2[u]=cnt2;
}
int dfs2(int u) {
	int sum=0;
	for(int i=first2[u];i;i=b[i].nex) {
		int v=b[i].v;
		sum+=dfs2(v);
	}
	int ans=0x7fffffff;
	if(flag[u]) ans=Min[u];
	else ans=min(Min[u],sum);
	flag[u]=false;
	first2[u]=0;
	return ans;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0); 
	int n;
	cin>>n;
	memset(Min,0x3f,sizeof Min);
	for(int i=1;i<n;i++){
		int u,v,w;
		cin>>u>>v>>w;
		add(u,v,w);
		add(v,u,w);
	}
	dfs(1,0);
	int m;
	cin>>m;
	while(m--){
		int k;
		cin>>k;
		for(int i=1;i<=k;i++){ 
			cin>>h[i];
			flag[h[i]]=true;
		}
		sort(h+1,h+k+1,cmp);
		top=1;
		sta[1]=1;
		for(int i=1;i<=k;i++){
			if(h[i]!=1) {
				int lca=LCA(h[i],sta[top]);
				if(sta[top]!=lca) {
					while(dfn[lca]<dfn[sta[top-1]]) {
						add2(sta[top-1],sta[top]);
						top--;
					}
					if(dfn[lca]>dfn[sta[top-1]]) {
						add2(lca,sta[top]);
						sta[top]=lca;
					}
					else {
						add2(lca,sta[top]);
						top--;
					}
				}
				sta[++top]=h[i];
			}
		}	
		for(int i=1;i<top;i++) add2(sta[i],sta[i+1]);
		cout<<dfs2(sta[1])<<"\n";
		cnt2=0;
	}
}