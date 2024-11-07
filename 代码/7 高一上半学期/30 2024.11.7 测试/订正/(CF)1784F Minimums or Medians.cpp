#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10,mod=998244353;
int fac[N],inv[N];
int qpow(int x,int y){
	int ans=1;
	while(y){
		if(y&1)ans=ans*x%mod;
		y>>=1;
		x=x*x%mod;
	}
	return ans;
}
void init(){
	fac[0]=inv[0]=1;
	for(int i=1;i<N;i++)fac[i]=fac[i-1]*i%mod;
	inv[N-1]=qpow(fac[N-1],mod-2);
	for(int i=N-2;i;i--)inv[i]=inv[i+1]*(i+1)%mod;
}
int C(int n,int m){return fac[n]*inv[m]%mod*inv[n-m]%mod;}
signed main(){
	init();
	int n,k;
	cin>>n>>k;
	if(n==k){
		cout<<1;
		return 0;
	}
	int ans=1;
	int sum=1;
	for(int p=1,L=0,R=0;p<=k;p++){
		int tmp=min(k-p,n-2*p-1);
		int l=max(0ll,k-p-tmp);
		int r=min(p,k-p);
		if(l>r)break;
		/*
		$$
		sum=\sum_{i=L}^R\binom{p-1}{i}\\
		\begin{aligned}
			\sum_{i=L}^R\binom{p}{i}&=\sum_{i=L}^R\binom{p-1}{i}+\binom{p-1}{i-1}\\
			&=sum+\sum_{i=L}^R\binom{p-1}{i-1}\\
			&=sum+\sum_{i=L-1}^{R-1}\binom{p-1}{i}\\
			&=2sum-\binom{p-1}{R}+\binom{p-1}{L-1}
		\end{aligned}
		$$
		*/
		sum=(sum*2%mod+C(p-1,L-1)-C(p-1,R)+mod)%mod;
		while(L>l)sum=(sum+C(p,--L))%mod;
		while(R<r)sum=(sum+C(p,++R))%mod;
		while(L<l)sum=(sum-C(p,L++)+mod)%mod;
		while(R>r)sum=(sum-C(p,R--)+mod)%mod;
		ans=(ans+sum)%mod;
	}
	for(int p=(n+1)/2;p<=k;p++)ans=(ans+C(n-p-1,k-p))%mod;
	cout<<ans;
}