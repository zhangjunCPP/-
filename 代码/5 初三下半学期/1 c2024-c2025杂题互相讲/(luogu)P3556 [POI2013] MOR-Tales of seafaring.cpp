#include <bits/stdc++.h>

using namespace std;
const int N=5010,M=1e6+10;
struct node{int v,nex;}a[N*2];
int first[N],cnt;
void add(int u,int v){
    a[++cnt]={v,first[u]};
    first[u]=cnt;
}
struct node2{int v,d,id;};
vector<node2> q[N];
int dis[N][2];
bool vis[N][2];
int ans[M];
int main(){
    int n,m,k;
    cin>>n>>m>>k;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        add(u,v);
        add(v,u);
    }
    for(int i=1;i<=k;i++){
        int u,v,d;
        cin>>u>>v>>d;
        q[u].push_back({v,d,i});
    }
    for(int i=1;i<=n;i++){
        if(!q[i].empty()){
            memset(dis,0x3f,sizeof dis);
            memset(vis, false,sizeof vis);
            queue<pair<int,int> >Q;
            dis[i][0]=0;
            Q.push({i,0});
            while(!Q.empty()){
                auto now=Q.front();
                Q.pop();
                int u=now.first;
                if(vis[u][now.second])continue;
                vis[u][now.second]=true;
                for(int j=first[u];j;j=a[j].nex){
                    int v=a[j].v;
                    if(dis[v][now.second^1]>dis[u][now.second]+1){
                        dis[v][now.second^1]=dis[u][now.second]+1;
                        Q.push({v,now.second^1});
                    }
                }
            }
            for(auto it:q[i]){
                if(!first[it.v])ans[it.id]=0;
                else ans[it.id]=dis[it.v][it.d&1]<=it.d;
            }
        }
    }
    for(int i=1;i<=k;i++)puts(ans[i]?"TAK":"NIE");
}