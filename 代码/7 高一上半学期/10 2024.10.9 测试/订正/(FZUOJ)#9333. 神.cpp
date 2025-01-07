#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353;
const int N=6e3+10;
int n,m;	
int qpow(int x,int y){
	int ans=1;
	while(y){
		if(y&1)ans=ans*x%mod;
		y>>=1;
		x=x*x%mod;
	}
	return ans;
}
int pw1[N],pw2[N],pw3[N];//(n-1)^i,(n+1)^i,n^i
int C[N][N];
int sum[N];//sum[l]=\sum_{i=1}^n i^l
void init(){
	C[0][0]=1;
	for(int i=1;i<=m+1;i++){
		C[i][0]=C[i][i]=1;
		for(int j=1;j<i;j++)C[i][j]=(C[i-1][j-1]+C[i-1][j])%mod;
	}
	pw1[0]=pw2[0]=pw3[0]=1;
	for(int i=1;i<=m+1;i++)pw1[i]=pw1[i-1]*(n-1)%mod,pw2[i]=pw2[i-1]*(n+1)%mod,pw3[i]=pw3[i-1]*n%mod;
	sum[0]=n%mod;
	for(int i=1;i<=m;i++){
		for(int j=0;j<i;j++)sum[i]=(sum[i]+C[i+1][j]*sum[j]%mod)%mod;
		sum[i]=(pw2[i+1]-sum[i]-1+mod)%mod;
		sum[i]=sum[i]*qpow(i+1,mod-2)%mod;
	}
}
int solve(int a,int b,int c,int k){
	int ans=0;
	for(int j=0;j<=c;j++){
		int tmp=C[c][j]*pw2[c-j]%mod*sum[j+b]%mod;
		ans=(ans+(j&1?-1:1)*tmp+mod)%mod;
	}
	return ans*pw1[a]%mod*pw3[m-k]%mod;
}
signed main(){
	string s;
	cin>>n>>m>>s;
	init();
	int inv=qpow(qpow(n,m),mod-2)%mod;
	int a=0,b=0,c=0;
	for(int i=1;i<=m;i++){
		if(s[i-1]=='=')cout<<solve(a,b,c,i)*inv%mod<<" ",a++;
		else if(s[i-1]=='<')cout<<(solve(a,b,c+1,i)-solve(a,b,c,i)+mod)%mod*inv%mod<<" ",b++;
		else cout<<(solve(a,b+1,c,i)-solve(a,b,c,i)+mod)%mod*inv%mod<<" ",c++;
	}
	cout<<solve(a,b,c,m)*inv%mod;
}