#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
int c[N],tmp[N];
int l[N],r[N];
int u[N],v[N];
int cnt[N];
signed main() {
    freopen("color.in","r",stdin);
    freopen("color.out","w",stdout);
    int n,m,q;
    cin>>n>>m>>q;
    for(int i=1;i<=n;i++)cin>>c[i],tmp[i]=c[i];
    for(int i=1;i<=m;i++) cin>>l[i]>>r[i];
    for(int i=1;i<=q;i++) cin>>u[i]>>v[i];
    int ans=0;
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++) cnt[j]=0;
        int sum=0;
        for(int j=l[i];j<=r[i];j++) {
            cnt[c[j]]++;
            if(cnt[c[j]]==1) sum++;
        }
        if(sum==(r[i]-l[i]+1)){ans^=0;continue;}
        bool flag=false;
        for(int j=1;j<=q;j++) {
            // for(int k=1;k<=n;k++) cout<<c[k]<<" ";
            // cout<<"\n"<<sum<<"\n";
            if(u[j]<l[i]||u[j]>r[i]) continue;
            cnt[c[u[j]]]--;
            if(cnt[u[j]]==0) sum--;
            cnt[v[j]]++;
            if(cnt[v[j]]==1) sum++;
            if(sum==(r[i]-l[i]+1)) {ans^=j;flag=true;break;}
            c[u[j]]=v[j];
        }
        if(!flag) {ans^=m+i;}
        for(int j=1;j<=n;j++) c[j]=tmp[j];
    }
    cout<<ans;
}