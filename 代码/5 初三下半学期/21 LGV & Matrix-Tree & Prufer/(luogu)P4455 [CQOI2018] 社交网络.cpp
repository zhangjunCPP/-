#include <bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e4+7;
const int N=1e3+10;
int a[N][N];
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int x,y;
		cin>>x>>y;
		a[x][x]++,a[y][x]--;
	}
	int opt=1;
	for(int i=2;i<=n;i++){
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
	for(int i=2;i<=n;i++)ans=ans*a[i][i]%mod;
	ans=ans*opt;
	cout<<(ans+mod)%mod;
}