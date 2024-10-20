#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e7+10;
const int mod=998244353;
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
signed main(){
	init();
	int l,r;
	cin>>l>>r;
	int sum0=0,sum1=0;
	int ans=0;
	for(int i=1;i<=r;i++){
		sum0=(sum0+(i-(i*i+1)%mod+mod)%mod*fac[i-1]%mod*inv[i]%mod)%mod;
		sum1=(sum1+fac[i]*i%mod*inv[i+1]%mod)%mod;
		if(i>=l)ans=(sum0*fac[i]%mod+sum1*fac[i+1]%mod)%mod^ans;
	}
	cout<<ans;
}