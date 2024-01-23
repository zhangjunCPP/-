#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e7+10;
int prime[N],cnt;
bool vis[N];
int f[N],g[N];
void get_sum(){
    f[1]=1;
    for(int i=2;i<N;i++){
        if(!vis[i]){
            prime[++cnt]=i;
            f[i]=i+1,g[i]=i+1;
        }
        for(int j=1;j<=cnt&&i*prime[j]<N;j++){
            vis[i*prime[j]]=true;
            if(i%prime[j]==0){
                g[i*prime[j]]=g[i]*prime[j]+1;
                f[i*prime[j]]=f[i]/g[i]*g[i*prime[j]];
                break;
            }
            f[i*prime[j]]=f[i]*f[prime[j]];
            g[i*prime[j]]=prime[j]+1;
        }
    }
    for(int i=3;i<N;i++)f[i]+=f[i-1];
}
signed main(){
    get_sum();
    int n;
    while(cin>>n){
        if(n==0) break;
        cout<<f[n]<<"\n";
    }
}