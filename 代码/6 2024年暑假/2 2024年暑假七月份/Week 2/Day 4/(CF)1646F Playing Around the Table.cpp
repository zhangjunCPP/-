#include <bits/stdc++.h>
using namespace std;
const int N=100+10;
int sum[N][N];
int ans[N*N][N],cnt;
int main() {
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int n;
	cin>>n;
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=n;j++) {
			int x;
			cin>>x;
			sum[i][x]++;
		}
	}
	while(true) {
		int swap=0;
		int start=0;
		for(int i=1;i<=n;i++) {
			for(int j=1;j<=n;j++) {
				if(sum[i][j]>1) {
					ans[++cnt][i]=j;
					sum[i][j]--;
					start=i,swap=j;
					break;
				}
			}
			if(swap)break;
		}
		if(!swap)break;
		for(int k=start+1;k<start+n;k++) {
			int i=(k-1)%n+1;
			sum[i][swap]++;
			for(int j=1;j<=n;j++) {
				if(sum[i][j]>1) {
					ans[cnt][i]=j;
					sum[i][j]--;
					swap=j;
					break;
				}
			}
		}
		sum[start][swap]++;
	}
	for(int i=2;i<=n;i++) {
		for(int j=1;j<i;j++) {
			cnt++;
			for(int k=i,l=0;k<i+n;k++,l++)ans[cnt][(j+l-1)%n+1]=(k-1)%n+1;
		}
	}
	cout<<cnt<<"\n";
	for(int i=1;i<=cnt;i++) {
		for(int j=1;j<=n;j++)cout<<ans[i][j]<<" ";
		cout<<"\n";
	}
}