#include<bits/stdc++.h>
using namespace std;
const int N=5e6+10;
int d[N];
vector<int> G[N];
void solve(){
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++) d[i]=0;
    for(int i=1;i<=m;i++) {
        int u,v;
        cin>>u>>v;
        d[u]++;
        d[v]++;
        if(d[u]<=2) G[u].push_back(v);
        if(d[v]<=2) G[v].push_back(u);
    }
    int ans=0;
    for(int i=1;i<=n;i++) {
        if(d[i]==2){
            int v1=G[i][0];
            int v2=G[i][1];
            if(d[v1]==2&&d[v2]==2){
                int tmp1=G[v1][0];
                int tmp2=G[v1][1];
                if(tmp1==v2||tmp2==v2) {
                    ans=max(ans,3);
                    break;
                }
            }
        }
    }
    for(int i=1;i<=n;i++) ans=max(ans,d[i]);
    cout<<ans<<"\n";
}
int main(){
    freopen("match.in","r",stdin);
    freopen("match.out","w",stdout);
    int T;
    cin>>T;
    while(T--) solve();
}