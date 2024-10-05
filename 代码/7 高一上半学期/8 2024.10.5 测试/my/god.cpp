#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
const int N=1e7+10;
int qpow(int x,int y){
	int ans=1;
	while(y){
		if(y&1)ans=ans*x%mod;
		y>>=1;
		x=x*x%mod;
	}
	return ans;
}
int inv[N];

void solve(int ans){
	map<pair<int,int>,bool> mp;
	for(int x=1;x<=1000;x++){
		for(int y=1;y<N;y++){
			if(x*inv[y]%mod==ans){
				int GCD=__gcd(x,y);
				x/=GCD,y/=GCD;
				if(!mp.count({x,y}))cout<<x<<"/"<<y<<"="<<ans<<"\n",mp[{x,y}]=true;
			}
		}
	}
}
signed main(){
	inv[1]=1;
	for(int i=2;i<N;i++)inv[i]=(mod-mod/i)*inv[mod%i]%mod;
	solve(710859005);
	solve(390982003);
	solve(135049706);
	solve(506522154);
	solve(13802205);
	solve(1);
}
