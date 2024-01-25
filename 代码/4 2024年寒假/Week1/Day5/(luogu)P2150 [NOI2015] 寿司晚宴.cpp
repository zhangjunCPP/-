#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=505;
int n,mod;
const int p[10]={0,2,3,5,7,11,13,17,19,23};
struct node{
    int x,S;
    int big;
    void calc(int now){
        x=now;
        S=big=0;
        for(int i=1;i<=8;i++){
            if(now%p[i]==0){
                S|=1<<(i-1);
                while(now%p[i]==0) now/=p[i];
            }
        }
        if(now>1) big=now;
    }
}a[N];
bool cmp(const node&x,const node&y){return x.big<y.big;}
int dp[N][N];
int f1[N][N];
int f2[N][N];
signed main(){
    cin>>n>>mod;
    for(int i=2;i<=n;i++)a[i-1].calc(i);
    sort(a+1,a+n,cmp);
    dp[0][0]=1;
    for(int i=1;i<n;i++){
        if(i==1||a[i].big!=a[i-1].big||a[i].big==0){
            memcpy(f1,dp,sizeof f1);
            memcpy(f2,dp,sizeof f2);
        }
        for(int S=255;S>=0;S--){
            int tmp=0;
            for(int j=1;j<=8;j++)if(!(S&(1<<(j-1)))) tmp|=1<<(j-1);
            for(int T=tmp;;T=tmp&(T-1)){
                if(!(T&a[i].S))f1[S|a[i].S][T]=(f1[S|a[i].S][T]+f1[S][T])%mod;
                if(!(S&a[i].S))f2[S][T|a[i].S]=(f2[S][T|a[i].S]+f2[S][T])%mod;
                if(!T) break;
            }
        }
        if(i==n-1||a[i].big!=a[i+1].big||a[i].big==0){
            for(int S=255;S>=0;S--){
                int tmp=0;
                for(int j=1;j<=8;j++)if(!(S&(1<<(j-1)))) tmp|=1<<(j-1);
                for(int T=tmp;;T=tmp&(T-1)){
                    dp[S][T]=((f1[S][T]+f2[S][T])%mod-dp[S][T]+mod)%mod;
                    if(!T) break;
                }
            }
        }
    }
    int ans=0;
    for(int S=255;S>=0;S--){
        int tmp=0;
        for(int j=1;j<=8;j++)if(!(S&(1<<(j-1)))) tmp|=1<<(j-1);
        for(int T=tmp;;T=tmp&(T-1)){
            ans=(ans+dp[S][T]%mod)%mod;
            if(!T) break;
        }
    }
    cout<<ans;
    return 0;
}