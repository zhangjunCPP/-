#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll maxn=1e6+5;

ll a[maxn], s[maxn];

int main() {
    freopen("b.in","r",stdin);
    freopen("b.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    ll n,ans=0; cin>>n;
    for(ll i=1;i<=n;i++) cin>>a[i];
    sort(a+1,a+n+1);
    for(ll i=1;i<=n;i++) s[i]=s[i-1]+a[i];
    ll j=0;
    for(ll i=1;i<=n;i++) {
        ll cnt=i, sum=s[i];
        while(j<=i&&a[j]*i<=sum) j++;
        ans=max(ans,i-j+1);
    }
    cout<<ans<<'\n';
    return 0;
}
