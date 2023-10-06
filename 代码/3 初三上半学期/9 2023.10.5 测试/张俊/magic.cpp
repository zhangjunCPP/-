#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int l[N],r[N],c[N];

int n;
int ans;
int q[N];
bool vis[N];

bool vis2[N];
int sum[N];
void dfs(int now) {
    if(now>n){
        for(int i=1;i<=n;i++) vis2[i]=0,sum[i]=0;
        for(int i=1;i<=n;i++) {
            int now=q[i];
            vis2[now]=true;
            for(int j=l[now];j<=r[now];j++) if(!vis2[j]) sum[j]+=c[now];
        }
        int tmp=0;
        for(int i=1;i<=n;i++) tmp+=sum[i];
        ans=max(ans,tmp);
        return;
    }
    for(int i=1;i<=n;i++) {
        if(!vis[i]) {
            vis[i]=true;
            q[now]=i;
            dfs(now+1);
            vis[i]=false;
        }
    }
}
void solve1(){
    dfs(1);
    cout<<ans;
}
void solve4(){cout<<0;}
void solve7(){
    if(n<=5) cout<<n*(n-1)/2;
    else cout<<n*6-21;
}
void solve8(){
    if(n<=6) cout<<n*(n-1)/2;
    else cout<<n*7-28;
}

signed main(){
    freopen("magic.in","r",stdin);
    freopen("magic.out","w",stdout);
    cin>>n;
    bool flag4=true,flag7=true,flag8=true;
    for(int i=1;i<=n;i++){
        cin>>l[i]>>r[i]>>c[i];
        if(max(i-l[i],r[i]-i)>0) flag4=false;
        if(l[i]!=max(i-6,1)||r[i]!=min(i+6,n)||c[i]!=1) flag7=false;
        if(l[i]!=max(i-7,1)||r[i]!=min(i+7,n)||c[i]!=1) flag8=false;
    }
    if(flag4) solve4();
    else if(flag7) solve7();
    else if(flag8) solve8();
    else {solve1();}
    return 0;
}