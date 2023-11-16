#include <bits/stdc++.h>
#define int long long
using namespace std;
int mod;
int qpow(int x,int y) {
    int ans=1;
    while(y){
        if(y&1) ans=(ans*x)%mod;
        x=(x*x)%mod;
        y>>=1;
    }
    return ans%mod;
}
int c(int n,int m){
    int ans1=1,ans2=1;
    for(int i=1;i<=m;i++) {
        ans1=(ans1*(n-i+1))%mod;
        ans2=(ans2*i)%mod;
    }
    return (ans1*qpow(ans2,mod-2))%mod;
}
signed main(){
    int n,m;
    cin>>n>>m>>mod;
    cout<<c(n+m-1,2*m-1);
    return 0;
}
