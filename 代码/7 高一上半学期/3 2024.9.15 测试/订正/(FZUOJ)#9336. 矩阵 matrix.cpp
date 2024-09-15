#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353;
int n,m,k;
int qpow(int x,int y){
	int ans=1;
	while(y){
		if(y&1)ans=ans*x%mod;
		y>>=1;
		x=x*x%mod;
	}
	return ans;
}
const int N=3e7+10,M=2e6;
int pn[N],pm[N];
int prime[M],cnt;
void init(const int lim){
	pn[1]=pm[1]=1;
	for(int i=2;i<=lim;i++){
		if(!pn[i]){
			prime[++cnt]=i;
			pn[i]=qpow(i,n),pm[i]=qpow(i,m);
		}
		for(int j=1;j<=cnt&&i*prime[j]<=lim;j++){
			pn[i*prime[j]]=pn[i]*pn[prime[j]]%mod;
			pm[i*prime[j]]=pm[i]*pm[prime[j]]%mod;
			if(i%prime[j]==0)break;
		}
	}
}
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	// freopen("matrix.in","r",stdin);
	// freopen("matrix.out","w",stdout);
	cin>>n>>m>>k;
	if(n>m)swap(n,m);
	init(k);
	if(n==1){
		cout<<qpow(k,m);
		return 0;
	}
	int ans=0;
	for(int i=1;i<=k;i++){
		ans=(ans+(pn[i]-pn[i-1]+mod)%mod*pm[k-i+1]%mod)%mod;
	}
	cout<<ans;
	return 0;
}
