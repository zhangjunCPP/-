#include <bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int a[N],b[N];
int sum[5][5];
int main() {
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i],b[i]=a[i];
	sort(b+1,b+n+1);
	for(int i=1;i<=n;i++)if(a[i]!=b[i])sum[a[i]][b[i]]++;
	int ans=0;
	for(int i=1;i<=4;i++)
		for(int j=1;j<=4;j++) {
			int tmp=min(sum[i][j],sum[j][i]);
			ans+=tmp;
			sum[i][j]-=tmp,sum[j][i]-=tmp;
		}
	for(int i=1;i<=4;i++)
		for(int j=1;j<=4;j++)
			for(int k=1;k<=4;k++){
				int tmp=min({sum[i][j],sum[j][k],sum[k][i]});
				ans+=2*tmp;
				sum[i][j]-=tmp,sum[j][k]-=tmp,sum[k][i]-=tmp;
			}
	for(int i=1;i<=4;i++)
		for(int j=1;j<=4;j++)
			for(int k=1;k<=4;k++)
				for(int l=1;l<=4;l++){
					int tmp=min({sum[i][j],sum[j][k],sum[k][l],sum[l][i]});
					ans+=tmp*3;
					sum[i][j]-=tmp,sum[j][k]-=tmp,sum[k][l]-=tmp,sum[l][i]-=tmp;
				}
	cout<<ans;
}