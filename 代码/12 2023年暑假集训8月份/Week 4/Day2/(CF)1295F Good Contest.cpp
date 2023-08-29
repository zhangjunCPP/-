#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353;
const int N=200;
int qpow(int x,int y){
	int ans=1;
	while(y){
		if(y&1) ans=ans*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return ans%mod;
}
int inv[N];

int n;
int a[N],b[N];
int tmp[N],cnt;
int dp[N][N*2];
int g[N];
signed main(){
	for(int i=1;i<N;i++) inv[i]=qpow(i,mod-2);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i]>>b[i];
		tmp[++cnt]=a[i];
		tmp[++cnt]=(++b[i]);
	} 
	sort(tmp+1,tmp+cnt+1);
	cnt=unique(tmp+1,tmp+cnt+1)-tmp-1;
	for(int i=1;i<=n;i++){
		a[i]=lower_bound(tmp+1,tmp+cnt+1,a[i])-tmp;
		b[i]=lower_bound(tmp+1,tmp+cnt+1,b[i])-tmp;
	}
	
	a[0]=1,b[0]=cnt+1;
	for(int i=1;i<=cnt;i++) dp[0][i]=1;
	for(int i=1;i<=n;i++){
		for(int j=a[i];j<b[i];j++){
			int len=tmp[j+1]-tmp[j];
			g[1]=len;
			for(int k=2;k<=i;k++) g[k]=g[k-1]*(len+k-1)%mod*inv[k]%mod;
			for(int k=i-1;k>=0;k--){
				dp[i][j]=(dp[i][j]+dp[k][j+1]*g[i-k]%mod)%mod;
				if(j<a[k]||j>=b[k]) break;
			}
		}
		for(int j=cnt-1;j;j--)dp[i][j]=(dp[i][j]+dp[i][j+1])%mod;
	}
	int ans=dp[n][1];
	for(int i=1;i<=n;i++) ans=(ans*qpow(tmp[b[i]]-tmp[a[i]],mod-2))%mod;
	cout<<ans%mod<<"\n";		

	return 0;
}

