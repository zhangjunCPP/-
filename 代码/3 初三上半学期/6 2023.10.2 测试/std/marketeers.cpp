#include<bits/stdc++.h>
#define ll int
#define For(i,a,b) for(ll i=(a);i<=(b);++i)
#define Rep(i,a,b) for(ll i=(a);i>=(b);--i)
#define pb push_back
const ll N=5e5+10;
const ll p=998244353;
using namespace std;
void PLUS(ll &a,ll b){a=a+b>p?a+b-p:a+b;}

ll n,m,k;
vector<ll>a[N];
ll b[N];
ll c[N],id[N];
vector<ll>f[N];

int main(){
    
    freopen("marketeers.in","r",stdin);
    freopen("marketeers.out","w",stdout);
    scanf("%d",&n);
    For(i,1,n){
        scanf("%d",&k);
        For(j,1,k){
            ll x;
            scanf("%d",&x);
            a[i].pb(x);
            b[++m]=x;
        }
    }
    //离散化
    sort(b+1,b+m+1);
    m=unique(b+1,b+m+1)-b-1;
    For(i,1,n){
        For(j,0,(ll)a[i].size()-1){
            a[i][j]=lower_bound(b+1,b+m+1,a[i][j])-b;
        }
        sort(a[i].begin(),a[i].end());
    }
    //构造边界
    set<ll>t;
    t.insert(1e9);
    For(i,1,n){
        id[i]=i;
        ll x=*t.upper_bound(a[i][0]);
        ll pos=lower_bound(a[i].begin(),a[i].end(),x)-a[i].begin()-1;
        c[i]=a[i][max(0,pos)];
        t.insert(c[i]);
        f[i].resize(a[i].size());
    }
    //重新排序
    sort(id+1,id+n+1,[&](ll x,ll y){return c[x]<c[y]||c[x]==c[y]&&x<y;});
    //DP
    a[0].pb(0),f[0].pb(1);
    For(I,0,n-1){
        ll i=id[I],j=id[I+1];
        For(k,0,(ll)f[i].size()-1){
            if(f[i][k]==0)continue;
            ll pos;
            if(i<j)pos=lower_bound(a[j].begin(),a[j].end(),a[i][k])-a[j].begin();
            else pos=upper_bound(a[j].begin(),a[j].end(),a[i][k])-a[j].begin();
            if(pos<(ll)f[j].size())PLUS(f[j][pos],f[i][k]);
        }
        For(k,1,(ll)f[j].size()-1){
            PLUS(f[j][k],f[j][k-1]);
        }
    }
    ll ans=0;
    For(k,0,(ll)f[id[n]].size()-1)PLUS(ans,f[id[n]][k]);
    printf("%d",ans);
    return 0;
}
