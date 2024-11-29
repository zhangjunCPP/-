#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int fa[N];
int find(int x){
	if(fa[x]!=x)fa[x]=find(fa[x]);
	return fa[x];
}
map<pair<int,int>,int> mp;
int tot;
int calc(int x,int y){
	if(mp.count({x,y}))return mp[{x,y}];
	mp[{x,y}]=++tot;
	fa[tot]=tot;
	return tot;
}
struct node{
	int v,w,nex;
}a[N];
int first[N],cnt;
void add(int u,int v,int w){
	a[++cnt]={v,w,first[u]};
	first[u]=cnt;
}
pair<int,int> q[N];
bool flag[N];
int ans[N];
int dep[N];
void dfs(int u,int fa){
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(v==fa)continue;
		dep[v]=dep[u]+a[i].w;
		dfs(v,u);
	}
}
int main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		int x,y;
		string s;
		cin>>x>>y>>s;
		if(s=="x"){
			int u=calc(x,y),v=calc(x+1,y);
			int fu=find(u),fv=find(v);
			if(fu!=fv){
				fa[fu]=fv;
				add(u,v,y),add(v,u,-y);
				flag[i]=false;
			}
			else{
				q[i]={u,v};
				ans[i]=y;
				flag[i]=true;
			}
		}
		else{
			int u=calc(x,y),v=calc(x,y+1);
			int fu=find(u),fv=find(v);
			if(fu!=fv){
				fa[fu]=fv;
				add(u,v,0),add(v,u,0);
				flag[i]=false;
			}
			else{
				q[i]={u,v};
				ans[i]=0;
				flag[i]=true;
			}
		}
	}
	for(int i=1;i<=tot;i++)if(fa[i]==i)dfs(i,0);
	for(int i=1;i<=n;i++)if(flag[i])ans[i]=abs(ans[i]+dep[q[i].first]-dep[q[i].second]);
	for(int i=1;i<=n;i++)cout<<ans[i]<<"\n";
}