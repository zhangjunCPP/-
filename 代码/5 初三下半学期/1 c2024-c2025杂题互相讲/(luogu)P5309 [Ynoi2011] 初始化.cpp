#include<iostream>
#define ll long long
using namespace std;
const int N=2e5+10;
const ll mod=1e9+7;
const int block=128;
int st[N],ed[N],belong[N];
ll a[N];
ll sum[N];
int n,m;
ll pre[130][130];
void update(int x,int y,int z){
    if(x>=block){
        for(int i=y;i<=n;i+=x){
            a[i]+=z;
            sum[belong[i]]+=z;
        }
        return;
    }
    for(int i=y;i<=x;i++)pre[x][i]+=z;
}
ll ans;
int query(int l,int r){
    ans=0;
    int p=belong[l],q=belong[r];
    if(p==q)for(int i=l;i<=r;i++)ans+=a[i];
    else{
        for(int i=l;i<=ed[p];i++)ans+=a[i];
        for(int i=st[q];i<=r;i++)ans+=a[i];
        for(int i=p+1;i<=q-1;i++)ans+=sum[i];
    }
    for(int i=1;i<block;i++){
        int left=(l-1)/i+1,right=(r-1)/i+1;
        ans=(ans+(right-left-1)*pre[i][i]%mod+pre[i][(r-1)%i+1]+pre[i][i]-pre[i][(l-1)%i]);
    }
    return (ans+mod)%mod;
}
signed main(){
    ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
    cin>>n>>m;
    int t=(n-1)/block+1;
    for(int i=1;i<=t;i++){
        st[i]=(i-1)*block+1;
        ed[i]=i*block;
    }
    ed[t]=n;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1;i<=t;i++)for(int j=st[i];j<=ed[i];j++)sum[i]+=a[j],belong[j]=i;
    while(m--){
        int opt;
        cin>>opt;
        if(opt==1){
            int x,y,z;
            cin>>x>>y>>z;
            update(x,y,z);
        }
        else {
            int l,r;
            cin>>l>>r;
            cout<<query(l,r)<<"\n";
        }
    }
}