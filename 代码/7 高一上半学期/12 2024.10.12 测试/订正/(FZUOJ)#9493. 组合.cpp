#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e3+10;
const int mod=1e9+7;

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
int pw[N];
void init(){
	fac[0]=inv[0]=pw[0]=1;
	for(int i=1;i<N;i++)fac[i]=fac[i-1]*i%mod,pw[i]=pw[i-1]*2%mod;
	inv[N-1]=qpow(fac[N-1],mod-2);
	for(int i=N-2;i;i--)inv[i]=inv[i+1]*(i+1)%mod;
}
int C(int n,int m){return fac[n]*inv[m]%mod*inv[n-m]%mod;}
int sum[N][N];
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	init();
	for(int c=1;c<N;c++)
		for(int i=1;i<N;i++)sum[c][i]=(sum[c][i-1]+pw[c-i]*i%mod*i%mod*(c-i+mod)%mod*C(c,i)%mod)%mod;
	int n,q;
	cin>>n>>q;
	while(q--){
		int a,b,c;
		cin>>a>>b>>c;
		cout<<(sum[c][b]-sum[c][a-1]+mod)%mod<<"\n";
	}
}