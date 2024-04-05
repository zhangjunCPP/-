//2-n+\sum_{m=1}^{n-1}2^{\gcd(m,n)}
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
int qpow(int x,int y){
    int ans=1;
    while(y){
        if(y&1)ans=ans*x%mod;
        y>>=1;
        x=x*x%mod;
    }
    return ans%mod;
}
int n;
vector<pair<int,int>> p;
int ans;
void dfs(int k,int s,int s1,int s2){
    if(k==p.size()){
        if(s==1)return;
        ans=(ans+qpow(2,n/s)%mod*(s/s2%mod*s1%mod)%mod)%mod;
        return;
    }
    dfs(k+1,s,s1,s2);
    s1=s1*(p[k].first-1);
    s2=s2*p[k].first;
    for(int i=1;i<=p[k].second;i++){
        s=s*p[k].first;
        dfs(k+1,s,s1,s2);
    }
}
signed main(){
    cin>>n;
    int tmp=n;
    for(int i=2;i*i<=tmp;i++){
        if(tmp%i==0){
            int tot=0;
            while(tmp%i==0)tmp/=i,tot++;
            p.emplace_back(i,tot);
        }
    }
    if(tmp>1)p.emplace_back(tmp,1);
    dfs(0,1,1,1);

    cout<<((ans+2-n)%mod+mod)%mod;
}