#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10,mod=998244353;
int qpow(int x,int y){
	int ans=1;
	while(y){
		if(y&1)ans=ans*x%mod;
		y>>=1;
		x=x*x%mod;
	}
	return ans;
}
int fac[N],inv[N];
void init(){
	fac[0]=1;
	for(int i=1;i<N;i++)fac[i]=fac[i-1]*i%mod;
	inv[0]=1;
	inv[N-1]=qpow(fac[N-1],mod-2);
	for(int i=N-2;i>0;i--)inv[i]=inv[i+1]*(i+1)%mod;
}
int C(int n,int m){return fac[n]*inv[m]%mod*inv[n-m]%mod;}
int A(int n,int m){return C(n,m)*fac[m]%mod;}
void solve(){
	int n,m;
	cin>>n>>m;
	int Min=n;
	for(int i=1;i<=m;i++){
		int x;
		cin>>x;
		Min=min(Min,x);
	}
	int ans;
	if(Min==0)ans=A(n,n-m);
	else ans=A(n,n-m-Min)*(m+1)%mod*fac[Min]%mod;
	cout<<ans<<"\n";
}
signed main(){
	freopen("atcoder.in","r",stdin);
	freopen("atcoder.out","w",stdout);
	ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
	init();
	int T;
	cin>>T;
	while(T--)solve();
}