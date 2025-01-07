#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e7+10;
int mod,n;
int qpow(int x,int y){
	int ans=1;
	while(y) {
		if(y&1) ans=ans*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return ans%mod;
}
int inv2,inv4,inv6;
int inv(int x) {return qpow(x,mod-2)%mod;}
int prime[N],cnt;
int phi[N];
bool vis[N];
void init() {
	inv2=inv(2);
	inv4=inv(4);
	inv6=inv(6);
	phi[1]=1;
	for(int i=2;i<N;i++) {
		if(!vis[i]){
			prime[++cnt]=i;
			phi[i]=i-1;
		}
		for(int j=1;i*prime[j]<N&&j<=cnt;j++) {
			vis[i*prime[j]]=true;
			if(i%prime[j]==0) {
				phi[i*prime[j]]=phi[i]*prime[j]%mod;
				break;
			}
			phi[i*prime[j]]=phi[i]*(prime[j]-1)%mod;
		}
	}
	for(int i=1;i<N;i++) {
		phi[i]=(phi[i-1]+i%mod*i%mod*phi[i]%mod)%mod;
	}
}

int id1(int x) {x%=mod;return x*(x+1)%mod*inv2%mod;}
int id2(int x) {x%=mod;return x*(x+1)%mod*(x+x+1)%mod*inv6%mod;};
int id3(int x) {x%=mod;return id1(x)%mod*id1(x)%mod;}

unordered_map<int,int> ans_phi;
int get(int x) {
	if(x<N) return phi[x];
	if(ans_phi[x]) return ans_phi[x];
	int ans=id3(x);
	for(int l=2,r;l<=x;l=r+1) {
		r=x/(x/l);
		ans=(ans-(id2(r)-id2(l-1)+mod)%mod*get(x/l)%mod+mod)%mod;
	}
	ans_phi[x]=(ans+mod)%mod;
	return ans_phi[x]%mod;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>mod>>n;
	init();
	int ans=0;
	for(int l=1,r;l<=n;l=r+1){
		r=n/(n/l);
		int x=id3(n/l)%mod;
		ans=(ans+(get(r)-get(l-1)+mod)%mod*x%mod)%mod;
	}
	cout<<ans;
	return 0;
}