#include<bits/stdc++.h>
using namespace std;
const int N=1e4+10;
struct node{
	int b[20],Max;
}a[N];
bool cmp(const node &x,const node &y){return x.Max>y.Max;}
int w[N],dp[13][N];
void solve(){
	memset(dp,0,sizeof dp);
	memset(a,0,sizeof a);
	int n,m;
	cin>>n>>m;
	for(int i=0;i<n;i++) {
		for(int j=0;j<m;j++) {
			cin>>a[j].b[i];
			a[j].Max=max(a[j].Max,a[j].b[i]);
		}
	}
	sort(a,a+m,cmp);
	for(int i=0;i<min(n,m);i++) {
		for(int j=0;j<(1<<n);j++){
			w[j]=0;
			for(int k=0;k<n;k++) {
				int tmp=0;
				for(int l=0;l<n;l++)if(j&(1<<l)) tmp+=a[i].b[(l+k)%n];
				w[j]=max(w[j],tmp);
			}
		}
		for(int j=0;j<(1<<n);j++){
			if(i==0){
				dp[i][j]=w[j];
				continue;
			}
			for(int k=j;k;k=(k-1)&j) {
				dp[i][j]=max(dp[i][j],dp[i-1][k]+w[k^j]);
			}
		}
	}
	cout<<dp[min(n,m)-1][(1<<n)-1]<<"\n";
}
int main(){
	int T;
	cin>>T;
	while(T--) solve();
}