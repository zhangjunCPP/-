#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
const int N=1e5+10;
int dp[N],pw[N];
int g[N];
int popc(int x) {return __builtin_popcountll(x);}
signed main(){
	int n,m;
	cin>>n>>m;
	pw[0]=1;
	for(int i=1;i<N;i++) pw[i]=(pw[i-1]*2)%mod;
	dp[0]=1;
	for(int i=1;i<=m;i++) {
		int x,y;
		cin>>x>>y;
		x--,y--;
		g[x]|=(1<<y);
	}
	for(int u=1;u<(1<<n);u++) {
		if((u&1)==(u>>1&1)) {
			for(int v=u;v;v=(v-1)&u) {
				if((v&1)==(v>>1&1)){
					int ans=1;
					for(int i=0;i<n;i++){
						if(u>>i&1) {
							if(v>>i&1)  ans=ans*pw[popc(g[i]&(u^v))]%mod;
							else ans=ans*(pw[popc(g[i]&v)]-1)%mod;
						}
					}
					dp[u]=(dp[u]+dp[u^v]*ans%mod)%mod;
				}
			}
		}
	}
	cout<<(pw[m]-dp[(1<<n)-1]+mod)%mod;
}
