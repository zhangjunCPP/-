#include <bits/stdc++.h>

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
int dep[N],siz[N],son[N];
int Max[N];
int depx;
void dfs(int u,int fa){
	dep[u]=dep[fa]+1;
	siz[u]=1;
	Max[u]=dep[u];
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(v==fa)continue;
		dfs(v,u);
		siz[u]+=siz[v];
		Max[u]=max(Max[u],Max[v]);
		if(siz[v]>siz[son[u]]&&Max[v]>=depx)son[u]=v;
	}
}
int rev[N];
int main(){
	int n;
	cin>>n;
	for(int i=1;i<n;i++) {
		int u,v;
		cin>>u>>v;
		add(u,v);
		add(v,u);
	}
	cout<<"d 1"<<endl;
	cin>>depx;
	depx++;
	dfs(1,0);
	int u=1;
	while(true){
		if(dep[u]==depx){
			cout<<"d "<<u<<endl;
			int d;
			cin>>d;
			if(!d){
				cout<<"! "<<u<<endl;
				return 0;
			}
			u=rev[dep[u]-d/2];
			cout<<"s "<<u<<endl;
			cin>>u;
			if(dep[u]==depx){
				cout<<"! "<<u<<endl;
				return 0;
			}
		}
		rev[dep[u]]=u;
		u=son[u];
	}
}