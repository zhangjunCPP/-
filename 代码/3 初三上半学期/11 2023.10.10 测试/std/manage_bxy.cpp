
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll maxn=5e5+5;

ll n,m;
ll a[maxn], ans[maxn], bit[maxn];
ll lst[maxn];

ll lowbit(ll x) {
    return x&(-x);
}

void add(ll x) {
    for(ll i=x;i>0;i-=lowbit(i)) bit[i]++;
    return ;
}

ll ask(ll x) {
    ll res=0;
    for(ll i=x;i<=m;i+=lowbit(i)) res+=bit[i];
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin>>n>>m;
    for(ll i=1;i<=m;i++) cin>>a[i];
    int sum=0;
    for(ll i=1;i<=m;i++) {
        if(!lst[a[i]]) ans[n]++;
        else {
            ll v=i-lst[a[i]]-1-ask(lst[a[i]]);
            ans[min(v,n)]++;
            add(lst[a[i]]);
        }
        lst[a[i]]=i;
    }
    for(ll i=n;i>=1;i--) ans[i]+=ans[i+1];
    for(ll i=1;i<=n;i++) cout<<ans[i]<<' '; cout<<'\n';
    return 0;
}
