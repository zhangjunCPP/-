#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=(1<<20),mod=1e9+1;
int n;
bool flag[N];
bool vis[N];
int sum[N],line;
int a[50][50];
void init(int x){
    vis[x]=true;
    a[0][1]=1;
    for(int i=1;;i++){
        if(i==1)a[i][1]=x;
        else a[i][1]=a[i-1][1]*3;
        vis[a[i][1]]=true;
        if(a[i][1]>n){line=i-1;break;}
        for(int j=2;;j++){
            a[i][j]=a[i][j-1]*2;
            vis[a[i][j]]=true;
            if(a[i][j]>n){sum[i]=j-1;break;}
        }
    }
}
int dp[50][N];
int solve(){
    for(int i=0;i<(1<<sum[1]);i++)dp[1][i]=flag[i];
    for(int i=2;i<=line;i++){
        for(int j=0;j<(1<<sum[i]);j++){
            dp[i][j]=0;
            if(!flag[j])continue;
            for(int k=0;k<(1<<sum[i-1]);k++){
                if(!flag[k])continue;
                if(!(j&k))dp[i][j]=(dp[i][j]+dp[i-1][k])%mod;
            }
        }
    }
    int ans=0;
    for(int i=0;i<(1<<sum[line]);i++)ans=(ans+dp[line][i])%mod;
    return ans;
}
signed main(){
    for(int i=0;i<N;i++){
        if(i&(i<<1))flag[i]=false;
        else flag[i]=true;
    }
    cin>>n;
    int ans=1;
    for(int i=1;i<=n;i++){
        if(!vis[i]){
            init(i);
            ans=ans*solve()%mod;
        }
    }
    cout<<ans%mod;

}