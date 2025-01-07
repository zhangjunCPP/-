#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
const int N=5e6+10;
struct node{
	int v,nex;
}a[N];
int first[N],cnt;
void add(int u,int v){
	a[++cnt]={v,first[u]};
	first[u]=cnt;
}
int qpow(int x,int y){
	int ans=1;
	while(y){
		if(y&1) ans=ans*x%mod;
		y>>=1;
		x=x*x%mod;
	}
	return ans;
}
int dep[N];
void dfs(int u,int fa){
	dep[u]=dep[fa]+1;
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(v==fa) continue;
		dfs(v,u);
	}
}
int dep1[N],dep2[N];
vector<int> d[N];
bool vis[N];
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int n;
	cin>>n;
	for(int i=1;i<n;i++) {
		int u,v;
		cin>>u>>v;
		add(u,v);
		add(v,u);
	}
	dep[0]=-1;
	dfs(1,0);
	int s=0,t=0;
	for(int i=1;i<=n;i++) if(dep[i]>dep[s]) s=i;
	dfs(s,0);
	for(int i=1;i<=n;i++) if(dep[i]>dep[t]) t=i;
	for(int i=1;i<=n;i++){
		dep1[i]=dep[i]; 
		if(i!=s&&i!=t) d[dep[i]].push_back(i);
	}
	dfs(t,0);
	for(int i=1;i<=n;i++){
		dep2[i]=dep[i];
		if(i!=s&&i!=t&&dep1[i]!=dep2[i]) d[dep[i]].push_back(i);
	}
	int len=dep[s];
	int last=n-2;
	int ans=0;
	for(int i=len;i>=1;i--) {
		int siz=d[i].size();
		int num=0;
		bool flag=true;
		for(auto now:d[i]) {
			if(!vis[now]) vis[now]=true,num++,last--;
			if(dep1[now]==dep2[now]) flag=false;
		}
		ans=(ans+(qpow(2,num)-((num==siz)&&flag)+mod)%mod*qpow(2,last)%mod*i%mod)%mod;
		flag=true;
		for(auto now:d[i]) {
			if(dep1[now]+dep2[now]>=2*i){
				flag=false;
				break;
			}
		}
		if(!flag) break;
	}
	ans=(ans+qpow(2,n-2)*len%mod)%mod;
	cout<<ans*2%mod;
}
