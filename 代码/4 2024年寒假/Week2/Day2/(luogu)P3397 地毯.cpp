#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e3+10;
int diff[N][N];
signed main() {
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int x_1,y_1,x_2,y_2;
		cin>>x_1>>y_1>>x_2>>y_2;
		diff[x_1][y_1]++;
		diff[x_1][y_2+1]--;
		diff[x_2+1][y_1]--;
		diff[x_2+1][y_2+1]++;
	}
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=n;j++){
			diff[i][j]+=diff[i-1][j]+diff[i][j-1]-diff[i-1][j-1];
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			cout<<diff[i][j]<<" ";
		}
		cout<<"\n";
	}
	return 0;
}