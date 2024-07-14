#include<bits/stdc++.h>
using namespace std;
const int N=100+10;
string s;
int dp1[N][N];
int calc1(int l1,int r1,int l2,int r2) {
	memset(dp1,0,sizeof dp1);
	for(int i=l1;i<=r1;i++) {
		for(int j=l2;j<=r2;j++) {
			dp1[i][j]=max({dp1[i-1][j],dp1[i][j-1],dp1[i-1][j-1]+(s[i-1]==s[j-1])});
		}
	}
	return dp1[r1][r2];
}
int dp2[N][N][N];
int calc2(int l1,int r1,int l2,int r2,int l3,int r3) {
	memset(dp2,0,sizeof dp2);
	for(int i=l1;i<=r1;i++) {
		for(int j=l2;j<=r2;j++) {
			for(int k=l3;k<=r3;k++) {
				dp2[i][j][k]=max({dp2[i-1][j][k],dp2[i][j-1][k],dp2[i][j][k-1],dp2[i-1][j-1][k-1]+(s[i-1]==s[j-1]&&s[j-1]==s[k-1])});
			}
		}
	}
	return dp2[r1][r2][r3];
}
int main() {
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	cin>>s;
	int n=s.size();
	int ans=0;
	for(int i=1;i<n;i++)ans=max(ans,2*calc1(1,i,i+1,n));
	for(int i=1;i<n;i++)
		for(int j=i+1;j<n;j++)
			ans=max(ans,3*calc2(1,i,i+1,j,j+1,n));
	for(int i=1;(i-1)*16<=n;i++) {
		int len=min(i*16,n)-(i-1)*16;
		for(int S=1;S<(1<<len);S++){
			string t;
			for(int j=0;j<len;j++)if((S>>j)&1)t.push_back(s[(i-1)*16+j]);
			int tot=t.size();
			int sum=0;
			for(int j=0,k=0;j<n;j++) {
				if(s[j]==t[k]) {
					k++;
					if(k==tot)sum++,k=0;
				}
			}
			if(sum>=2)ans=max(ans,sum*tot);
		}
	}
	cout<<ans;
}