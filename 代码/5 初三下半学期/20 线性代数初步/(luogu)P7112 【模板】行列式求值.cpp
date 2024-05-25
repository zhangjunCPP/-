#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e3+10;
int n,mod;
int a[N][N];
signed main(){
	cin>>n>>mod;
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)cin>>a[i][j];
	int opt=1;
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			while(a[i][i]){
				int tmp=a[j][i]/a[i][i];
				for(int k=i;k<=n;k++)a[j][k]=(a[j][k]-tmp*a[i][k]%mod+mod)%mod;
				swap(a[i],a[j]);opt=-opt;
			}
			swap(a[i],a[j]);opt=-opt;
		}
	}
	int ans=1;
	for(int i=1;i<=n;i++)ans=ans*a[i][i]%mod;
	ans=ans*opt;
	cout<<(ans+mod)%mod;
}