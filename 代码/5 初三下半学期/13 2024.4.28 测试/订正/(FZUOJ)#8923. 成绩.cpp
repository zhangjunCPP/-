#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353;
int qpow(int x,int y){
    int ans=1;
    while(y){
        if(y&1)ans=ans*x%mod;
        y>>=1;
        x=x*x%mod;
    }
    return ans%mod;
}
void solve(){
    int n,a,b;
    cin>>n>>a>>b;
    int inv=qpow(n-1,mod-2)%mod;
    int inv2=qpow(2,mod-2)%mod;
    int sum=0;
    //i<a a+b-i-2
    int start=a+b-1-2;
    int end=a+b-(a-1)-2;
    sum=sum+max(0ll,a+b-n-1-1)*(n-1);
    start=min(start,n-1);
    sum=(sum+(start+end)%mod*max(0ll,((a-1)-(max(0ll,a+b-n-1-1)+1)+1))%mod*inv2%mod)%mod;
    //i>a a+b-i-1
    start=a+b-(a+1)-1;
    if(start>0){
        end=max(0ll,a+b-n-1);
        sum=(sum+(start+end)%mod*max(0ll,(min(a+b-1,n)-(a+1)+1))%mod*inv2%mod)%mod;
    }
    cout<<(sum*inv%mod+1)%mod<<"\n";
}
signed main(){
    ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
    int T;
    cin>>T;
    while(T--)solve();
}