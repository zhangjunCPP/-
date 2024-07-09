#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e7+10;
int c[N];
int dp[N];
int pos[N];
signed main(){
	// freopen("dictionary.in","r",stdin);
	// freopen("dictionary.out","w",stdout);
	for(int i=1;i<N;i++)c[i]=c[i-1]+1+log2(i);
	c[1]=0;
	memset(dp,0x3f,sizeof dp);
	dp[1]=1;
	pos[1]=1;
	for(int i=2;i<N;i++){
		for(int j=pos[i-1];j<min(i,pos[i-1]+3);j++){
			int tmp=dp[j]+c[j]+dp[i-j]+c[i];
			if(tmp<dp[i]){
				dp[i]=tmp;
				pos[i]=j;
			}
		}
	}
	int T;
	cin>>T;
	while(T--){
		int n;
		cin>>n;
		cout<<dp[n]<<"\n";
	}
}