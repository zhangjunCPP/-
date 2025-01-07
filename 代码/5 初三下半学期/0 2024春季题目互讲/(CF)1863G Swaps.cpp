#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10,mod=1e9+7;
int a[N];
int deg[N];
int ans=1;
bool vis[N];
bool in[N];
bool flag[N];
int sta[N],top;
void dfs(int u){
	if(vis[u])return;
	vis[u]=true;
	sta[++top]=u,in[u]=true;
	int v=a[u];
	if(!in[v])dfs(v);
	else{
		int tmp1=1,tmp2=0;
		for(int i=top;i;i--){
			flag[sta[i]]=true;
			tmp1=tmp1*(deg[sta[i]]+1)%mod;
			tmp2=(tmp2+deg[sta[i]])%mod;
			if(sta[i]==v)break;
		}
		ans=ans*(tmp1-tmp2+mod)%mod;
	}
	top--,in[u]=false;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr),cout.tie(nullptr);
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i],deg[a[i]]++;
	for(int i=1;i<=n;i++)dfs(i);
	for(int i=1;i<=n;i++)if(!flag[i])ans=ans*(deg[i]+1)%mod;
	cout<<ans;
}