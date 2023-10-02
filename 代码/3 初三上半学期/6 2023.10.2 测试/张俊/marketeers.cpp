#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
const int mod=998244353;
int n;
vector<int> s[N];
vector<int> tmp;
map<int,bool> vis;
string ans;
void dfs1(int now){
    if(now>n){
        if(tmp.size()!=n) return;
        string s;
        for(int i=0;i<n;i++){
            int sum=0;
            for(int j=i+1;j<n;j++)if(tmp[i]>tmp[j]) sum++;
            s+=sum-'0';
        }
        ans=max(ans,s);
        return;
    }
    for(int i:s[now]){
        if(vis[i]==false){
            vis[i]=true;
            tmp.push_back(i);
            dfs1(now+1);
            tmp.pop_back();
            vis[i]=false;
        }
    }
}
int ans2;
void dfs2(int now){
    if(now>n){
        string s;
        for(int i=0;i<n;i++){
            int sum=0;
            for(int j=i+1;j<n;j++)if(tmp[i]>tmp[j]) sum++;
            s+=sum-'0';
        }
        if(s==ans)ans2++;
        return;
    }
    for(int i:s[now]){
        if(vis[i]==false){
            vis[i]=true;
            tmp.push_back(i);
            dfs2(now+1);
            tmp.pop_back();
            vis[i]=false;
        }
    }
}
signed main(){
    freopen("marketeers.in","r",stdin);
    freopen("marketeers.out","w",stdout);
    cin>>n;
    for(int i=1;i<=n;i++){
        int k;
        cin>>k;
        for(int j=1;j<=k;j++) {
            int x;
            cin>>x;
            s[i].push_back(x);
        }
    }
    dfs1(1);
    dfs2(1);
    cout<<ans2;
}