#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e3+10;
int a[N],b[N];
int dp1[N][N],dp2[N][N];
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)cin>>b[i];
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			dp1[i][j]=max(dp1[i][j],dp1[i-1][j-1]);
			int sum=a[i];
			for(int k=1;a[i]-(k-1)*b[i]>0&&k<=j+1-i;k++){
				dp1[i][j]=max(dp1[i][j],dp1[i-1][j-k-1]+sum);
				sum+=a[i]-k*b[i];
			}
		}
	}
	for(int i=n;i>=1;i--){
		for(int j=1;j<=m;j++){
			dp2[i][j]=max(dp2[i][j],dp2[i+1][j-1]);
			int sum=a[i];
			for(int k=1;a[i]-(k-1)*b[i]>0&&k<=j+i-n;k++){
				dp2[i][j]=max(dp2[i][j],dp2[i+1][j-k-1]+sum);
				sum+=a[i]-k*b[i];
			}
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		ans=max(ans,dp1[i][m]);
		for(int j=i;j<=m;j++)for(int k=n;k>=max(n+i+j-m,1ll);k--)if(i<k)ans=max(ans,dp1[i][j]+dp2[k][m-j-i]);
	}
	for(int i=n;i>=1;i--){
		ans=max(ans,dp2[i][m-1]);
		for(int j=n-i;j<=m;j++)for(int k=1;k<=min(m-j-(n-i+1),n);k++)if(i>k)ans=max(ans,dp2[i][j]+dp1[k][m-j-(n-i+1)-1]);
	}
	cout<<ans;
	return 0;
}