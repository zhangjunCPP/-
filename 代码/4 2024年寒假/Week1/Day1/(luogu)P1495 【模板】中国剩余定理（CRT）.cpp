#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
int exgcd(int a,int b,int &x,int &y){
	if(b==0){
		x=1,y=0;
		return a;
	}
	int gcd=exgcd(b,a%b,y,x);
	y-=a/b*x;
	return gcd;
}
int mul(int x,int y,int mod){
	int ans=0;
	while(y){
		if(y&1) ans=(ans+x)%mod;
		x=(x+x)%mod;
		y>>=1;
	}
	return ans;
}
int m[N],a[N];
signed main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>m[i]>>a[i];
	int M=1;
	for(int i=1;i<=n;i++) M*=m[i];
	int ans=0;
	for(int i=1;i<=n;i++){
		int mi=M/m[i];
		int x,y;
		exgcd(mi,m[i],x,y);
		x=(x%m[i]+m[i])%m[i];
		ans=(ans+mul(a[i]*mi%M,x,M)%M)%M;
	}
	cout<<(ans%M+M)%M;
}