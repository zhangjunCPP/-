#include <bits/stdc++.h>
#define int long long
using namespace std;
const int INF=1e16;
const int N=4e5+10;
int w[N];
int fa[N][20];
int sum[N][20];
void add(int u,int v){ //u->v
    if(w[u]>=w[v])fa[v][0]=u;
    else {
        for(int i=19;i>=0;i--){
            if(w[fa[u][i]]<w[v]) u=fa[u][i];
        }
        fa[v][0]=fa[u][0];
    }
    sum[v][0]=w[fa[v][0]];
    for(int i=1;i<=19;i++){
        fa[v][i]=fa[fa[v][i-1]][i-1];
        if(fa[v][i]!=0) sum[v][i]=sum[v][i-1]+sum[fa[v][i-1]][i-1];
        else sum[v][i]=INF;
    }
}
int query(int u,int x){
    if(w[u]>x) return 0;
    x-=w[u];
    int ans=1;
    for(int i=19;i>=0;i--){
        if(sum[u][i]<=x){
            x-=sum[u][i];
            u=fa[u][i];
            ans+=1<<i;
        }
    }
    return ans;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    w[0]=INF;
    memset(sum[1],0x3f,sizeof sum[1]);
    int cnt=1;
    w[1]=0;

    int last=0;
    int q;
    cin>>q;
    while(q--){
        int opt,r,x;
        cin>>opt>>r>>x;
        r^=last,x^=last;
        if(opt==1){
            w[++cnt]=x;
            add(r,cnt);
        }
        else {
            int ans=query(r,x);
            cout<<ans<<"\n";
            last=ans;
        }
    }
}