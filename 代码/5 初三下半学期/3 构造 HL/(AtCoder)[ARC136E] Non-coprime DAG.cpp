#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
bool flag[N];
int Min[N];
int prime[N],cnt;
int c[N];
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr),cout.tie(nullptr);
    int n;
    cin>>n;
    for(int i=2;i<=n;i++){
        if(!flag[i])Min[i]=i,prime[++cnt]=i;
        for(int j=1;j<=cnt&&i*prime[j]<=n;j++){
            flag[i*prime[j]]=true;
            Min[i*prime[j]]=prime[j];
            if(!(i%prime[j]))break;
        }
    }
    for(int i=1;i<=n;i++){
        int x;
        cin>>x;
        if(i==1)c[1]+=x,c[n+1]-=x;
        else if(i&1)c[i-Min[i]+1]+=x,c[i+Min[i]-1+1]-=x;
        else c[i]+=x,c[i+1]-=x;
    }
    int ans=0;
    for(int i=1;i<=n;i++)c[i]+=c[i-1];
    for(int i=1;i<=n;i++)ans=max(ans,c[i]);
    cout<<ans;
    return 0;
}