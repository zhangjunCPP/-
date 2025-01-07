#include<bits/stdc++.h>
using namespace std;
int read(){
	int x=0;
	int f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') {x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x*f;
}
void write(int x){
	if(x<0) {putchar('-');x=-x;}
	if(x>9) write(x/10);
	putchar(x%10+'0');
}
int n;
int a[5005];
int dp[5005][5005];
int p[5005][5005];
int sum[5005];
void slove(){
	for(int i=1;i<=n;i++){cin>>a[i];sum[i]=sum[i-1]+a[i];}
	memset(dp,0x3f,sizeof dp);
	for(int i=1;i<=n;i++){
		dp[i][i]=0;
		p[i][i]=i;
	}
	for(int len=2;len<=n;len++){
		for(int i=1;i<=n-len+1;i++){
			int j=i+len-1;
			int w=sum[j]-sum[i-1];
			for(int k=p[i][j-1];k<=p[i+1][j];k++){
				if(dp[i][j]>=dp[i][k]+dp[k+1][j]+w){
					dp[i][j]=dp[i][k]+dp[k+1][j]+w;
					p[i][j]=k;
				}
			}
		}
	}
	cout<<dp[1][n]<<"\n";
}
int main(){
	cin>>n;
	slove();
	return 0;
}