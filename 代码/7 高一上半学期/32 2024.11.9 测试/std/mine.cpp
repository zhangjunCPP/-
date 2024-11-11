#include<bits/stdc++.h>
#define int long long
using namespace std;
int num;
int hd[1000006];
int dis[1000006];
int deep[1000006];
int bl[1000006],vis[1000006];
int x,n,k,u,v;
int fat[1000006],T;
vector<int>ans,xl;
struct P{int nxt,to;}line[2000006];
void ini(){
	memset(hd,0,sizeof(int)*(n+5));
	memset(deep,0,sizeof(int)*(n+5));
	memset(bl,0,sizeof(int)*(n+5));
	memset(fat,0,sizeof(int)*(n+5));
	memset(vis,0,sizeof(int)*(n+5));
	num=1;
	ans.clear(),xl.clear();
	return;
}
void add(int x,int y){
	++num;
	line[num]={hd[x],y};
	hd[x]=num;
	return ;
}
using pi=pair<int,int>;
priority_queue<pi,vector<pi>,greater<pi> >dl;
void dij(){
	while(dl.size()){
		int tp=dl.top().second;
		dl.pop();
		if(vis[tp])continue;
		vis[tp]=1;
		for(int i=hd[tp];i;i=line[i].nxt){
			int to=line[i].to;
			if(dis[to]>dis[tp]+1){
				dis[to]=dis[tp]+1;
				dl.push({dis[to],to});
			}
		}
	}
	return ;
}
void dfs(int x,int fa){
	fat[x]=fa;
	deep[x]=deep[fa]+1;
	for(int i=hd[x];i;i=line[i].nxt){
		int to=line[i].to;
		if(to==fa)continue;
		dfs(to,x);
	}
	return ;
}
void dfs1(int x,int last){
	bl[x]=1;
	if(!last)return ;
	for(int i=hd[x];i;i=line[i].nxt){
		int to=line[i].to;
		if(bl[to] or dis[to]>last-1)continue;
		dfs1(to,last-1);
	}
	return;
}
void mymain(){
	cin>>n;
	for(int i=1;i<n;++i){
		cin>>u>>v;
		add(u,v);
		add(v,u);
	}
	memset(dis,0x3f,sizeof(int)*(n+5));
	cin>>k;
	for(int i=1;i<=k;++i){
		cin>>x;
		dis[x]=0;
		dl.push({0,x});
		xl.push_back(x);
	}
	dij();
	dfs(1,0);
	auto cmp=[&](int x,int y)->bool{return deep[x]>deep[y];};
	sort(xl.begin(),xl.end(),cmp);
	for(auto x:xl){
		if(bl[x])continue;
		int tp=x;
		while(fat[tp] and dis[fat[tp]]==deep[x]-deep[fat[tp]])tp=fat[tp];
		dfs1(tp,dis[tp]);
		ans.push_back(tp);
	}
	cout<<ans.size()<<'\n';
	return ;
}
signed main(){
	cin.tie(0)->sync_with_stdio(0);
	cin>>T;
	while(T--)ini(),mymain();
	return 0;
}