#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1e7+10;
const int mod=998244353;
int prime[N],cnt;
bool vis[N];
ll phi[N];
void get_phi(){
	vis[1]=true;
	for(int i=2;i<N;i++){
		if(!vis[i]){
			prime[++cnt]=i;
			phi[i]=i-1;
		}
		for(int j=1;j<=cnt&&i*prime[j]<N;j++){
			vis[i*prime[j]]=true;
			if(i%prime[j]==0){
				phi[i*prime[j]]=prime[j]*phi[i];
				break;
			}
			phi[i*prime[j]]=(prime[j]-1)*phi[i];
		}
	}
}
ll qpow(ll x,ll y){
	ll ans=1;
	while(y){
		if(y&1)ans=(ans*x)%mod;
		y>>=1;
		x=(x*x)%mod;
	}
	return ans%mod;
}
ll sum[N];
int main(){
	get_phi();
	sum[1]=1;
	for(int i=2;i<N;i++){
		sum[i]=(sum[i-1]+vis[i]* qpow(phi[i]*i%mod,mod-2))%mod;
	}
	int T;
	cin>>T;
	while(T--){
		int n;
		cin>>n;
		cout<<sum[n]%mod<<"\n";
	}

}