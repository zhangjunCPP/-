#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e6+10,mod=1e9+7;
int qpow(int x,int y){
	int ans=1;
	while(y){
		if(y&1)ans=ans*x%mod;
		y>>=1;
		x=x*x%mod;
	}
	return ans%mod;
}
int fac[N],inv[N];
void init(){
	fac[0]=1;
	for(int i=1;i<N;i++)fac[i]=fac[i-1]*i%mod;
	inv[0]=1;
	inv[N-1]=qpow(fac[N-1],mod-2);
	for(int i=N-2;i>=1;i--)inv[i]=inv[i+1]*(i+1)%mod;
}
int C(int n,int m){if(n<0||m<0||m>n)return 0;return fac[n]*inv[m]%mod*inv[n-m]%mod;}
signed main(){
	init();
	int n,m;
	cin>>n>>m;
	int x=n+m+1,y=n;
	int ans=C(x+y,x);
	while(x>=0&&y>=0){
		swap(x,y);x-=1,y+=1;
		ans=(ans-C(x+y,x)+mod)%mod;
		swap(x,y);x-=(-m-2);y+=(-m-2);
		ans=(ans+C(x+y,x))%mod;
	}
	x=n+m+1,y=n;
	while(x>=0&&y>=0){
		swap(x,y);x-=(-m-2);y+=(-m-2);
		ans=(ans-C(x+y,x)+mod)%mod;
		swap(x,y);x-=1,y+=1;
		ans=(ans+C(x+y,x))%mod;
	}
	cout<<ans%mod;
}