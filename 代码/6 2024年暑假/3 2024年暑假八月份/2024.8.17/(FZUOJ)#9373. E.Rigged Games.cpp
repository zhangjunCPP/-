#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int sum0[N*4],sum1[N*4];
int dp[2][N][20],nex[N][20];
int main() {
	int n,A,B;
	string s;
	cin>>n>>A>>B>>s;
	for(int i=1;i<N*4;i++)sum0[i]=sum0[i-1]+(s[(i-1)%n]=='0'),sum1[i]=sum1[i-1]+(s[(i-1)%n]=='1');
	for(int i=1;i<=n;i++) {
		int l=i+A-1,r=N*4-1;
		int pos1=1e9,pos2=1e9;
		while(l<=r) {
			int mid=(l+r)>>1;
			if(sum0[mid]-sum0[i-1]>=A)pos1=mid,r=mid-1;
			else l=mid+1;
		}
		l=i+A-1,r=N*4-1;
		while(l<=r) {
			int mid=(l+r)>>1;
			if(sum1[mid]-sum1[i-1]>=A)pos2=mid,r=mid-1;
			else l=mid+1;
		}
		dp[pos1>pos2][i][0]++;
		nex[i][0]=min(pos1,pos2)%n+1;
	}
	for(int j=1;j<20;j++) {
		for(int i=1;i<=n;i++) {
			dp[0][i][j]=dp[0][i][j-1]+dp[0][nex[i][j-1]][j-1];
			dp[1][i][j]=dp[1][i][j-1]+dp[1][nex[i][j-1]][j-1];
			nex[i][j]=nex[nex[i][j-1]][j-1];
		}
	}
	for(int i=1;i<=n;i++) {
		int sum0=0,sum1=0;
		int pos=i;
		for(int j=19;j>=0;j--) {
			if(sum0+dp[0][pos][j]==B&&sum1+dp[1][pos][j]==B)continue;
			if(sum0+dp[0][pos][j]>B||sum1+dp[1][pos][j]>B)continue;
			sum0+=dp[0][pos][j];sum1+=dp[1][pos][j];
			pos=nex[pos][j];
		}
		if(sum0==B)putchar('0');
		else putchar('1');
	}
}