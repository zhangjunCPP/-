#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
const int INF=0x3f3f3f3f3f3f3f3f;
int n,m;
struct node{
	int v,w,nex;
}a[N];
int first[N],cnt;
void add(int u,int v,int w){
	a[++cnt]={v,w,first[u]};
	first[u]=cnt; 
}
struct node2{
    int id,val;
    bool operator<(const node2 &oth) const {
        return val>oth.val;
    }
};
int dis[N];
bool vis[N];
void dij(int s){
	memset(dis,0x3f,sizeof dis);
	memset(vis,0,sizeof vis);
	priority_queue<node2> q;
	dis[s]=0; 
    q.push({s,0});
	while(!q.empty()){
		auto now=q.top(); 
        q.pop();
        int u=now.id;
		if(vis[u]) continue;
		vis[u]=1;
		for(int i=first[u];i;i=a[i].nex){
			int v=a[i].v;
			if(dis[v]>dis[u]+a[i].w){
                dis[v]=dis[u]+a[i].w;
                q.push({v,dis[v]});
            }
		}
	}
}

queue<int> s[N];
int dis2[N];
void bfs(int c){
    int tmp=0;
	for(int i=0;i<=tmp;i++){
		while(!s[i].empty()){
			int now=s[i].front();
            s[i].pop();
			if(dis2[now]<i) continue;
			for(int j=first[now];j;j=a[j].nex){
				int v=a[j].v;
				if(dis2[v]>dis2[now]+dis[now]+a[j].w-dis[v]){
					dis2[v]=dis2[now]+dis[now]+a[j].w-dis[v];
					if(dis2[v]<=min(c,n-1)){
						s[dis2[v]].push(v);
						tmp=max(tmp,dis2[v]);
					}
				}
			}
		}
    }
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int q;
    cin>>n>>m>>q;
	for(int i=1;i<=m;i++) {
		int u,v,w;
        cin>>u>>v>>w;
		add(u,v,w); 
	}
	dij(1);
	while(q--){
		int opt,v;
        cin>>opt>>v;
		if(opt==1){ 
            if(dis[v]==INF)cout<<"-1\n";
            else cout<<dis[v]<<"\n";
        }
		else{
			for(int i=1;i<=v;i++){int tmp;cin>>tmp;a[tmp].w++;}
			memset(dis2,0x3f,sizeof dis2);
			dis2[1]=0; 
            s[0].push(1);
			bfs(v);
			for(int i=1;i<=n;i++) dis[i]=min(INF,dis[i]+dis2[i]);
		}
	}
	return 0;
}
