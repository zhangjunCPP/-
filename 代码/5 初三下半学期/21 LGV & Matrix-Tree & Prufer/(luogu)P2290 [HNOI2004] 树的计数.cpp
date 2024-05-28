#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e3+10;
int C[N][N];
int d[N];
signed main(){
	int n;
	cin>>n;
	int sum=0;
	for(int i=1;i<=n;i++)cin>>d[i],sum+=d[i]-1;
	if(sum!=n-2){cout<<"0";return 0;}
	if(n==1){cout<<"1";return 0;}
	for(int i=0;i<=n;i++)C[i][0]=1;
	for(int i=1;i<=n;i++)for(int j=1;j<=i;j++)C[i][j]=C[i-1][j]+C[i-1][j-1];
	int ans=1;
	for(int i=1;i<=n;i++)ans*=C[sum][d[i]-1],sum-=d[i]-1;
	cout<<ans;
}