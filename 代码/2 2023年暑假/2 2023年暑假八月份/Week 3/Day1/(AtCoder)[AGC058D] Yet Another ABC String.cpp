#include <bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353;
const int N=3e6+10;
int qpow(int x,int y){
	int ans=1;
	while(y){
		if(y&1) ans=ans*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return ans%mod;
}
int inv[N],jc[N];
void init(){
	jc[0]=inv[0]=1;
	for(int i=1;i<N;i++) jc[i]=jc[i-1]*i%mod;
	for(int i=1;i<N;i++) inv[i]=qpow(jc[i],mod-2)%mod;
}
int C(int x,int y){
	return jc[x]%mod*inv[y]%mod*inv[x-y]%mod;
}
signed main(){
	init();
	int a,b,c;
	cin>>a>>b>>c;
	int ans=0;
	for(int i=0;i<=min({a, b, c});i++){
		int tmp1=C(i+a+b+c-3*i-1,a+b+c-3*i-1)%mod*qpow(2,i)%mod;
		if(i)tmp1=(tmp1+C(i-1+a+b+c-3*i,a+b+c-3*i)%mod*qpow(2,i-1)%mod*3%mod)%mod;
		int tmp2=jc[a+b+c-3*i]%mod*inv[a-i]%mod*inv[b-i]%mod*inv[c-i]%mod;
		ans=(ans+(i&1?-1:1)*(tmp1%mod*tmp2%mod)%mod+mod)%mod;
	}
	cout<<ans%mod;
}