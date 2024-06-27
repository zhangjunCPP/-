#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
int read(){
	int x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9')ch=getchar();
	while(ch>='0'&&ch<='9'){
		x=((x<<3)+(x<<1)+(ch^48))%(mod-1);
		ch=getchar();
	}
	return x%(mod-1);
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
	int sqrt2=59713600;
	cout<<sqrt2*qpow(4,mod-2)%mod*(qpow(1+sqrt2,n)%mod-qpow(1-sqrt2,n)%mod+mod)%mod;
}