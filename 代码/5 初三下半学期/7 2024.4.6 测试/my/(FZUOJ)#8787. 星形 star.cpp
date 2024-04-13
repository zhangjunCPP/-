#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+10;
const int mod=998244353;
int n;
int ans;
vector<int> G[N];
int a[N];
int fa[N];
int find(int x){if(fa[x]!=x)fa[x]=find(fa[x]);return fa[x];}
int deg[N];
void dfs(int k){
    if(k>n){
        for(int i=1;i<=n;i++)fa[i]=i,deg[i]=0;
        for(int i=1;i<=n;i++){
            if(a[i]){
                for(int j:G[i]){
                    if(a[j]){
                        int fi=find(i),fj=find(j);
                        if(fi!=fj)fa[fj]=fi,deg[i]++,deg[j]++;
                    }
                }
            }
        }
        int num=0;
        for(int i=1;i<=n;i++)if(a[i]&&find(i)==i)num++;
        if(num==1){
            num=0;
            for(int i=1;i<=n;i++)if(deg[i]>=3)num++;
            if(num==1)ans=(ans+1)%mod;
        }
        return;
    }
    a[k]=0;
    dfs(k+1);
    a[k]=1;
    dfs(k+1);
}
int fac[N],inv[N];
void init(){
	fac[0]=1;
	for(int i=1;i<N;i++)fac[i]=fac[i-1]*i%mod;
	inv[1]=1;
	for(int i=2;i<N;i++)inv[i]=(mod-mod/i)*inv[mod%i]%mod;
	for(int i=2;i<N;i++)inv[i]=inv[i-1]*inv[i]%mod;
}
int C(int n,int m){return fac[n]*inv[m]%mod*inv[n-m]%mod;}
signed main(){
    cin>>n;
    bool flag=true;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        if(u!=1||v!=i+1)flag=false;
        deg[u]++,deg[v]++;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    int sum=0;
    for(int i=1;i<=n;i++)if(deg[i]>=3)sum++;
    if(sum==0){cout<<0<<"\n";return 0;}
    if(flag){
        init();
        for(int i=0;i<=n-4;i++)ans=(ans+C(n-1,i)%mod)%mod;
        cout<<ans+1;
        return 0;
    }
    dfs(1);
    cout<<ans;
}