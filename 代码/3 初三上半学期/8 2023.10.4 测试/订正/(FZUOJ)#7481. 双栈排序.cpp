#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e6+10;
int mod;
int qpow(int x,int y){
	int ans=1;
	while(y){
		if(y&1) ans=ans*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return ans%mod;
} 
int f[N];
int jc[N];
int inv[N];
signed main(){
	int T;
	cin>>T;
	while(T--){
		int n;
		cin>>n>>mod;
		jc[0]=1;
		jc[1]=1;
		f[0]=1;
		f[1]=1;
		if(n==1) {cout<<0<<"\n";continue;}
		inv[1]=1;
		for(int i=2;i<=n;i++) inv[i]=(mod-mod/i*inv[mod%i]%mod+mod)%mod;
		for(int i=2;i<=n;i++) {
			f[i]=((6*i-3)*f[i-1]%mod-(i-2)*f[i-2]%mod+mod)%mod;
			f[i]=f[i]*inv[i+1]%mod;
			jc[i]=jc[i-1]*i%mod;
		}
		cout<<(jc[n]-f[n-1]*2%mod+mod)%mod<<"\n";
	}
	return 0;
}
