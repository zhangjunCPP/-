#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
int d[N],a[N];
int sum1[N];
int dp1[105][N],dp2[N];
int q[N];
bool cmp(int x,int y){return x<y;}
signed main(){
	memset(dp1,0x3f,sizeof dp1);
	dp1[0][0]=0;
	int n,m,p;
	cin>>n>>m>>p;
	for(int i=2;i<=n;i++){
		int x;
		cin>>x;
		d[i]=d[i-1]+x;
	}
	for(int i=1;i<=m;i++){
		int x,y;
		cin>>x>>y;
		a[i]=y-d[x];
	}
	sort(a+1,a+m+1,cmp);
	for(int i=1;i<=m;i++)sum1[i]=sum1[i-1]+a[i];
	for(int i=1;i<=p;i++){
		int l=1,r=1;
		q[l]=0;
		for(int j=1;j<=m;j++) dp2[j]=dp1[i-1][j]+sum1[j];
		for(int j=1;j<=m;j++){
			while(l<r&&dp2[q[l+1]]-dp2[q[l]]<=a[j]*(q[l+1]-q[l]))l++;
			dp1[i][j]=min(dp1[i-1][j],dp2[q[l]]-a[j]*q[l]+a[j]*j-sum1[j]);
			while(l<r&&(dp2[q[r]]-dp2[q[r-1]])*(j-q[r])>=(dp2[j]-dp2[q[r]])*(q[r]-q[r-1]))r--;
			q[++r]=j;
		}
	}
	cout<<dp1[p][m];
}