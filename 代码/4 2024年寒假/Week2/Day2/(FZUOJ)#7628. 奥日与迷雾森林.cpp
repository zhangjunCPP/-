#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e3+10;
struct node{
    int v,nex;
}a[N*20];
int first[N],cnt;
void add(int u,int v){
    a[++cnt]={v,first[u]};
    first[u]=cnt;
}
int n,m;
int dis[N][N];
int fa[N][N][13];
void bfs(int t){
    queue<int> q;
    q.push(t);
    dis[t][t]=0;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(int i=first[u];i;i=a[i].nex){
            int v=a[i].v;
            if(v==t) continue;
            if(!fa[t][v][0]) fa[t][v][0]=u,q.push(v);
            else if(fa[t][v][0]>u) fa[t][v][0]=u;
        }
    }
    for(int j=1;j<=12;j++){
        for(int i=1;i<=n;i++){
            fa[t][i][j]=fa[t][fa[t][i][j-1]][j-1];
        }
    }
    q.push(t);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(int i=first[u];i;i=a[i].nex){
            int v=a[i].v;
            if(v==t) continue;
            if(fa[t][v][0]==u){
                if(dis[t][v]==-1) q.push(v);
                dis[t][v]=dis[t][u]+1;
            }
        }
    }
}
signed main(){
    int q,ty;
    cin>>n>>m>>q>>ty;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        add(v,u);
    }
    memset(dis,-1,sizeof dis);
    for(int i=1;i<=n;i++) bfs(i);
    int last=1;
    while(q--){
        int s,t,k;
        cin>>s>>t>>k;
        if(ty){
            s=(s^last)%n+1;
            t=(t^last)%n+1;
            k=(k^last)%n+1;
        }
        if(dis[t][s]==-1||dis[t][s]<k-1) {puts("-1");last=1;}
        else {
            k--;
            int now=s;
            for(int i=12;i>=0;i--){
                if((k>>i)&1) now=fa[t][now][i];
            }
            cout<<now<<"\n";
            last=now;
        }
    }
}