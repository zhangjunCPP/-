#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e7+10;
const int mod=998244353;
int qpow(int x,int y){
	int ans=1;
	while(y){
		if(y&1) ans=(ans*x)%mod;
		x=(x*x)%mod;
		y>>=1;
	}
	return ans%mod;
}
bool cmp(const int &x,const int &y){
	return x>y;
}
int a[N];
int sum[N];
signed main() {
	int n;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++) sum[i]=sum[i-1]+a[i];
	int inv=qpow(n,mod-2);
	for(int k=1;k<=n;k++){
		int ans=0;
		for(int i=k,j=1;i<n;i+=k,j++){
			ans=(ans+j*(sum[min(n,i+k)]-sum[i]+mod)%mod)%mod;
		}
		cout<<ans*inv%mod<<"\n";
	}
}