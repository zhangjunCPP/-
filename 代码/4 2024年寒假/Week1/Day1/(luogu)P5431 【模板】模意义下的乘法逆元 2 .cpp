#include <bits/stdc++.h>
#define int long long
const int N=5e6+10;
using namespace std;
int inv[N];
int a[N],s[N];
int n,mod,k;
int qpow(int x,int y){
	int ans=1;
	while(y){
		if(y&1) ans=ans*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return ans;
}
int read(){
	int x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9') {
		x=(x<<3)+(x<<1)+(ch^48);
		ch=getchar();
	}
	return x;
}
signed main(){
	n=read(),mod=read(),k=read();
	s[0]=1;
	for(int i=1;i<=n;i++)a[i]=read(),s[i]=s[i-1]*a[i]%mod;
	inv[n]=qpow(s[n],mod-2);
	for(int i=n-1;i>=1;i--) inv[i]=inv[i+1]*a[i+1]%mod;
	int ans=0;
	int K=1;
	for(int i=1;i<=n;i++){
		K=(K*k)%mod;
		int tmp=inv[i]*s[i-1]%mod;
		ans=(ans+K*tmp%mod)%mod;
	}
	cout<<ans;
}