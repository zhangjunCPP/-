#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=100,mod=1e9+7;
int C[N][N];
void init(){
	C[0][0]=1;
	for(int i=1;i<N;i++){
		C[i][0]=C[i][i]=1;
		for(int j=1;j<i;j++)C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
	}
}
int a[N];
int sum[15];
int ans;
int dp[N];
void calc(int n){
	for(int k=0;k<=9;k++){
		for(int s=sum[k];s<=sum[k]+n;s++){
			int tot=n-(s-sum[k]);
			for(int i=1;i<=tot;i++)dp[i]=0;
			dp[0]=1;
			bool flag=true;
			for(int i=0;i<=9;i++){
				if(i==k)continue;
				int now=s-sum[i];
				if(i>k)now--;
				if(now<0){flag=false;break;}
				for(int j=tot;j;j--){
					for(int l=1;l<=now;l++)dp[j]=(dp[j]+dp[j-l]*C[j][l]%mod)%mod;
				}
			}
			if(flag)ans=(ans+k*dp[tot]%mod*C[n][s-sum[k]]%mod)%mod;
		}
	}
}
void solve(){
	string s;
	cin>>s;
	int n=s.length();
	for(int i=1;i<=n;i++)a[i]=s[i-1]-'0';
	memset(sum,0,sizeof sum);
	for(int i=1;i<=n;i++)sum[a[i]]++;
	ans=9;
	for(int i=8;i>=0;i--)if(sum[i]>sum[ans])ans=i;
	memset(sum,0,sizeof sum);
	for(int i=1;i<n;i++)//此时位数比原数少1，可以随便选
		for(int j=1;j<=9;j++)sum[j]++,calc(i-1),sum[j]--;
	for(int i=1;i<=n;i++){
		for(int j=(i!=1?0:1);j<a[i];j++)sum[j]++,calc(n-i),sum[j]--;
		sum[a[i]]++;
	}
	cout<<ans<<"\n";
}
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	init();
	int T;
	cin>>T;
	while(T--)solve();
}