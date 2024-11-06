//扒的最短解
#include <bits/stdc++.h>
#define ll long long
#define mid ((l+r)/2)
using namespace std;
const int N=1e6+5;
const ll INF=1e18;
int T,n,l,r,a[N],b[N];
bool dp[N];
bool chk1(int x,int y,int w){ return x&&y?abs(b[x]-b[y])<=1ll*abs(a[x]-a[y])*w:1; }
bool chk(int w){
	fill(dp+1,dp+n+1,0);
	dp[1]=1;
	for(int i=2,t=1;i<=n;++i){
		if(chk1(i,i-1,w)){ if(chk1(i,t-1,w))dp[i]=1; } else{
			for(int j=t;j<i;++j)if(dp[j]&&chk1(i,j-1,w)){
				dp[i]=1;
				break;
			}
			if(!dp[i]) return 0;
			t=i;
		}
	}
	return 1;
}
void slv(){
	scanf("%d",&n);
	l=0;
	r=1e9;
	for(int i=1;i<=n;++i) scanf("%d %d",&a[i],&b[i]);
	while(l<r)if(chk(mid))r=mid;
	else l=mid+1;
	printf("%d\n",l<1e9?l:-1);
}
int main(){
	scanf("%d",&T);
	while(T--)slv();
	return 0;
}