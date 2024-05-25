#include <bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
int qpow(int x,int y){
	int ans=1;
	while(y){
		if(y&1)ans=ans*x%mod;
		y>>=1;
		x=x*x%mod;
	}
	return ans%mod;
}
const int N=1e3+10;
int a[N][N];
signed main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)cin>>a[i][j];
		a[i][i+n]=1;
	}
	for(int i=1;i<=n;i++){
		for(int j=i;j<=n;j++)if(a[j][i]>0){swap(a[i],a[j]);break;}
		if(!a[i][i]){puts("No Solution");return 0;}
		int inv=qpow(a[i][i],mod-2)%mod;
		for(int j=1;j<=n;j++){
			if(j==i)continue;
			int tmp=a[j][i]*inv%mod;
			for(int k=i;k<=2*n;k++)a[j][k]=(a[j][k]-tmp*a[i][k]%mod+mod)%mod;
		}
		for(int j=1;j<=2*n;j++)a[i][j]=a[i][j]*inv%mod;
	}
	for(int i=1;i<=n;i++){
		for(int j=n+1;j<=2*n;j++)cout<<a[i][j]<<" ";
		cout<<"\n";
	}
	return 0;
}