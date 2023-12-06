#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
struct node{
    int v,w,nex;
}a[N];
int first[N],cnt;
void add(int u,int v,int w){
    a[++cnt]={v,w,first[u]};
    first[u]=cnt;
}
int dis[N];
bool vis[N];
void spfa() {
    queue<int> q;
    memset(dis,0x3f,sizeof dis);
    dis[1]=1;
    vis[1]=true;
    q.push(1);
    while(!q.empty()){
        int now=q.front();
        q.pop();
        vis[now]=false;
        for(int i=first[now];i;i=a[i].nex){
            int v=a[i].v;
            if(dis[v]>dis[now]+a[i].w){
                dis[v]=dis[now]+a[i].w;
                if(!vis[v]){
                    vis[v]=true;
                    q.push(v);
                }
            }
        }
    }
}
signed main(){
    int h;
    cin>>h;
    int x,y,z;
    cin>>x>>y>>z;
    for(int i=0;i<z;i++) { //以z为模数
        add(i,(i+x)%z,x);
        add(i,(i+y)%z,y);
    }
    spfa();
    int ans=0;
    for(int i=0;i<z;i++) {
        if(dis[i]<=h) {
            ans+=(h-dis[i])/z+1;
        }
    }
    cout<<ans;
}