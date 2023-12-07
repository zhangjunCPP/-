/*
首先，考虑 $m=0$ 的情况
那么，我们最后每个点会组成一个树。
很明显的，我们可以维护一个待选答案集合 $ans$
每次从 $ans$ 中随机选取两个点，询问它们之间的路径，然后将起点保留，终点删去。
最后剩下的唯一一个点就是答案。
那么，$m>0$ 怎么做？
我们依然考虑采用上面的方法。
我们先将粉色的边缩点，找出强连通分量。
然后我们取出强连通分量中的1个点加入 $ans$，然后按照上面的方法做。
但这样就有个问题：我们不能因为强连通分量中的一个点被删就认为这个强连通分量被删。
我们考虑有哪些点需要额外加入 $ans$ 集合中
我们可以这样做：
把每个强连通分量删掉一些边使之成为一个DAG，把度数为0的点加入 $ans$ 集合，询问完之后把终点以及终点连出去的所有边都删掉，再将度数为0的点加入 $ans$。
考虑是否正确：对于从 $ans$ 删去的那些点中，一定能从答案走绿色边走到。对于没有加入到 $ans$ 的点，也就是剩下的DAG中的点，想想它们为什么没有加入到 $ans$ 中，也就是它们的入度此时仍然大于0，就是因为答案（或答案所在的强连通分量中的一个点）与它有一条粉边。那所以这些点就一定能从答案走粉色边走到
那么，这道题就做完了。
*/
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
struct node{
    int v,nex;
}a[N];
int first[N],cnt;
void add(int u,int v) {
    a[++cnt]={v,first[u]};
    first[u]=cnt;
}
vector<int> G[N];
int d[N];
bool vis1[N],vis2[N];
void dfs(int u){
    vis1[u]=true;
    vis2[u]=true;
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(!vis2[v]) {
            d[v]++;
            G[u].push_back(v);
        }
        if(!vis1[v]) dfs(v);
    }
    vis2[u]=false;
}
int query(int u,int v) {
    cout<<"? "<<u<<" "<<v<<endl;
    int ans;
    cin>>ans;
    return ans;
}
int main(){
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=m;i++) {
        int u,v;
        cin>>u>>v;
        add(u,v);
    }
    for(int i=1;i<=n;i++) if(!vis1[i]) dfs(i);
    vector<int> ans;
    for(int i=1;i<=n;i++) if(d[i]==0) ans.push_back(i);
    while(ans.size()>1){
        int u=ans.back();ans.pop_back();
        int v=ans.back();ans.pop_back();
        if(!query(u,v)) swap(u,v);
        ans.push_back(u);
        for(int i:G[v]) {
            d[i]--;
            if(d[i]==0) ans.push_back(i);
        }
    }
    cout<<"! "<<ans.back()<<endl;
    return 0;
}