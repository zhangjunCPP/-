#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10,mod=998244353;
int n,val;
int qpow(int x,int y){
	int ans=1;
	while(y){
		if(y&1)ans=ans*x%mod;
		y>>=1;
		x=x*x%mod;
	}
	return ans;
}
int fac[N],inv[N];
void init(){
	fac[0]=inv[0]=1;
	for(int i=1;i<N;i++)fac[i]=fac[i-1]*i%mod;
	inv[N-1]=qpow(fac[N-1],mod-2);
	for(int i=N-2;i;i--)inv[i]=inv[i+1]*(i+1)%mod;
}
int tot[60];
unordered_map<int,int> dp;
int dfs(int sum,int k,int val){
	if(sum>=50||k==n-tot[0])return fac[n-k-tot[0]]*val%mod;
	int Hash=0;
	for(int i=1;i<=50;i++)Hash=Hash*131+tot[i];
	if(dp.count(Hash))return dp[Hash];
	int ans=0;
	for(int i=min(sum,50ll);i>=1;i--){
		if(tot[i]){
			tot[i]--;
			ans=(ans+dfs(sum+i,k+1,val*(tot[i]+1)%mod))%mod;
			tot[i]++;
		}
	}
	dp[Hash]=ans;
	return ans;
}
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	init();
	cin>>n>>val;
	for(int i=1;i<=n;i++){
		int x;
		cin>>x;
		tot[x]++;
	}
	int ans=dfs(val,0,1)*fac[n]%mod*inv[n-tot[0]]%mod;
	cout<<ans;
}