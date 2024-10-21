#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+10;
const int mod=998244353;
int dp1[N],dp2[N];
int p[N];
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	dp1[1]=2,dp1[2]=6,dp1[3]=42,dp2[3]=7;
	for(int i=4;i<N;i++){
		dp2[i]=(2*dp2[i-1]%mod+1)%mod;
		dp1[i]=dp1[i-1]*dp2[i]%mod;
	}
	int T;
	cin>>T;
	while(T--){
		int n;
		cin>>n;
		for(int i=1;i<=n;i++)cin>>p[i];
		cout<<dp1[n]<<"\n";
	}
}