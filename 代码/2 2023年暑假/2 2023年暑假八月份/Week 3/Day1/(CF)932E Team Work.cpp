#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e3+5;
const int mod=1e9+7;
int qpow(int x,int y){
	int ans=1;
	while(y){
		if(y&1) ans=ans*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return ans%mod;
}
int S[N][N];
int pw[N];
void init(){
	S[0][0]=1;
	for(int i=1;i<N;i++){
		for(int j=1;j<=i;j++){
			S[i][j]=(S[i-1][j-1]%mod+j*S[i-1][j]%mod)%mod;
		}
	}
}
signed main(){
	init();
	int n,k;
	cin>>n>>k;
	int ans=0;
	for(int i=1;i<=min(n,k);i++) {
		int tmp= S[k][i]* qpow(2,n-i)%mod;
		for(int j=n-i+1;j<=n;j++) tmp=tmp*j%mod;
		ans=(ans+tmp)%mod;
	}
	cout<<ans%mod;
}