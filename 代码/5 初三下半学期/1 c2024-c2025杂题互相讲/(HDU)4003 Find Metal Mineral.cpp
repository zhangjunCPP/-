#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
struct node{
    int v,w,nex;
}a[N];
int first[N],cnt;
void add(int u,int v,int w){
    a[++cnt]={v,w,first[u]};
    first[u]=cnt;
}
int n,s,k;
int dp[N][20];
void dfs(int u,int fa){
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(v==fa)continue;
        dfs(v,u);
        for(int j=k;j>=0;j--){
            dp[u][j]+=dp[v][0]+2*a[i].w;
            for(int l=1;l<=j;l++)dp[u][j]=min(dp[u][j],dp[u][j-l]+dp[v][l]+l*a[i].w);
        }
    }
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    while(cin>>n>>s>>k){
        for(int i=1;i<n;i++){
            int u,v,w;
            cin>>u>>v>>w;
            add(u,v,w);add(v,u,w);
        }
        dfs(s,s);
        cout<<dp[s][k]<<"\n";
        for(int i=1;i<=n;i++)for(int j=0;j<=k;j++)dp[i][j]=0;
        for(int i=1;i<=n;i++)first[i]=0;
        cnt=0;
    }
}