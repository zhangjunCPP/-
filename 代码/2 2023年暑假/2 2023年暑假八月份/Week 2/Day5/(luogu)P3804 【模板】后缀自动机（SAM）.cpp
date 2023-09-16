#include <bits/stdc++.h>
using namespace std;
const int N=2e6+10;
struct node{
    int ch[26];
    int len,link;
}sam[N];
int last=1,tot=1;//初始节点为1，link[1]=0;虚拟状态为0
long long dp[N];
void add(int c){
    int cur=++tot;
    dp[cur]=1;
    sam[cur].len=sam[last].len+1;
    int p=last;
    while(p&&!sam[p].ch[c]) {
        sam[p].ch[c]=cur;
        p=sam[p].link;
    }
    if(p==0) sam[cur].link=1;
    else{
        int q=sam[p].ch[c];
        if(sam[q].len==sam[p].len+1) sam[cur].link=q;
        else{
            int clone=++tot;
            sam[clone]=sam[q];
            sam[clone].len=sam[p].len+1;
            sam[cur].link=sam[q].link=clone;
            while(p&&sam[p].ch[c]==q){
                sam[p].ch[c]=clone;
                p=sam[p].link;
            }
        }
    }
    last=cur;
}

vector<int> G[N];
long long ans=0;
void dfs(int u){
    for(int v:G[u]){
        dfs(v);
        dp[u]+=dp[v];
    }
    if(dp[u]!=1) ans=max(ans,dp[u]*sam[u].len);
}
signed main(){
    string s;
    cin>>s;
    for(int i=0;i<s.size();i++) add(s[i]-'a');
    for(int i=2;i<=tot;i++) G[sam[i].link].push_back(i);
    dfs(1);
    cout<<ans;
}