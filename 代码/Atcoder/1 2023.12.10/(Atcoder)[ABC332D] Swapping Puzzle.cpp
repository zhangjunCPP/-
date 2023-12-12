#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=50;
int a[N][N],b[N][N];
int ans1[N],ans2[N];
signed main(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)cin>>a[i][j];
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)cin>>b[i][j];
	bool flag=true;
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)if(a[i][j]!=b[i][j]){flag=false;break;}
	if(flag){cout<<0;return 0;}
	for(int i=1;i<=n;i++)ans1[i]=i;
	for(int i=1;i<=m;i++)ans2[i]=i;
	int ans=0x3f3f3f3f;
	while(next_permutation(ans1+1,ans1+n+1)) {
		do{
			flag=true;
			for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)if(a[ans1[i]][ans2[j]]!=b[i][j]) {flag=false;break;}
			if(!flag) continue;
			int tmp=0;
			for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)if(i<j&&ans1[i]>ans1[j]) tmp++;
			for(int i=1;i<=m;i++)for(int j=1;j<=m;j++)if(i<j&&ans2[i]>ans2[j]) tmp++;
			ans=min(ans,tmp);
		}while(next_permutation(ans2+1,ans2+m+1));
	}
	if(ans==0x3f3f3f3f) ans=-1;
	cout<<ans;
	return 0;
}
