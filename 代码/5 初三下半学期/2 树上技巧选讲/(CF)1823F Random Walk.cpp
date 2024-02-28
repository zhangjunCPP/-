#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10,mod=998244353;
struct node{
    int v,nex;
}a[N];
int first[N],cnt;
int deg[N];
void add(int u,int v){
    a[++cnt]={v,first[u]};
    first[u]=cnt;
    deg[v]++;
}
int qpow(int x,int y){
    int ans=1;
    while(y){
        if(y&1)ans=ans*x%mod;
        y>>=1;
        x=x*x%mod;
    }
    return ans%mod;
}
int n,s,t;
int A[N],B[N];
void dfs(int u,int fa){
    int tmp1=0,tmp2=(u==s);
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(v==fa)continue;
        dfs(v,u);
        tmp1=(tmp1+A[v]*qpow(deg[v],mod-2)%mod)%mod;
        tmp2=(tmp2+B[v]*qpow(deg[v],mod-2)%mod)%mod;
    }
    int inv=qpow(1-tmp1+mod,mod-2)%mod;
    tmp2=tmp2*inv%mod;
    tmp1=qpow(deg[fa],mod-2)%mod*inv%mod;
    A[u]=tmp1,B[u]=tmp2;
}
int dp[N];
void calc(int u,int fa){
    dp[u]=(A[u]*dp[fa]%mod+B[u]%mod)%mod;
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(v==fa)continue;
        calc(v,u);
    }
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>n>>s>>t;
    for(int i=1;i<n;i++) {
        int u,v;
        cin>>u>>v;
        add(u,v);
        add(v,u);
    }
    dfs(t,0);
    calc(t,0);
    dp[t]=1;

    for(int i=1;i<=n;i++)cout<<dp[i]<<" ";

}