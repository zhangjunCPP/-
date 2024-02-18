#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
struct node{
    int v,nex;
}a[N];
int first[N],cnt;
void add(int u,int v){
    a[++cnt]={v,first[u]};
    first[u]=cnt;
}
struct node2{int u,v,w;}G[N];
bool cmp(const node2&x,const node2&y){return x.w<y.w;}
int fa[N];
int find(int x){
    if(fa[x]!=x)fa[x]=find(fa[x]);
    return fa[x];
}
int val[N];
int dep[N];
int fa2[N][20];
void dfs(int u,int dad){
    dep[u]=dep[dad]+1;
    fa2[u][0]=dad;
    for(int i=1;i<20;i++)fa2[u][i]=fa2[fa2[u][i-1]][i-1];
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(v==dad)continue;
        dfs(v,u);
    }
}
int lca(int x,int y){
    if(dep[x]<dep[y])swap(x,y);
    for(int i=19;i>=0;i--)if(dep[fa2[x][i]]>=dep[y])x=fa2[x][i];
    if(x==y)return x;
    for(int i=19;i>=0;i--)if(fa2[x][i]!=fa2[y][i])x=fa2[x][i],y=fa2[y][i];
    return fa2[x][0];
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=(n<<1);i++)fa[i]=i;
    for(int i=1;i<=m;i++)cin>>G[i].u>>G[i].v>>G[i].w;
    sort(G+1,G+m+1,cmp);
    int tot=n;
    for(int i=1;i<=m;i++){
        int u=G[i].u,v=G[i].v;
        int fu=find(u),fv=find(v);
        if(fu!=fv) {
            val[++tot]=G[i].w;
            fa[fu]=fa[fv]=tot;
            add(tot,fu), add(fu,tot);
            add(tot,fv), add(fv,tot);
            if(tot==2*n-1)break;
        }
    }
    for(int i=tot;i>=1;i--)if(!dep[i])dfs(i,0);
    int q;
    cin>>q;
    while(q--){
        int x,y;
        cin>>x>>y;
        if(find(x)!=find(y))cout<<"impossible\n";
        else cout<<val[lca(x,y)]<<"\n";
    }
}