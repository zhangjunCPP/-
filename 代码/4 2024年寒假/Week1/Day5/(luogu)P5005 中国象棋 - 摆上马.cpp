#include<bits/stdc++.h>
using namespace std;
const int N=1<<6;
const int mod=1e9+7;

int n,m;
bool check1(int S1,int S2){
	for(int i=0;i<m;++i){
		if(S1&(1<<i)){
			if( !(S1&(1<<(i+1))) && (S2&(1<<(i+2))) )return false;
			if(i>1)if( !(S1&(1<<(i-1))) && (S2&(1<<(i-2))) )return false;
		}
	}
	for(int i=0;i<m;++i){
		if(S2&(1<<i)){
			if( !(S2&(1<<(i+1))) && (S1&(1<<(i+2))) )return false;
			if(i>1)if( !(S2&(1<<(i-1))) && (S1&(1<<(i-2))) )return false;
		}
	}
	return true;
}
bool check2(int S1,int S2,int S3){
	for(int i=0;i<m;++i){
		if( (S1&(1<<i)) && !(S2&(1<<i)) ){
			if(S3&(1<<(i+1)))return false;
			if(i)if(S3&(1<<(i-1)))return false;
		}

	}
	for(int i=0;i<m;++i){
		if( (S3&(1<<i)) && !(S2&(1<<i)) ){
			if(S1&(1<<(i+1)))return false;
			if(i)if(S1&(1<<(i-1)))return false;
		}
	}
	return true;
}

bool flag1[N][N],flag2[N][N][N];
void init(){
	for(int i=0;i<(1<<m);++i)for(int j=0;j<(1<<m);++j)flag1[i][j]=check1(i,j);
	for(int S1=0;S1<(1<<m);++S1){
		for(int S2=0;S2<(1<<m);++S2){
			if(!flag1[S1][S2])continue;
			for(int S3=0;S3<(1<<m);++S3){
				if(!flag1[S2][S3])continue;
				flag2[S1][S2][S3]=check2(S1,S2,S3);
			}
		}
	}
}
int dp[3][N][N];
int main(){
	cin>>n>>m;
	init();
	dp[0][0][0]=1;
	for(int i=1;i<=n;++i){
		for(int S1=0;S1<(1<<m);++S1)for(int S2=0;S2<(1<<m);++S2)dp[i%3][S1][S2]=0;
		for(int S1=0;S1<(1<<m);++S1){
			for(int S2=0;S2<(1<<m);++S2){
				if(!flag1[S1][S2])continue;
				for(int S3=0;S3<(1<<m);++S3){
					if(!flag1[S2][S3])continue;
					if(!flag2[S1][S2][S3])continue;
					dp[i%3][S1][S2]=(dp[i%3][S1][S2]+dp[(i-1)%3][S2][S3])%mod;
				}
			}
		}
	}
	int ans=0;
	for(int S1=0;S1<(1<<m);++S1){
		for(int S2=0;S2<(1<<m);++S2){
			if(!flag1[S1][S2])continue;
			ans=(ans+dp[n%3][S1][S2])%mod;
		}
	}
	cout<<ans;
	return 0;
}