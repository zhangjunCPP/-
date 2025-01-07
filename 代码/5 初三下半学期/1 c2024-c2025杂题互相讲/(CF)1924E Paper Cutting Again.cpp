#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e6+10;
const int mod=1e9+7;
int inv[N];
void init(){
	inv[1]=1;
	for(int i=2;i<N;i++)inv[i]=(mod-mod/i)*inv[mod%i]%mod;
}
void solve(){
	int n,m,k;
	cin>>n>>m>>k;
	k--;
	if(n*m<=k){cout<<"0\n";return;}
	int ans=1;
	for(int i=1;i<n;i++){
		int j=min(k/i,m);
		if(j==m)continue;
		ans=(ans+inv[i+j])%mod;
	}
	for(int j=1;j<m;j++){
		int i=min(k/j,n);
		if(i==n)continue;
		ans=(ans+inv[i+j])%mod;
	}
	cout<<ans%mod<<"\n";
}
signed main(){
	init();
	int T;
	cin>>T;
	while(T--)solve();
}