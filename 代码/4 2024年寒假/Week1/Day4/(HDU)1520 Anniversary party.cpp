#include<bits/stdc++.h>
using namespace std;
const int N=100005;
struct node{
    int v,nex;
}a[N*2];
int cnt,first[N];
void add(int u,int v){
    a[++cnt]={v,first[u]};
    first[u]=cnt;
}
int val[N];
int dp[N][2];
void dfs(int u){
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        dfs(v);
        dp[u][0]+=max(dp[v][1],dp[v][0]);
        dp[u][1]+=dp[v][0];
    }
    dp[u][1]+=val[u];
}
int deg[N];
void init(){
    memset(first,0,sizeof first);
    cnt=0;
    memset(deg,0,sizeof deg);
    memset(dp,0,sizeof dp);
}
int main(){
    int n;
    while(cin>>n){
        init();
        for(int i=1;i<=n;i++)cin>>val[i];
        int l,k;
        while(cin>>l>>k){
            if(l==0&&k==0)break;
            add(k,l);
            deg[l]++;
        }
        int root;
        for(int i=1;i<=n;i++)if(deg[i]==0)root=i;
        dfs(root);
        cout<<max(dp[root][1],dp[root][0]);
    }
}
