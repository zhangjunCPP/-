#include <bits/stdc++.h>
using namespace std;
const int N=2e5+10;
struct node{
    int v,nex;
}a[N*2];
int first[N],cnt;
int deg[N];
void add(int u,int v){
    a[++cnt]={v,first[u]};
    first[u]=cnt;
    deg[v]++;
}
int n,m;
vector<pair<int,int> > G;
int top[N];
bool top_sort(){
    queue<int> q;
    for(int i=1;i<=n;i++)if(!deg[i])q.push(i);
    int tot=0;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        top[u]=++tot;
        for(int i=first[u];i;i=a[i].nex){
            int v=a[i].v;
            deg[v]--;
            if(!deg[v])q.push(v);
        }
    }
    if(tot<n)return false;
    return true;
}
void init(){
    memset(first,0,sizeof first);
    memset(deg,0,sizeof deg);
    G.clear();
    cnt=0;
}
void solve(){
    init();
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int t,u,v;
        cin>>t>>u>>v;
        if(t==0)G.push_back({u,v});
        else add(u,v);
    }
    if(!top_sort())cout<<"NO\n";
    else {
        cout<<"YES\n";
        for(int i=1;i<=n;i++)for(int j=first[i];j;j=a[j].nex)cout<<i<<" "<<a[j].v<<"\n";
        for(auto i:G){
            if(top[i.first]>top[i.second]) swap(i.first,i.second);
            cout<<i.first<<" "<<i.second<<"\n";
        }
    }
}
int main(){
    int T;
    cin>>T;
    while(T--)solve();
    return 0;
}