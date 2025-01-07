#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod=59393;
const int N=1e6+10;
int fac[N],inv[N];
void init(){
	fac[0]=inv[0]=inv[1]=1;
	for(int i=1;i<N;i++)fac[i]=fac[i-1]*i%mod;
	for(int i=2;i<N;i++)inv[i]=(mod-mod/i)*inv[mod%i]%mod;
	for(int i=1;i<N;i++)inv[i]=inv[i-1]*inv[i]%mod;
}
int C(int n,int m){return fac[n]*inv[m]%mod*inv[n-m]%mod;}
int lucas(int n,int m){
	if(m==0)return 1;
	return lucas(n/mod,m/mod)%mod*C(n%mod,m%mod)%mod;
}

struct node{
	int x,y;
}a[N];
bool cmp(const node&x,const node&y){
	if(x.x==y.x) return x.y<y.y;
	else return x.x<y.x;
}
int w(int n,int m){
	int ans=0;
	for(int i=0;i<=min(n,m);i++){
		ans=(ans+lucas(n+m-i,i)*lucas(n+m-2*i,n-i)%mod)%mod;
	}
	return ans%mod;
}
int dp[N];
signed main(){
	init();
	int n,m,k;
	cin>>n>>m>>k;
	for(int i=1;i<=k;i++)cin>>a[i].x>>a[i].y;
	a[++k]={n+1,m+1};
	sort(a+1,a+k+1,cmp);
	for(int i=1;i<=k;i++){
		dp[i]=w(a[i].x-1,a[i].y-1);
		for(int j=1;j<i;j++){
			if(a[j].x<=a[i].x&&a[j].y<=a[i].y){
				dp[i]=(dp[i]-dp[j]*w(a[i].x-a[j].x,a[i].y-a[j].y)+mod)%mod;
			}
		}
	}
	cout<<(dp[k]+mod)%mod;
}