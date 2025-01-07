#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=5000+10,M=1e6+10;
int l[M];
int A[M],fac[N];
int dp1[N][N];
int dp2[N],tmp[N];
signed main(){
	int n,m,p;
	cin>>n>>m>>p;
	A[0]=fac[0]=1;
	for(int i=1;i<=m;i++)A[i]=A[i-1]*(m-i+1)%p;
	for(int i=1;i<N;i++)fac[i]=fac[i-1]*i%p;
	dp1[0][0]=1;
	for(int i=1;i<N;i++)for(int j=1;j<=min(i,m);j++)dp1[i][j]=(dp1[i-1][j-1]+(j-1)*dp1[i-1][j]%p)%p;
	for(int i=1;i<=n;i++)cin>>l[i];
	int ans=1;
	for(int i=1;i<=n;i++){
		int sum=0;
		for(int j=1;j<=l[i];j++){
			dp2[j]=(dp1[l[i]][j]*A[j]%p*ans%p-dp1[l[i]][j]*fac[j]%p*tmp[j]%p+p)%p;
			sum=(sum+dp2[j])%p;
		}
		ans=sum;
		for(int j=1;j<=l[i-1];j++)tmp[j]=0;
		for(int j=1;j<=l[i];j++)tmp[j]=dp2[j];
	}
	cout<<ans;
}