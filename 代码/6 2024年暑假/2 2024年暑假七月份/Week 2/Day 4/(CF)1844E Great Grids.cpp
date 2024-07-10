#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
struct node {
	int v,w,nex;
}a[N];
int first[N],cnt;
void add(int u,int v,int w) {
	a[++cnt]={v,w,first[u]};
	first[u]=cnt;
}
int col[N];
bool dfs(int u,int color) {
	if(col[u]!=-1) {
		if(col[u]!=color)return false;
		return true;
	}
	col[u]=color;
	for(int i=first[u];i;i=a[i].nex) {
		int v=a[i].v;
		if(!dfs(v,color^a[i].w))return false;
	}
	return true;
}
void clear() {
	memset(first,0,sizeof first);
	cnt=0;
}
void solve() {
	clear();
	int n,m,k;
	cin>>n>>m>>k;
	for(int i=1;i<=k;i++) {
		int x_1,y_1,x_2,y_2;
		cin>>x_1>>y_1>>x_2>>y_2;
		int u=min(x_1,x_2);
		int v=n-1+min(y_1,y_2);
		int w=x_1+y_1!=x_2+y_2;
		add(u,v,w),add(v,u,w);
	}
	for(int i=1;i<=n+m-2;i++)col[i]=-1;
	bool ans=true;
	for(int i=1;i<=n+m-2;i++)if(col[i]==-1)if(!dfs(i,0)){ans=false;break;}
	puts(ans?"YES":"NO");
}
int main() {
	int T;
	cin>>T;
	while(T--)solve();
}