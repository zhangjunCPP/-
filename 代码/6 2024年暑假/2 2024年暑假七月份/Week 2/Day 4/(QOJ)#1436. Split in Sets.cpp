#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
const int mod=1e9+7;
int qpow(int x,int y) {
	int ans=1;
	while(y) {
		if(y&1)ans=ans*x%mod;
		y>>=1;
		x=x*x%mod;
	}
	return ans;
}
int fac[N],inv[N];
void init() {
	fac[0]=inv[0]=1;
	for(int i=1;i<N;i++)fac[i]=fac[i-1]*i%mod;
	inv[N-1]=qpow(fac[N-1],mod-2)%mod;
	for(int i=N-2;i>=1;i--)inv[i]=inv[i+1]*(i+1)%mod;
}
int C(int n,int m) {
	if(m>n)return 0;
	return fac[n]*inv[m]%mod*inv[n-m]%mod;
}
int a[N];
signed main() {
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	init();
	int n,k;
	cin>>n>>k;
	int ans1=0,ans2=1;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int bit=30;bit>=0;bit--) {
		int tot=0;
		for(int i=1;i<=n;i++)tot+=(a[i]>>bit)&1;
		if(!tot)continue;
		if(tot<k) {
			vector<int>tmp;
			for(int i=1;i<=n;i++) {
				if((a[i]>>bit)&1)ans1+=a[i];
				else tmp.push_back(a[i]);
			}
			ans2=ans2*fac[k]%mod*inv[k-tot]%mod;
			k-=tot;
			n=tmp.size();
			for(int i=0;i<n;i++)a[i+1]=tmp[i];
		}
		else {
			int sum=-1;
			for(int i=1;i<=n;i++) {
				if(!((a[i]>>bit)&1)) {
					if(sum==-1)sum=a[i];
					else sum&=a[i];
				}
			}
			vector<int>tmp;
			if(sum!=-1)tmp.push_back(sum);
			for(int i=1;i<=n;i++)if((a[i]>>bit)&1)tmp.push_back((1<<bit)^a[i]);
			ans1+=k*(1<<bit);
			if(sum!=-1)ans1-=(1<<bit);
			n=tmp.size();
			for(int i=0;i<n;i++)a[i+1]=tmp[i];
		}
	}
	int sum=0;
	for(int i=1;i<=k;i++)sum=(sum+(((k-i)&1)?-1:1)*C(k,i)*qpow(i,n)%mod+mod)%mod;
	ans2=ans2*sum%mod;
	cout<<ans1<<" "<<ans2;
}