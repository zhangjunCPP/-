#include<bits/stdc++.h>
using namespace std;
const int N=5e6+10;
int n;
struct node{
    int v,nex;
}a[N];
int first[N],cnt;
void add(int u,int v){
    a[++cnt]={v,first[u]};
    first[u]=cnt;
}
int calc(int x,int y){return (x-1)*n+y;}
int dis[N];
int val[N];
void bfs(int x){
    queue<int> q;
    q.push(x);
    while(!q.empty()){
        int now=q.front();
        q.pop();
        for(int i=first[now];i;i=a[i].nex){
            int v=a[i].v;
            if(dis[v]>dis[now]+1-val[now]) {
                dis[v]=dis[now]+1-val[now];
                q.push(v);
            }
        }
    }
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            dis[calc(i,j)]=min(min(i-1,j-1),min(n-i,n-j));
            if(i>1) add(calc(i,j),calc(i-1,j)),add(calc(i-1,j),calc(i,j));
            if(j>1) add(calc(i,j),calc(i,j-1)),add(calc(i,j-1),calc(i,j));
            if(i<n) add(calc(i,j),calc(i+1,j)),add(calc(i+1,j),calc(i,j));
            if(j<n) add(calc(i,j),calc(i,j+1)),add(calc(i,j+1),calc(i,j));
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            int x;
            cin>>x;
            ans+=dis[x];
            val[x]=1;
            bfs(x);
        }
    }
    cout<<ans;
}
