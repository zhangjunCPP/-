#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
int x[N],p[N],c[N];
int sum1[N],sum2[N];
int dp[N];
int X(int i){return sum2[i];}
int Y(int i){return dp[i]+sum1[i];}
int q[N],l,r;
double slope(int i,int j){
	if(X(i)==X(j)){return Y(j)>=Y(i)?1e18:-1e18;}
	return (1.0*(Y(j)-Y(i)))/(1.0*(X(j)-X(i)));
}
signed main(){
	memset(dp,0x3f,sizeof dp);
	dp[0]=0;
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>x[i]>>p[i]>>c[i];
		sum1[i]=sum1[i-1]+p[i]*x[i];
		sum2[i]=sum2[i-1]+p[i];
	}
	l=1,r=1;
	q[1]=0;
	for(int i=1;i<=n;i++){
		while(l<r&&slope(q[l],q[l+1])<=x[i])l++;
		dp[i]=Y(q[l])-x[i]*X(q[l])+c[i]+x[i]*sum2[i-1]-sum1[i-1];
		while(l<r&&slope(q[r-1],q[r])>=slope(q[r],i))r--;
		q[++r]=i;
	}
	int ans=1e18;
	for(int i=n;i;i--){
		ans=min(ans,dp[i]);
		if(p[i])break;
	}
	cout<<ans;
}