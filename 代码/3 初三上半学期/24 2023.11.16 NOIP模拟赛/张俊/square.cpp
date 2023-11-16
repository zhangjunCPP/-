#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
struct node{
	int v,nex;
}a[N];
int first[N],cnt;
void add(int u,int v){
	a[++cnt]={v,first[u]};
	first[u]=cnt;
}
int dep[N];
int fa[N][25];
void dfs(int u,int dad){
	fa[u][0]=dad;
	dep[u]=dep[dad]+1;
	for(int i=1;i<25;i++) fa[u][i]=fa[fa[u][i-1]][i-1];
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(v==dad) continue;
		dfs(v,u);
	}
}
int LCA(int x,int y) {
	if(dep[x]<dep[y]) swap(x,y);
	for(int i=24;i>=0;i--) if(dep[fa[x][i]]>=dep[y])x=fa[x][i];
	if(x==y) return x;
	for(int i=24;i>=0;i--) {
		if(fa[x][i]!=fa[y][i]) {
			x=fa[x][i];
			y=fa[y][i];
		}
	}
	return fa[x][0];
}
int val[N];
int tmp[N],tot;
int read(){
	int x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9') {
		x=(x<<3)+(x<<1)+(ch^48);
		ch=getchar();
	}
	return x;
}
bool check(int x,int y){
	int now=val[x]*val[y];
	int tmpp=sqrt(now);
	if(tmpp*tmpp!=now) return false;
	return true;
}
signed main(){
	freopen("square.in","r",stdin);
	freopen("square.out","w",stdout);
	int n,q;
	n=read();q=read();
	for(int i=1;i<=n;i++) val[i]=read();
	for(int i=1;i<n;i++) {
		int u,v;
		u=read();v=read();
		add(u,v);
		add(v,u);
 	}
 	dfs(1,0);
 	while(q--) {
 		tot=0;
 		int x,y;
 		x=read();y=read();
 		if(dep[x]<dep[y]) swap(x,y);
 		int lca=LCA(x,y);
 		while(x!=lca) {
 			tmp[++tot]=x;
 			x=fa[x][0];
 		}
 		tmp[++tot]=lca;
 		while(y!=lca) {
 			tmp[++tot]=y;
 			y=fa[y][0];
 		}
 		bool flag=false;
 		for(int i=1;i<=tot;i++){
 			for(int j=1;j<i;j++) {
 				if(check(tmp[i],tmp[j])) {
 					flag=true;
 					break;
 				}
 			}
 		}
 		if(flag) puts("Yes");
 		else puts("No");
 	}
	return 0;
}

