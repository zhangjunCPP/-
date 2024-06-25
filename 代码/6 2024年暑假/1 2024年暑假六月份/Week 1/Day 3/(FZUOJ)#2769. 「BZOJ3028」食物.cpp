#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=10007;
int read(){
	int x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9')ch=getchar();
	while(ch>='0'&&ch<='9'){
		x=((x<<3)+(x<<1)+(ch^48))%mod;
		ch=getchar();
	}
	return x%mod;
}
int qpow(int x,int y){
	int ans=1;
	while(y){
		if(y&1)ans=ans*x%mod;
		y>>=1;
		x=x*x%mod;
	}
	return ans%mod;
}
signed main(){
	int n=read();
	cout<<(n+2)%mod*(n+1)%mod*n%mod*qpow(6,mod-2)%mod;
}