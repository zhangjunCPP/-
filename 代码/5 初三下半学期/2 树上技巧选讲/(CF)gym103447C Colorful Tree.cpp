#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
struct node{
    int v,nex;
}a[N];
int first[N],cnt;
void add(int u,int v){
    a[++cnt]={v,first[u]};
    first[u]=cnt;
}
map<int,int> mp[N];
int dp[N];
int c[N];
void dfs(int u){
    if(c[u]){dp[u]=1,mp[u][c[u]]=1;return;}
    int Max=1;
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        dfs(v);
        dp[u]+=dp[v];
        if(mp[u].size()<mp[v].size())swap(mp[u],mp[v]);
        for(auto j:mp[v])Max=max(Max,mp[u][j.first]+=j.second);
    }
    if(Max>1){
        map<int,int> tmp;
        for(auto j:mp[u])if(j.second==Max)tmp[j.first]=1;
        swap(tmp,mp[u]);
    }
    dp[u]=dp[u]+1-Max;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr),cout.tie(nullptr);
    int n;
    cin>>n;
    for(int i=1;i<n;i++){
        int x;
        cin>>x;
        add(x,i+1);
    }
    for(int i=1;i<=n;i++)cin>>c[i];
    dfs(1);
    cout<<dp[1];
}