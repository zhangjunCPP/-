#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10,mod=2004;
int fac[N];
int n,a,b;
int m[N];
int C(int x,int y){
	if(x<y)return 0;
	int Mod=mod*fac[n];
	int ans=1;
	for(int i=x-y+1;i<=x;i++)ans=ans*i%Mod;
	return (ans/fac[n])%mod;
}
int dfs(int k,int opt,int sum,int tot){
	if(k>n)return C(n+tot-sum,n)*opt;
	else return (dfs(k+1,opt,sum,tot)+dfs(k+1,-opt,sum+m[k]+1,tot)+mod)%mod;
}
signed main(){
	cin>>n>>a>>b;
	for(int i=1;i<=n;i++)cin>>m[i];
	fac[0]=1;
	for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i;
	cout<<(dfs(1,1,0,b)-dfs(1,1,0,a-1)+mod)%mod;
}