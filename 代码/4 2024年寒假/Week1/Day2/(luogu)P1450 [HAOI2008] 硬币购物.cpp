#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
int c[N],d[N];
int n;
int dp[N];
signed main(){
    for(int i=1;i<=4;i++)cin>>c[i];
    cin>>n;
    dp[0]=1;
    for(int i=1;i<=4;i++)for(int j=c[i];j<N;j++)dp[j]+=dp[j-c[i]];
    while(n--){
        int s;
        cin>>d[1]>>d[2]>>d[3]>>d[4]>>s;
        int ans=dp[s];
        for(int i=1;i<=15;i++){
            int t=s,sum=0;
            for(int j=1;j<=4;j++) {
                if((i>>(j-1))&1){
                    sum++;
                    t-=c[j]*(d[j]+1);
                }
            }
            if(t>=0){
                if(sum&1)ans-=dp[t];
                else ans+=dp[t];
            }
        }
        cout<<ans<<"\n";
    }
    return 0;
}