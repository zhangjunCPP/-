#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e6+10;
struct node{
    int v,w,nex;
}a[N];
int first[N],cnt;
void add(int u,int v,int w){
    a[++cnt]={v,w,first[u]};
    first[u]=cnt;
}
int n,k;
int dis[N];
bool vis[N];
int sum[N];
bool spfa(int s){
    queue<int> q;
    q.push(s);
    dis[s]=0;
    while(!q.empty()){
        int now=q.front();
        q.pop();
        vis[now]=false;
        for(int i=first[now];i;i=a[i].nex){
            int v=a[i].v;
            if(dis[v]<dis[now]+a[i].w){
                dis[v]=dis[now]+a[i].w;
                sum[v]=sum[now]+1;
                if(sum[v]>n) return false;
                if(!vis[v]){
                    q.push(v);
                    vis[v]=true;
                }
            }
        }
    }
    return true;
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
    cin>>n>>k;
    while(k--) {
        int opt,u,v;
        cin>>opt>>u>>v;
        switch (opt){
            case 1:
                add(u,v,0);
                add(v,u,0);
                break;
            case 2:
                if(u==v){puts("-1");return 0;}
                add(u,v,1);
                break;
            case 3:
                add(v,u,0);
                break;
            case 4:
                if(u==v){puts("-1");return 0;}
                add(v,u,1);
                break;
            default:
                add(u,v,0);
                break;
        }
    }
    for(int i=n;i>=1;i--)add(0,i,1);
    if(!spfa(0)) {puts("-1");return 0;}
    int ans=0;
    for(int i=1;i<=n;i++) ans+=dis[i];
    cout<<ans;
}
