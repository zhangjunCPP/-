#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353,inv2=(mod+1)/2;
int exgcd(int a,int b,int &x,int &y){
	if(!b){
		x=1,y=0;
		return a;
	}
	int gcd=exgcd(b,a%b,y,x);
	y-=a/b*x;
	return gcd;
}
int f(int a,int b,int m){
	int x,y;
	int gcd=exgcd(a,m,x,y);
	if(b%gcd)return 0;
	x=b/gcd*x;
	int tmp=m/gcd;
	return (x%tmp+tmp)%tmp;
}
void solve(){
	int ans=0;
	int n,a,b;
	cin>>n>>a>>b;
	for(int i=1;i<=min(b,n);i++)ans=(ans+f(a,b,i))%mod;
	if(b%a==0){
		cout<<(ans+b/a*(max(0ll,n-b)%mod)%mod)%mod<<"\n";
		return;
	}
	for(int i=0;i<a;i++){
		int d=f(i,-b,a);
		if(d==0)continue;
		int l=i>b?0:(b-i)/a+1;
		int r=i<=n?(n-i)/a:-1;
		if(l>r)continue;
		int val1=(b+i*d)/a+l*d;
		int val2=(b+i*d)/a+r*d;
		ans=(ans+(val1+val2)%mod*((r-l+1)%mod)%mod*inv2%mod)%mod;
	}
	cout<<ans%mod<<"\n";
}
signed main(){
	int T;
	cin>>T;
	while(T--)solve();
}