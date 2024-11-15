#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e6+10,mod=998244353;
int qpow(int x,int y){
	int ans=1;
	while(y){
		if(y&1)ans=ans*x%mod;
		y>>=1;
		x=x*x%mod;
	}
	return ans;
}
int n;
int fac[N],inv[N];
int lg[N];
void init(){
	fac[0]=1;
	for(int i=1;i<N;i++)fac[i]=fac[i-1]*i%mod;
	inv[0]=1;
	inv[N-1]=qpow(fac[N-1],mod-2);
	for(int i=N-2;i>0;i--)inv[i]=inv[i+1]*(i+1)%mod;
	lg[1]=0;
	for(int i=2;i<N;i++)lg[i]=lg[i>>1]+1;
	for(int i=2;i<N;i++)if(i!=(1ll<<lg[i]))lg[i]++;
}
int C(int n,int m){
	return fac[n]*inv[m]%mod*inv[n-m]%mod;
}
map<pair<int,int>,int> mp;
int dp(int n,int k){
	k=min(k,lg[n]);
	if(mp.count({n,k}))return mp[{n,k}];
	if(!k)return 1;
	mp[{n,k}]=dp((n+1)/2,k-1)*dp(n/2,k-1)%mod*C(n,n/2)%mod;
	return mp[{n,k}];
}
void solve(){
	int k;
	cin>>k;
	cout<<dp(n,k)<<"\n";
}
signed main(){
	freopen("sort.in","r",stdin);
	freopen("sort.out","w",stdout);
	ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
	init();
	int T;
	cin>>T>>n;
	while(T--)solve();
}