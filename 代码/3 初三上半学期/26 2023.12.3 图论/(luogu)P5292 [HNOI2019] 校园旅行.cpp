#include<bits/stdc++.h>
using namespace std;
const int N=5e3+10;
struct node{
	int v,nex;
}a[N*100];
int first[N],cnt;
void add(int u,int v){
	a[++cnt]={v,first[u]};
	first[u]=cnt;
}
vector<int> G[N];
string s;
int fa[N];
int find(int x) {
	if(fa[x]!=x) fa[x]=find(fa[x]);
	return fa[x];
}
int col[N];
bool flag;

queue<pair<int,int> > q; //最开始存的是所有可行的二元组
bool ans[N][N];
void dfs(int u,int color) {
	col[u]=color;
	for(int v:G[u]) {
		if(s[u-1]!=s[v-1]) continue;
		if(col[v]){
			if(col[v]==col[u]) flag=false;//非二分图	
			continue;
		}
		add(u,v);add(v,u);
		dfs(v,color^1);
		ans[u][v]=ans[v][u]=true;
		q.push({u,v}); //两点一样一定可以 
	}
}
int main(){
	int n,m,Q;
	cin>>n>>m>>Q;
	cin>>s;
	for(int i=1;i<=n;i++) fa[i]=i;
	
	for(int i=1;i<=m;i++) {
		int u,v;
		cin>>u>>v;
		G[u].push_back(v);
		G[v].push_back(u);
		if(s[u-1]!=s[v-1]) {  //颜色不相同，一定是二分图，只保留一颗生成树即可
			if(find(u)==find(v)) continue;
			add(u,v);add(v,u);
			fa[find(u)]=find(v);
		}
	}
	for(int i=1;i<=n;i++) {
		if(!col[i]) {
			flag=true;
			dfs(i,2);
			if(!flag) add(i,i); //非二分图连自环
		}
	}
	for(int i=1;i<=n;i++) ans[i][i]=true,q.push({i,i});
	while(!q.empty()){
		int x=q.front().first,y=q.front().second;
		q.pop();
		for(int i=first[x];i;i=a[i].nex) {
			int v1=a[i].v;
			for(int j=first[y];j;j=a[j].nex) {
				int v2=a[j].v;
				if(ans[v1][v2]) continue;
				if(s[v1-1]==s[v2-1]) {
					ans[v1][v2]=ans[v2][v1]=true;
					q.push({v1,v2});
				}
			}
		}
	}
	while(Q--){
		int x,y;
		cin>>x>>y;
		if(ans[x][y])puts("YES");
		else puts("NO");
	}
}
