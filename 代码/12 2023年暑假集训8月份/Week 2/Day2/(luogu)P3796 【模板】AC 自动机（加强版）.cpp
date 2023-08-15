#include <bits/stdc++.h>

using namespace std;
const int N=1e5+10;
int tree[N][30];
int fail[N];
int cnt;
int e[N];
void insert(string s,int id){
    int now=0;
    int SIZE=s.size();
    for(int i=0;i<SIZE;i++){
        if(!tree[now][s[i]-'a']) tree[now][s[i]-'a']=++cnt;
        now=tree[now][s[i]-'a'];
    }
    e[now]=id;
}
queue<int> q;
void build(){
    for(int i=0;i<26;i++) if(tree[0][i]) q.push(tree[0][i]);
    while(!q.empty()){
        int now=q.front();
        q.pop();
        for(int i=0;i<26;i++){
            if(tree[now][i]) {
                fail[tree[now][i]]=tree[fail[now]][i];
                q.push(tree[now][i]);
            }
            else tree[now][i]=tree[fail[now]][i];
        }
    }
}
int ans[N];
void query(string s){
    int SIZE=s.size();
    int now=0;
    for(int i=0;i<SIZE;i++){
        now=tree[now][s[i]-'a'];
        for(int j=now;j;j=fail[j]){
            ans[e[j]]++;
        }
    }
}
string t[N];
void init(){
    memset(e,0, sizeof e);
    memset(ans,0, sizeof ans);
    memset(tree,0, sizeof tree);
    memset(fail,0, sizeof fail);
    cnt=0;
}
int main(){
    int n;
    cin>>n;
    while(n!=0){
        init();
        for(int i=1;i<=n;i++){
            cin>>t[i];
            insert(t[i],i);
        }
        build();
        string s;
        cin>>s;
        query(s);
        int MAX=-1;
        for(int i=1;i<=n;i++) MAX=max(MAX,ans[i]);
        cout<<MAX<<"\n";
        for(int i=1;i<=n;i++) if(ans[i]==MAX) cout<<t[i]<<"\n";
        cin>>n;
    }

}