#include <bits/stdc++.h>
using namespace std;
const int N=2e6+10;
int dp[N];
int a[N];
int c[N];
int main(){
	int T=0;
	while(1){
		++T;
		bool flag=false;
		int sum=0;
		for(int i=1;i<=6;i++) cin>>a[i],flag|=(a[i]>0),sum+=a[i]*i;
		if(!flag) break;
		printf("Collection #%d:\n",T);
		if(sum&1) {puts("Can't be divided.");continue;}
		int cnt=0;
		for(int i=1;i<=6;i++){
			for(int j=0;j<=20;j++){
				if(a[i]>=(1<<j)){
					c[++cnt]=i*(1<<j);
					a[i]-=(1<<j);
				}
			}
			if(a[i]) c[++cnt]=i*a[i];
		}
		memset(dp,0,sizeof dp);
		dp[0]=1;
		for(int i=1;i<=cnt;i++)for(int j=sum/2;j>=c[i];j--) dp[j]|=dp[j-c[i]];
		puts(dp[sum/2]?"Can be divided.\n":"Can't be divided.\n");
	}
}