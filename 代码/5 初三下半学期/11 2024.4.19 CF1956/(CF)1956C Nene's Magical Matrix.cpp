#include<bits/stdc++.h>
using namespace std;
const int N=510;
int a[N][N];
void solve(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		for(int j=n;j>=1;j--)a[i][n-j+1]=j;
		for(int j=n;j>=1;j--)a[n-j+1][i]=j;
	}
	int sum=0;
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)sum+=a[i][j];
	cout<<sum<<" "<<2*n<<"\n";
	for(int i=1;i<=n;i++){
		cout<<"1 "<<i<<" ";
		for(int j=n;j>=1;j--)cout<<j<<" ";
		cout<<"\n";
		cout<<"2 "<<i<<" ";
		for(int j=n;j>=1;j--)cout<<j<<" ";
		cout<<"\n";
	}
}
int main(){
	int T;
	cin>>T;
	while(T--)solve();
}