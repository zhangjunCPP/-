#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
const int mod=998244353;
int fac[N];
void init() {
	int p=1e18;
	p%=mod;
	fac[0]=1;
	for(int i=1;i<N;i++)fac[i]=fac[i-1]*p%mod;
}
vector<int> G[N];
int sg[3][N];
int dp[3][N];
signed main(){
	init();
	int n;
	cin>>n;
	for(int opt=0;opt<3;opt++){
		for(int i=0;i<=n;i++)G[i].clear();
		int m;
		cin>>m;
		for(int i=1;i<=m;i++){
			int u,v;
			cin>>u>>v;
			if(u>v)swap(u,v);
			G[u].push_back(v);
		}
		for(int i=n;i;i--){
			map<int,bool> mp;
			for(int j:G[i])mp[sg[opt][j]]=true;
			while(mp.count(sg[opt][i]))sg[opt][i]++;
		}
		for(int i=1;i<=n;i++)dp[opt][sg[opt][i]]=(dp[opt][sg[opt][i]]%mod+fac[i]%mod)%mod;
	}
	int ans=0;
	for(int i=0;i<500;i++)for(int j=0;j<500;j++)ans=(ans+(dp[0][i]*dp[1][j])%mod*dp[2][i^j]%mod)%mod;
	cout<<ans<<"\n";
}