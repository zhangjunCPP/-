#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int p[N];
int l[N],r[N];
struct node{
	int v,nex;
}a[N][2];
int first[N][2],cnt[2];
int deg[N][2];
void add(int u,int v,int opt){
	a[++cnt[opt]][opt]={v,first[u][opt]};
	first[u][opt]=cnt[opt];
	deg[v][opt]++;
}
vector<pair<int,int>> G[N];
void solve(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++)G[i].clear(),l[i]=1,r[i]=n,deg[i][0]=deg[i][1]=0,first[i][0]=first[i][1]=0;
	cnt[0]=cnt[1]=0;
	for(int i=1;i<=n;i++){
		cin>>p[i];
		if(p[i])l[i]=r[i]=p[i];
	}
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		add(u,v,0);
		add(v,u,1);
	}
	queue<int> q;
	for(int i=1;i<=n;i++)if(!deg[i][0])q.push(i);
	while(!q.empty()){
		int u=q.front();
		q.pop();
		for(int i=first[u][0];i;i=a[i][0].nex){
			int v=a[i][0].v;
			l[v]=max(l[v],l[u]+1);
			deg[v][0]--;
			if(!deg[v][0])q.push(v);
		}
	}
	for(int i=1;i<=n;i++)if(!deg[i][1])q.push(i);
	while(!q.empty()){
		int u=q.front();
		q.pop();
		for(int i=first[u][1];i;i=a[i][1].nex){
			int v=a[i][1].v;
			r[v]=min(r[v],r[u]-1);
			deg[v][1]--;
			if(!deg[v][1])q.push(v);
		}
	}
	for(int i=1;i<=n;i++)if((l[i]>r[i])||(p[i]&&(l[i]>p[i]||r[i]<p[i]))){cout<<"-1\n";return;}
	priority_queue<pair<int,int>> q2;
	for(int i=1;i<=n;i++)G[l[i]].push_back({-r[i],i});
	for(int i=1;i<=n;i++){
		for(auto it:G[i])q2.push(it);
		if(q2.empty()){cout<<"-1\n";return;}
		if(-q2.top().first<i){cout<<"-1\n";return;}
		int now=q2.top().second;
		q2.pop();
		p[now]=i;
	}
	for(int i=1;i<=n;i++)cout<<p[i]<<" ";
	cout<<"\n";
}
int main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int T;
	cin>>T;
	while(T--)solve();
}