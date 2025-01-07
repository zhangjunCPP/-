#include<bits/stdc++.h>
#define int long long
using namespace std;
int qpow(int x,int y,int mod) {
	int ans=1,a=x;
	while(y) {
		if(y&1) {
			ans=ans*a%mod;
		}
		y>>=1;
		a=(a*a)%mod;
	}
	return ans;
}
int exgcd(int a,int b,int &x,int &y) {
	if(b==0) {
		x=1,y=0;
		return a;
	}
	int g=exgcd(b,a%b,y,x);
	y-=a/b*x;
	return g;
}
int BSGS(int a,int b,int mod){
	unordered_map<int,int> mp;
	if(a%mod==0)return -1;
	int t=ceil(sqrt(mod));
	int k=b%mod;
	mp[k]=0;
	for(int i=1;i<=t;i++){
		k=k*a%mod;
		mp[k]=i;
	}
	k=qpow(a,t,mod);
	int now=1;
	for(int i=1;i<=t;i++){
		now=now*k%mod;
		if(mp[now]){
			int ans=(i*t-mp[now]);
			return (ans%mod+mod)%mod;
		}
	}
	return -1;
}
signed main() {
	int T,K;
	cin>>T>>K;
	for(int i=1; i<=T; i++) {
		int a,b,c;
		cin>>a>>b>>c;
		if(K==1) cout<<qpow(a,b,c)<<"\n";
		else if(K==2) {
			int x,y;
			int gcd=exgcd(a,c,x,y);
			if(gcd!=1)puts("Orz, I cannot find x!");
			else {
				x=x*b/gcd;
				int B=c/gcd;
				x=x%B;
				x=(x%c+c)%c;
				cout<<x<<"\n";
			}
		}
		else if(K==3) {
			int ans=BSGS(a,b,c);
			if(a%c==b%c) ans=1;
			if(ans==-1)puts("Orz, I cannot find x!");
			else cout<<ans<<"\n";
		}
	}
	return 0;
}