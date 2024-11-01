#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e6+10,mod=1e9+7;
int a[N];
int qpow(int x,int y){
	int ans=1;
	while(y){
		if(y&1)ans=ans*x%mod;
		y>>=1;
		x=x*x%mod;
	}
	return ans;
}
const int inv2=qpow(2,mod-2),inv6=qpow(6,mod-2);
int C2(int x){return x*(x-1)%mod*inv2%mod;}
int C3(int x){return x*(x-1)%mod*(x-2)%mod*inv6%mod;}
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int n;
	cin>>n;
	int sum=0;
	for(int i=1;i<=n;i++)cin>>a[i],a[i+n]=a[i],sum=(sum+a[i])%mod;
	a[0]=a[n];
	int ans=C3(sum);
	for(int i=1;i<=n;i++)ans=(ans-C3(a[i])+mod)%mod;
	for(int i=1;i<=n;i++){
		ans=(ans+C2(a[i]+(n==3?2:0))%mod)%mod;
		ans=(ans+a[i]*a[i+n/2]*2%mod)%mod;
		ans=(ans+a[i]*a[i-1]%mod)%mod;
	}
	cout<<(ans-(n==3?2:0)+mod)%mod;
}