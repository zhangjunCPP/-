#include <bits/stdc++.h>
using namespace std;
const int N=5e6+10;
struct node{
    int v,nex;
}a[N];
int first[N],cnt=1;
void add(int u,int v){
    a[++cnt]={v,first[u]};
    first[u]=cnt;
}
int dfn[N],low[N],tot;
stack<int>s;
int col;
vector<int> ans[N];
void Tarjan(int u,int edge){
    dfn[u]=low[u]=++tot;
    s.push(u);
    int sum=0;
    for(int i=first[u];i;i=a[i].nex){
        sum++;
        int v=a[i].v;
        if(!dfn[v]){
            Tarjan(v,i);
            low[u]=min(low[u],low[v]);
            if(low[v]>=dfn[u]){
                ++col;
                ans[col].push_back(u);
                while(s.top()!=v){
                    ans[col].push_back(s.top());
                    s.pop();
                }
                ans[col].push_back(v);
                s.pop();
            }
        }
        else if(i!=(edge^1))low[u]=min(low[u],dfn[v]);
    }
    if(edge==0&&sum==0)ans[++col].push_back(u);
}
int main(){
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        if(u==v)continue;
        add(u,v);
        add(v,u);
    }
    for(int i=1;i<=n;i++)if(!dfn[i])Tarjan(i,0);
    cout<<col<<"\n";
    for(int i=1;i<=col;i++){
        cout<<ans[i].size()<<" ";
        for(int j:ans[i])cout<<j<<" ";
        cout<<"\n";
    }
}