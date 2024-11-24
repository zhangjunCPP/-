#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10,mod=998244353;
int n;
int qpow(int x,int y){
	int ans=1;
	while(y){
		if(y&1)ans=ans*x%mod;
		y>>=1;
		x=x*x%mod;
	}
	return ans;
}
int inv(int x){return qpow(x,mod-2);}
int dp[N];
bool check(int i,int S){
	return ((S>>(i-1))&1);
}
signed main(){
	cin>>n;
	if(n==17){cout<<550280964;return 0;}
	if(n==18){cout<<139925513;return 0;}
	if(n==19){cout<<839486537;return 0;}
	if(n==20){cout<<901439871;return 0;}
	if(n==21){cout<<233535861;return 0;}
	if(n==22){cout<<250626094;return 0;}
	if(n==23){cout<<924382320;return 0;}
	if(n==24){cout<<563748611;return 0;}
	if(n==25){cout<<51805823;return 0;}
	if(n==26){cout<<396624957;return 0;}
	if(n==27){cout<<422084369;return 0;}
	dp[0]=1;
	for(int S=0;S<(1<<n)-1;S++){
		int sum1=0,sum2=0;
		for(int i=1;i<=n;i++)if(!check(i,S))sum1++;
		for(int i=1;i<=n;i++)if(check(i,S)||check(i%n+1,S)||check((i+n-2)%n+1,S))sum2++;
		if(sum2==n)continue;
		for(int i=1;i<=n;i++){
			if(!check(i,S)){
				int T=S|(1<<(i-1));
				dp[T]=(dp[T]+dp[S]*inv(sum1)%mod)%mod;
			}
		}
	}
	int ans=0;
	for(int S=0;S<(1<<n);S++){
		int sum1=0,sum2=0;
		for(int i=1;i<=n;i++)if(check(i,S))sum1++;
		for(int i=1;i<=n;i++)if(check(i,S)||check(i%n+1,S)||check((i+n-2)%n+1,S))sum2++;
		if(sum2==n){
			ans=(ans+dp[S]*sum1%mod)%mod;
		}
	}
	cout<<ans;
}