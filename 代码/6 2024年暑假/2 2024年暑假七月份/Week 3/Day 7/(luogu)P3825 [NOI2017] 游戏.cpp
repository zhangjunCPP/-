#include <bits/stdc++.h>
using namespace std;
const int N=5e6+10;
struct node{
    int v,nex;
}a[N];
int first[N],cnt;
void add(int u,int v){
    a[++cnt]={v,first[u]};
    first[u]=cnt;
}
int dfn[N],low[N],tot;
stack<int> s;
bool vis[N];
int col,scc[N];
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
        ++col;
        while(s.top()!=u){
            scc[s.top()]=col;
            vis[s.top()]=false;
            s.pop();
        }
        scc[u]=col;
        vis[u]=false;
        s.pop();
    }
}
int n,d;
int m;
int mp[N];
void clear(){
    cnt=0;
    tot=0;
    col=0;
    for(int i=1;i<=(n<<1);i++)dfn[i]=first[i]=0;
}
int x[N],y[N];
char h1[N],h2[N];
int tmp[N];
//1~n:取前面的 n+1~2n:取后面的
void check(int S){
    clear();
    for(int i=n;i;i--){
        if(mp[i]==3)tmp[i]=S&1,S>>=1;
        else tmp[i]=mp[i];
    }
    for(int i=1;i<=m;i++){
        if(h1[i]-65==tmp[x[i]])continue;
        int last1=0,last2=0;
        if(last1==tmp[x[i]])last1++;
        if(last2==tmp[y[i]])last2++;
        if(h2[i]-65==tmp[y[i]])add(x[i]+(last1!=h1[i]-65)*n,x[i]+(last1==h1[i]-65)*n);
        else add(x[i]+(last1!=h1[i]-65)*n,y[i]+(last2!=h2[i]-65)*n),add(y[i]+(last2==h2[i]-65)*n,x[i]+(last1==h1[i]-65)*n);
    }

    for(int i=1;i<=(n<<1);i++)if(!dfn[i])tarjan(i);
    for(int i=1;i<=n;i++)if(scc[i]==scc[i+n])return;
    for(int i=1;i<=n;i++){
        int ans=0;
        if(ans==tmp[i])ans++;
        if(scc[i]>scc[i+n]){
            ans++;
            if(ans==tmp[i])ans++;
        }
        cout<<char(ans+65);
    }
    exit(0);
}
int main(){
    cin>>n>>d;
    string S;
    cin>>S;
    for(int i=1;i<=n;i++){
        switch(S[i-1]){
            case 'x':
                mp[i]=3;
                break;
            case 'a':
                mp[i]=0;
                break;
            case 'b':
                mp[i]=1;
                break;
            default:
                mp[i]=2;
        }
    }
    cin>>m;
    for(int i=1;i<=m;i++)cin>>x[i]>>h1[i]>>y[i]>>h2[i];
    for(int i=0;i<(1<<d);i++)check(i);
    puts("-1");
}