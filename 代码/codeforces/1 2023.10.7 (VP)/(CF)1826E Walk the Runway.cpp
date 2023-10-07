#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e3+10,M=5e2+10;
int n,m;
int p[N]; 
int r[N][M];
bitset<N> flag[N];
int id[N];
int tmp;
bool cmp(const int &x,const int &y){return r[x][tmp]<r[y][tmp];}
int dp[N];
bitset<N> now;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>m>>n;
	for(int i=1;i<=n;i++) id[i]=i,flag[i].set();
	for(int i=1;i<=n;i++) cin>>p[i];
	for(int j=1;j<=m;j++)for(int i=1;i<=n;i++) cin>>r[i][j];
	for(int i=1;i<=m;i++){
		now.reset();
		now[0]=1;
		tmp=i;
		sort(id+1,id+n+1,cmp); 
		for(int j=1;j<=n;j++) {
			int k=j;
			while(k<n && r[id[k+1]][tmp]==r[id[j]][tmp]) k++;
			for(int l=j;l<=k;l++) flag[id[l]]&=now;
			for(int l=j;l<=k;l++) now[id[l]]=1;
			j=k;
		}
	}
	for(int i=1;i<=n;i++) {
		for(int j=0;j<i;j++ ) {
			if(flag[id[i]][id[j]]) dp[i]=max(dp[i],dp[j]+p[id[i]]);
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++) ans=max(ans,dp[i]);
	cout<<ans;
	return 0;
}