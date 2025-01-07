#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e7+10;
const int mod=1e9+7;
int prime[N],cnt;
bool vis[N];
int phi[N];
void get_phi(){
	for(int i=2;i<N;i++){
		if(!vis[i]){prime[++cnt]=i;phi[i]=i-1;}
		for(int j=1;j<=cnt&&i*prime[j]<N;j++){
			vis[i*prime[j]]=true;
			if(i%prime[j]==0){phi[i*prime[j]]=prime[j]*phi[i];break;}
			phi[i*prime[j]]=(prime[j]-1)*phi[i];
		}
	}
}
int gcd(int x,int y){
	while(y^=x^=y^=x%=y);
	return x;
}
int lcm(int x,int y){return x/gcd(x,y)*y;}
signed main(){
	get_phi();
	int n;
	cin>>n;
	int ans=0;
	for(int i=1;i<n;i++){
		for(int j=2;j*i<n;j++){
			int c=n-i*j;
			int tmp=lcm(c,i);
			ans=(ans+tmp*phi[j])%mod;
		}
	}
	cout<<ans%mod;
}