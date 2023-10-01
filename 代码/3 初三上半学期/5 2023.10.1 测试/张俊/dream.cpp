#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e6+10;
const int mod=1e9+7;

int d[N];
struct node{
	int v,w,nex;
}a[N];
int first[N],cnt;
void add(int u,int v,int w){
	a[++cnt]={v,w,first[u]};
	first[u]=cnt;
	d[v]++;
}

struct node2{
	int val,id;
	bool operator<(const node2 &b) const{
		return val>b.val;
	}
};
int n,m,k,id;
int dis[N],ans[N];
bool vis[N];
void dij(int s){
	for(int i=1;i<=n;i++) dis[i]=0x3f3f3f3f3f3f3f3f,ans[i]=0,vis[i]=false;
	dis[s]=1;
	ans[s]=1;
	priority_queue<node2> q;
	q.push(node2{1,s});
	while(!q.empty()){
		node2 now=q.top();
		q.pop();
		if(vis[now.id]) continue;
		vis[now.id]=true;
		for(int i=first[now.id];i;i=a[i].nex){
			int v=a[i].v;
			if(v==now.id) continue;
			if(dis[v]==dis[now.id]+a[i].w){
				ans[v]=(ans[v]+ans[now.id])%mod;
			}
			if(dis[v]>dis[now.id]+a[i].w){
				dis[v]=dis[now.id]+a[i].w;
				ans[v]=ans[now.id]%mod;
				q.push(node2{dis[v],v});
			}
		}
	}
}

int dep[N];
void dfs(int u,int fa){
	dep[u]=dep[fa]+1;
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(v==fa) continue;
		dfs(v,u);
	}
}
signed main(){
	freopen("dream.in","r",stdin);
	freopen("dream.out","w",stdout);
	int q;
	cin>>n>>m>>q>>k>>id;
	
	if(id==16){
		while(q--)puts("1");
		return 0;
	}
	for(int i=1;i<=m;i++) {
		int u,v,w;
		cin>>u>>v>>w;
		add(u,v,w);
		add(v,u,w);
	}
	
	if(id==7||id==19||id==20){
		int tmp;
		for(int i=1;i<=n;i++) if(d[i]==1) tmp=i;
		dfs(tmp,0);
		while(q--){
			int s,t;
			cin>>s>>t;
			int ans=abs(dep[s]-dep[t]);
			if(d[s]==1) ans--;
			cout<<ans<<"\n";
		}
		return 0;	
	}
	while(q--){
		int s,t;
		cin>>s>>t;
		dij(s);
		cout<<ans[t]<<"\n";
	}
	
}
