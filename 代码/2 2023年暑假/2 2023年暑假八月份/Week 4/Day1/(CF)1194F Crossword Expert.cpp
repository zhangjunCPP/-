#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+10;
const int mod=1e9+7;
int jc[N],inv[N];
int qpow(int x,int y){
	int ans=1;
	while(y){
		if(y&1) ans=ans*x%mod;
		y>>=1;
		x=x*x%mod;
	}
	return ans%mod;
}
int C(int n,int m){return jc[n]*inv[m]%mod*inv[n-m]%mod;}
int t[N];
int dp[N];
signed main(){
	int inv2=qpow(2,mod-2);
	jc[0]=inv[0]=1;
	for(int i=1;i<N;i++) jc[i]=(jc[i-1]*i)%mod;
	for(int i=1;i<N;i++) inv[i]=qpow(jc[i],mod-2)%mod;
	int n,T;
	cin>>n>>T;
	for(int i=1;i<=n;i++) cin>>t[i];
	for(int i=1;i<=n;i++) t[i]=t[i-1]+t[i];
	dp[0]=1;

	int sum=1;
	int now=0;
	for(int i=1;i<=n;i++){
		if(t[i]>T) break;
		sum=(sum*2-C(i-1,now)%mod+mod)%mod;
		int MAX=min(T-t[i],i);
		while(now<MAX){
			++now;
			sum=(sum+C(i,now)%mod)%mod;
		}
		while(now>MAX){
			sum=(sum-C(i,now)%mod+mod)%mod;
			--now;
		}
		dp[i]=sum*qpow(inv2,i)%mod;
	}
	int ans=0;
	for(int i=1;i<=n;i++)ans=(ans+dp[i])%mod;
	cout<<ans;
}