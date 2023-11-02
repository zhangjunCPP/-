#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1e5+10;
ll dp1[N],dp2[N][330];
ll sum1[N],sum2[N];
int main(){
    int n,mod;
    cin>>n>>mod;
    int base=sqrt(n);
    int tmp=n/base+1;
    sum1[0]=1;
    dp1[0]=1;
    for(int j=1;j<base;++j) {
        for(int i=1;i<=n;++i) {
            if(i>=j) dp1[i]=(dp1[i]+dp1[i-j])%mod;
        }
    }
    for(int i=1;i<=n;++i) sum1[i]=dp1[i]%mod;

    sum2[0]=1;
    dp2[base][1]=1;
    for(int i=0;i<=n;++i) {
        for(int j=1;j<=i&&j<=tmp;++j) {
            dp2[i][j]=(dp2[i][j]+dp2[i-j][j])%mod;
            if(i>=base) dp2[i][j]=(dp2[i][j]+dp2[i-base][j-1])%mod;
        }
    }
    for(int i=0;i<=n;++i) for(int j=1;j<=tmp;++j) sum2[i]=(sum2[i]+dp2[i][j])%mod;
    ll ans=0;
    for(int i=0;i<=n;++i) ans=(ans+sum1[i]*sum2[n-i]%mod)%mod;
    cout<<ans;
}