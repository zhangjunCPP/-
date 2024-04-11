#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int k,n,m;
int num;
bool vis[N],vis2[N];
int leaf[N];
int ans;
int a[N];
int tmp;
int val[N];
void dfs(int kk){
    if(kk>tmp){

        for(int i=0;i<=num;i++)val[i]=0;
        for(int i=1;i<=tmp;i++){
            int tmp_p=leaf[a[i]];
            val[tmp_p]++;
            while(tmp_p){
                tmp_p=(tmp_p-1)/k;
                val[tmp_p]++;
            }
            for(int j=0;j<leaf[1];j++){
                int Min=0x3f3f3f3f,Max=-1;
                for(int l=j*k+1;l<=j*k+k;l++){
                    Min=min(Min,val[l]),Max=max(Max,val[l]);
                }
                if(Max-Min>=2)return;
            }
        }
        ans++;
        return;
    }
    if(vis[kk])dfs(kk+1);
    else{  
        for(int i=1;i<=tmp;i++){
            if(!vis2[i]){
                vis2[i]=true;
                a[kk]=i;
                dfs(kk+1);
                vis2[i]=false;
            }
        }
    }
}
void solve(){
    ans=0;
    cin>>k>>n>>m;
    num=0;
    for(int i=0;i<=n;i++)num+=pow(k,i);
    tmp=pow(k,n);
    for(int i=1;i<=tmp;i++)leaf[i]=num-tmp+i-1;
    for(int i=1;i<=tmp;i++)vis[i]=vis2[i]=false;
    for(int i=1;i<=m;i++){
        int t,x;
        cin>>t>>x;
        a[t]=x;
        vis[t]=true;
        vis2[x]=true;
    }
    dfs(1);
    cout<<ans<<"\n";
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr),cout.tie(nullptr);
    int T;
    cin>>T;
    while(T--)solve();
}