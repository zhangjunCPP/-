#include <bits/stdc++.h>
using namespace std;
const int N=1e4+10;
struct node{int v,nex;}a[N];
int first[N],cnt;
void add(int u,int v){
    a[++cnt]={v,first[u]};
    first[u]=cnt;
}
int dfn[N],low[N];
stack<int> s;
int scc[N],tot;
bool vis[N];
void tarjan(int u){
    dfn[u]=low[u]=++tot;
    s.push(u);
    vis[u]=true;
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(!dfn[v]){
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else if(vis[v])low[u]=min(low[u],dfn[v]);
    }
    if(low[u]==dfn[u]){
        ++tot;
        while (s.top()!=u){
            scc[s.top()]=tot;
            vis[s.top()]=false;
            s.pop();
        }
        scc[s.top()]=tot;
        vis[s.top()]=false;
        s.pop();
    }
}
//1~n:true n+1~2n:false
void init(){
    cnt=tot=0;
    memset(first,0,sizeof first);
    memset(scc,0,sizeof scc);
    memset(dfn,0,sizeof dfn);
    memset(vis,false,sizeof vis);
    while(!s.empty())s.pop();
}
int calc(string tmp){
    int sum=0;
    for(int i=1;i<tmp.size();i++)sum=sum*10+tmp[i]-'0';
    return sum;
}
void solve(){
    init();
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        string s1,s2;
        cin>>s1>>s2;
        int u,vu,v,vv;
        u=calc(s1),v=calc(s2);
        if(s1[0]=='m')vu=1;
        else vu=0;
        if(s2[0]=='m')vv=1;
        else vv=0;
        add(u+n*vu,v+n*(!vv));
        add(v+n*vv,u+n*(!vu));
    }
    for(int i=1;i<=2*n;i++)if(!dfn[i])tarjan(i);
    for(int i=1;i<=n;i++)if(scc[i]==scc[i+n]){cout<<"BAD\n";return;}
    cout<<"GOOD\n";
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int T;
    cin>>T;
    while(T--)solve();
}