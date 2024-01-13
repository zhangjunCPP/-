#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e6+10;
int a[N];
int dp[N];
bool flag[N];
int vis[N];
void solve(){
    int n,m;
    cin>>n>>m;
    for(int i=0;i<=m;i++)flag[i]=false,vis[i]=0;
    int Min=0x3f3f3f3f;
    for(int i=1;i<=n;i++)cin>>a[i],flag[a[i]]=true,Min=min(Min,a[i]);
    int ans=m;
    for(int i=1;i<=m;i++){
        dp[i]=i;
        if(flag[i])vis[i]=1;
    }
    int Max=m;
    for(int i=m;i>=1;i--){
        for(int j=i*i;j<=m;j+=i){
            if(flag[j])vis[dp[j]]--;
            dp[j]=min(dp[j],dp[j/i]);
            if(flag[j])vis[dp[j]]++;
        }
        while(!vis[Max])Max--;
        if(i<=Min)ans=min(ans,Max-i);
    }
    cout<<ans<<"\n";
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T;
    cin>>T;
    while(T--)solve();
}