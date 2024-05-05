#include<bits/stdc++.h>
using namespace std;
const int N=710+10;
int a[N][N];
int main(){
	int n,m;
	cin>>n>>m;
	int Max=-0x3f3f3f3f,Min=0x3f3f3f3f;
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)cin>>a[i][j],Max=max(Max,a[i][j]),Min=min(Min,a[i][j]);
	int ans1=0,ans2=-1;
	for(int i=1;i<m;i++)if(a[1][i]>=a[1][i+1])ans1=-1;
	if(ans1==-1){
		cout<<"-1\n-1";
		return 0;
	}
	for(int i=2;i<=n;i++){
		int Minn=0x3f3f3f3f;
		for(int l=-1000;l<=1000;l++){
			int sum=0;
			for(int j=1;j<=m;j++){
				int now=l+a[1][j];
				sum+=abs(a[i][j]-now);
			}
			Minn=min(Minn,sum);
		}
		ans1+=Minn;
	}
	cout<<ans1<<"\n"<<ans2;
}