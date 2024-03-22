#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
struct node{
    int v,nex;
}a[N];
int first[N],cnt;
int deg[N];
void add(int u,int v){
    a[++cnt]={v,first[u]};
    first[u]=cnt;
    deg[v]++;
}
bool vis[N];
int main(){
    int n;
    cin>>n;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        add(u,v);
        add(v,u);
    }
    queue<int> q;
    for(int i=1;i<=n;i++)if(deg[i]==1)q.push(i);
    for(int i=1;i<=n/2;i++){
        int u=q.front();q.pop();
        int v=q.front();q.pop();
        cout<<"? "<<u<<" "<<v<<endl;
        int x;
        cin>>x;
        if(u==x||v==x){
            cout<<"! "<<x<<endl;
            return 0;
        }
        vis[u]=vis[v]=true;
        for(int j=first[u];j;j=a[j].nex){
            --deg[a[j].v];
            if(!vis[a[j].v]&&deg[a[j].v]==1)q.push(a[j].v);
        }
        for(int j=first[v];j;j=a[j].nex){
            --deg[a[j].v];
            if(!vis[a[j].v]&&deg[a[j].v]==1)q.push(a[j].v);
        }
    }
    for(int i=1;i<=n;i++)if(!vis[i]){cout<<"! "<<i<<endl;}
}