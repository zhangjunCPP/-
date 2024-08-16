#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll maxn=2e5+5;

ll n,mo;
ll fac[maxn], ifac[maxn], pw[maxn], s[maxn], s2[maxn], F[maxn];

vector<ll> D[maxn];

ll qpow(ll a,ll p) {
    ll res=1;
    while(p) {
        if(p&1) res=res*a%mo;
        p>>=1, a=a*a%mo;
    }
    return res;
}

ll f[maxn], prime[maxn], vis[maxn], mu[maxn];
ll q[maxn], l, r, cnt;

ll S(ll x) {
    return (x*(x+1)/2)%mo;
}

int main() {
    freopen("graph.in","r",stdin);
    freopen("graph.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin>>n>>mo;
    ll ans=0;
    fac[0]=pw[0]=1;
    for(ll i=1;i<=n;i++) fac[i]=fac[i-1]*i%mo, pw[i]=pw[i-1]*n%mo;
    ifac[n]=qpow(fac[n],mo-2);
    for(ll i=n-1;i>=0;i--) ifac[i]=ifac[i+1]*(i+1)%mo;
    mu[1]=1;
    for(ll i=2;i<=n;i++) {
        if(!vis[i]) mu[i]=mo-1, prime[++cnt]=i;
        for(int j=1;j<=cnt&&prime[j]*i<=n;j++) {
            vis[i*prime[j]]=1;
            if(i%prime[j]==0) {
                mu[i*prime[j]]=0;
                break;
            }
            mu[i*prime[j]]=(mo-mu[i])%mo;
        }
    }
    for(ll v=1;v<=n;v++) {
        for(ll i=v;i<=n;i+=v) {
            D[i].push_back(v);
            (F[i]+= mu[v]*v)%= mo;
        }
    }
    for(ll len=1;len<=n;len++) {
        for(auto T:D[len]) (s[len]+= (n/T)*(len/T)%mo*F[T]%mo)%= mo;
        (s[len]+= s[len-1])%= mo;
    }
    for(ll d=1;d<=n;d++) {
        for(ll j=1;j<=d;) {
            ll k=d/(d/j), v=d/j;
            s2[d]+= (k-j+1)*(n-(d+v-1)/v+1);
            j=k+1;
        }
    }
    for(ll i=1;i<=n;i++) (s2[i]+= s2[i-1])%= mo;
    for(ll i=1;i<=n;i++) (s2[i]+= s2[i-1])%= mo;
    for(ll c=1;c<=n;c++) {
        ll ks=fac[n]*ifac[n-c]%mo*pw[n-c]%mo;
        (ans+= ks*(S(c)%mo*S(n-1)%mo-S(n)+mo)%mo)%= mo;
        (ans+= ks*s[c]%mo)%= mo;
        if(c>=2) (ans+= ks*s2[c-2]%mo)%= mo;
    }
    cout<<ans<<'\n';
    return 0;
}