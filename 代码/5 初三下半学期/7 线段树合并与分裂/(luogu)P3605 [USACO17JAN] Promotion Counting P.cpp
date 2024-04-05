#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
struct node{
    int v,nex;
}a[N];
int first[N],cnt;
void add(int u,int v){
    a[++cnt]={v,first[u]};
    first[u]=cnt;
}
int n;
int lowbit(int x){return x&(-x);}
int tree[N];
void update(int x,int val){for(int i=x;i<=n;i+=lowbit(i))tree[i]+=val;}
int query(int x){
    int sum=0;
    for(int i=x;i;i-=lowbit(i))sum+=tree[i];
    return sum;
}
int p[N],tmp_p[N];
int ans[N];
void dfs(int u){
    ans[u]-=query(n)-query(p[u]);
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        dfs(v);
    }
    ans[u]+=query(n)-query(p[u]);
    update(p[u],1);
}
signed main(){
    cin>>n;
    for(int i=1;i<=n;i++)cin>>p[i],tmp_p[i]=p[i];
    sort(tmp_p+1,tmp_p+n+1);
    for(int i=1;i<=n;i++)p[i]=lower_bound(tmp_p+1,tmp_p+n+1,p[i])-tmp_p;
    for(int i=2;i<=n;i++){
        int x;
        cin>>x;
        add(x,i);
    }
    dfs(1);
    for(int i=1;i<=n;i++)cout<<ans[i]<<"\n";
}