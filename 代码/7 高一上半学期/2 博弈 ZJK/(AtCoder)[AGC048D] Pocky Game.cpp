#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=100+10;
int a[N];
int L[N][N],R[N][N];
void solve() {
	int n;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) L[i][i]=R[i][i]=1;
	for(int i=n-1;i>=1;i--){
		for(int j=i+1;j<=n;j++){
			if(R[i+1][j]>a[j]) L[i][j]=1;
			else L[i][j]=L[i][j-1]+(a[j]-R[i+1][j]+1);
			if(L[i][j-1]>a[i]) R[i][j]=1;
			else R[i][j]=R[i+1][j]+(a[i]-L[i][j-1]+1);
		}
	}
	if(L[1][n]<=a[1]) puts("First");
	else puts("Second");
}
signed main(){
	int T;
	cin>>T;
	while(T--)solve();
}