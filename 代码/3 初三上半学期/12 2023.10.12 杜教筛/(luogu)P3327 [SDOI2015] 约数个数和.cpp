#include<bits/stdc++.h>
using namespace std;
const int N=5e4+10;
int prime[N],cnt;
bool vis[N];
int mu[N];

long long s[N];
void init() {
    mu[1]=1;
    for(int i=2;i<=N-5;i++) {
        if(!vis[i]) {
            prime[++cnt]=i;
            mu[i]=-1;
        }
        for(int j=1;j<=cnt&&i*prime[j]<=N-5;j++) {
            vis[i*prime[j]]=true;
            if(i%prime[j]==0) {
                mu[i*prime[j]]=0;
                break;
            }
            mu[i*prime[j]]=-mu[i];
        }
    }
    for(int i=1;i<=N-5;i++) mu[i]+=mu[i-1];
    for(int i=1;i<=N-5;i++) {
        int ans=0;
        for(int l=1,r;l<=i;l=r+1) {
            r=i/(i/l);
            ans+=(r-l+1)*(i/l);
        }
        s[i]=ans;
    }
}
void solve(){
    int n,m;
    cin>>n>>m;
    if(n>m) swap(n,m);
    long long ans=0;
    for(int l=1,r;l<=n;l=r+1) {
        r=min(n/(n/l),m/(m/l));
        ans+=(mu[r]-mu[l-1])*s[n/l]*s[m/l];
    }
    cout<<ans<<"\n";
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    init();
    int T;
    cin>>T;
    while(T--) solve();
    return 0;
}
