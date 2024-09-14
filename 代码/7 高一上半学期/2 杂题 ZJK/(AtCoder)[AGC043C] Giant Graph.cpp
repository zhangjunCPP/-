#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e5+10;
const int mod=998244353;
const int p=(long long)(1e18)%mod;
int fac[N];
vector<int>G[N];
int dp[3][N];
int SG[3][N];
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int n;
	cin>>n;
	fac[0]=1;
	for(int i=1;i<=n*3;i++)fac[i]=(fac[i-1]*p)%mod;
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
			for(int j:G[i])mp[SG[opt][j]]=true;
			while(mp.count(SG[opt][i]))SG[opt][i]++;
		}
		for(int i=1;i<=n;i++)dp[opt][SG[opt][i]]=(dp[opt][SG[opt][i]]%mod+fac[i]%mod)%mod;
	}
	int ans=0;
	for(int i=0;i<500;i++)
		for(int j=0;j<500;j++)
			ans=(ans+(dp[0][i]*dp[1][j])%mod*dp[2][i^j]%mod)%mod;
	cout<<ans<<"\n";
}