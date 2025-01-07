#include <bits/stdc++.h>
#define int long long
using namespace std;
int st[3001][3001];
int q[1000001];
int ans;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n,k;
	cin>>n>>k;
	for(int i=1;i<=n;i++)for(int j=1;j<=i;j++)cin>>st[i][j];

	int p=2;
	while (p<k){
		for(int x=1;x<=n-p+1;x++){
			int l=1,r=0;
			for(int y=1;y<=(p>>1);y++){
				while (l<=r&&st[x+(p>>1)][y]>=st[x+(p>>1)][q[r]]) --r;
				q[++r]=y;
			}
			for(int y=1;y<=x;y++){
				while (l<=r&&q[l]<y) ++l;
				while (l<=r&&st[x+(p>>1)][y+(p>>1)]>=st[x+(p>>1)][q[r]]) --r;
				q[++r]=y+(p>>1);
				st[x][y]=max(st[x][y],st[x+(p>>1)][q[l]]);
			}
		}
		p*=2;
	}
	p>>=1;

	for(int x=1;x<=n-k+1;x++){
		int l=1,r=0;
		for(int y=1;y<=k-p;y++){
			while (l<=r&&st[x+k-p][y]>=st[x+k-p][q[r]]) --r;
			q[++r]=y;
		}
		for(int y=1;y<=x;y++){
			while (l<=r&&q[l]<y) ++l;
			while (l<=r&&st[x+k-p][y+k-p]>=st[x+k-p][q[r]]) --r;
			q[++r]=y+k-p;
			ans+=max(st[x][y],st[x+k-p][q[l]]);
		}
	}
	cout<<ans;
}