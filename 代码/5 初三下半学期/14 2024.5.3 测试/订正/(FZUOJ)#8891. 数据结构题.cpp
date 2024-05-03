#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
const int mod=998244353;
int qpow(int x,int y){
	int ans=1;
	while(y){
		if(y&1)ans=ans*x%mod;
		y>>=1;
		x=x*x%mod;
	}
	return ans%mod;
}
int fac[N],inv[N];
void init(){
	fac[0]=1;
	for(int i=1;i<N;i++)fac[i]=fac[i-1]*i%mod;
	inv[N-1]=qpow(fac[N-1],mod-2);
	for(int i=N-2;i>=0;i--)inv[i]=inv[i+1]*(i+1)%mod;
}
int C(int x,int y){return fac[x]*inv[y]%mod*inv[x-y]%mod;}
struct node{
	int id,val;
	int time;
};
int t;
int solve(int id,node x){
	if(x.id>id)return 0;
	return x.val*C(t-x.time+id-x.id,t-x.time)%mod;
}
vector<node> q;
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	init();
	int n,m;
	cin>>n>>m;
	t=1;
	q.push_back({1,1,0});
	while(m--){
		int opt;
		cin>>opt;
		if(opt==1)t++;
		else if(opt==2){
			int id,val;
			cin>>id>>val;
			q.push_back({id,val,t});
		}
		else{
			int l,r;
			cin>>l>>r;
			int ans=0;
			for(auto i:q)ans=(ans+solve(r,i)-solve(l-1,i)+mod)%mod;
			cout<<ans<<"\n";
		}
	}
}