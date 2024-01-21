#include <bits/stdc++.h>
#define int long long
using namespace std;
int mod;
int qpow(int x,int y){
    int ans=1;
    while(y){
        if(y&1) ans=ans*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return ans;
}
int solve(int a,int b){
    unordered_map<int,int> mp;
    if(a%mod==0)return -1;
    int t=ceil(sqrt(mod));
    int k=b%mod;
    mp[k]=0;
    for(int i=1;i<=t;i++){
        k=k*a%mod;
        mp[k]=i;
    }
    k=qpow(a,t);
    int now=1;
    for(int i=1;i<=t;i++){
        now=now*k%mod;
        if(mp[now]){
            int ans=(i*t-mp[now]);
            return (ans%mod+mod)%mod;
        }
    }
    return -1;
}
signed main(){
    int b,n;
    cin>>mod>>b>>n;
    int ans=solve(b,n);
    if(ans==-1)cout<<"no solution";
    else cout<<ans;
}