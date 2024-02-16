#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
const int N=1e5+10;
struct node{int v,nex;}a[N];
int first[N],cnt;
void add(int u,int v) {
    a[++cnt]={v,first[u]};
    first[u]=cnt;
}
int dfn[N],low[N],tot;
int root;
int cut[N];
void Tarjan(int u,int fa) {
    low[u]=dfn[u]=++tot;
    int sum=0;
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(!dfn[v]){
            sum++;
            Tarjan(v,u);
            low[u]=min(low[u],low[v]);
            if(u==root&&sum>1||u!=root&&low[v]>=dfn[u])cut[u]=1;
        }
        if(v!=fa)low[u]=min(low[u],dfn[v]);
    }
}
void init(){
    tot=cnt=0;
    memset(first,0,sizeof first);
    memset(cut,0,sizeof cut);
    memset(low,0,sizeof low);
    memset(dfn,0,sizeof dfn);
}
signed main(){
    int n;
    cin>>n;
    while(n!=0){
        init();
        int k,y;
        cin>>k;
        y=k;
        char ch;
        while(k!=0){
            ch=getchar();
            if(ch!='\n'){
                cin>>k;
                add(k,y);
                add(y,k);
            }
            else {
                cin>>k;
                y=k;
            }
        }
        for(int i=1;i<=n;i++){
            if(!dfn[i]){
                root=i;
                Tarjan(i,i);
            }
        }
        int ans=0;
        for(int i=1;i<=n;i++)if(cut[i]==1)ans++;
        cout<<ans<<"\n";
        cin>>n;
    }
}