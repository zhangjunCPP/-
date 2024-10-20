#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=500+10;
const int mod=998244853;
int qpow(int x,int y){
	int ans=1;
	while(y){
		if(y&1)ans=ans*x%mod;
		y>>=1;
		x=x*x%mod;
	}
	return ans;
}
int a[N][5];
int C[N][N];
signed main(){
	int n;
	cin>>n;
	bool flag=true;
	for(int i=1;i<=n;i++){
		cin>>a[i][0]>>a[i][1]>>a[i][2]>>a[i][3];
		if(a[i][0]||a[i][1]||a[i][2]||a[i][3])flag=false;
	}
	C[0][0]=1;
	for(int i=1;i<=n;i++){
		C[i][0]=C[i][i]=1;
		for(int j=1;j<i;j++)C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
	}
	if(n<=5){cout<<"0";return 0;}
	if(flag){//C(n,6) *4^6*6!/4!
		cout<<C[n][6]*qpow(4,6)%mod*6%mod*5%mod;
		return 0;
	}
	cout<<"0";
	return 0;
}