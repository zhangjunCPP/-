#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10,mod=1e9+7;
int qpow(int x,int y){
    int ans=1;
    while(y){
        if(y&1)ans=ans*x%mod;
        y>>=1;
        x=x*x%mod;
    }
    return ans%mod;
}
int a[N];
int c[N];
signed main(){
    int n,k;
    cin>>n>>k;
    for(int i=1;i<=n;i++)cin>>a[i];
    c[0]=1;
    for(int i=1;i<=n;i++){
        for(int j=i;j;j--)c[j]=(c[j]*a[i]%mod-c[j-1]+mod)%mod;
        c[0]=c[0]*a[i]%mod;
    }
    int ans=0;
    int inv=qpow(n,mod-2)%mod;
    int tmp=1;
    for(int i=0;i<=n;i++){
        ans=(ans+c[i]*tmp)%mod;
        tmp=tmp*(k-i)%mod*inv%mod;
    }
    cout<<(c[0]-ans+mod)%mod;
}