#include "bits/stdc++.h"
#ifdef DEBUG
#include "PrettyDebug.hpp"
#else
#define debug(...) [](auto...){}(__VA_ARGS__)
#define debuga(...) [](auto...){}(__VA_ARGS__)
#endif
#define For(i,a,b) for(int i=a;i<=b;i++)
#define Rev(i,a,b) for(int i=a;i>=b;i--)
#define Fin(file) freopen(file,"r",stdin)
#define Fout(file) freopen(file,"w",stdout)
#define assume(expr) ((!!(expr))||(exit((fprintf(stderr,"Assumption Failed: %s on Line %d\n",#expr,__LINE__),-1)),false))
#define range basic_string_view
using namespace std; typedef long long ll; using pii = pair<int,ll>;
int a[10004];
signed main(){
    atexit([](){cerr<<"Time = "<<clock()<<" ms"<<endl;});
    int n,m; cin>>n>>m; vector<vector<int>> to(n+1); For(i,1,m) { int x,y; cin>>x>>y; to[x].push_back(y); to[y].push_back(x); }
    function<pii(int)> solve=[&](int S){
        vector<int> dis(n+1,1e9); vector<ll> cnt(n+1); dis[S]=0; cnt[S]=1; queue<int> q; q.push(S); int mn=1e9; ll res=0;
        while(q.size()){
            int u=q.front(); q.pop();
            for(int v:to[u]){
                if(dis[v]==1e9) dis[v]=dis[u]+1,cnt[v]=cnt[u],q.push(v);
                else if(dis[v]>=dis[u]){
                    if(mn==dis[u]+dis[v]+1) res+=1ll*cnt[u]*cnt[v];
                    else if(mn>dis[u]+dis[v]+1) mn=dis[u]+dis[v]+1,res=1ll*cnt[u]*cnt[v];
                    if(dis[v]==dis[u]+1) cnt[v]+=cnt[u];
                }
            }
        }
        if(mn&1) res/=2;; return pii(mn,res);
    };
    int mn=1e9; ll cnt=0;
    For(i,1,n){
        auto [x,y]=solve(i);
        debug(i,x,y);
        if(x<mn) mn=x,cnt=y; else if(x==mn) cnt+=y;
    }
    debug(mn,cnt);
    cout<<cnt/mn<<'\n';
    return 0;
}

