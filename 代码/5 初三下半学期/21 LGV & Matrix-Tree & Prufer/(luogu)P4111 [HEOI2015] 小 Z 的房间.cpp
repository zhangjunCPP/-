#include <bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9;
const int N=1e3+10;
int mp[N][N];
int id[N][N],cnt;
int a[N][N];
void add(int u,int v){a[u][v]--,a[v][u]--;a[u][u]++,a[v][v]++;}
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		string s;
		cin>>s;
		for(int j=1;j<=m;j++)mp[i][j]=s[j-1]=='.'?1:0;
	}
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)if(mp[i][j])id[i][j]=++cnt;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(mp[i][j]&&mp[i+1][j])add(id[i][j],id[i+1][j]);
			if(mp[i][j]&&mp[i][j+1])add(id[i][j],id[i][j+1]);
		}
	}
	cnt--;
	int opt=1;
	for(int i=1;i<=cnt;i++){
		for(int j=i+1;j<=cnt;j++){
			while(a[i][i]){
				int tmp=a[j][i]/a[i][i];
				for(int k=i;k<=cnt;k++)a[j][k]=(a[j][k]-tmp*a[i][k]%mod+mod)%mod;
				swap(a[i],a[j]);opt=-opt;
			}
			swap(a[i],a[j]);opt=-opt;
		}
	}
	int ans=1;
	for(int i=1;i<=cnt;i++)ans=ans*a[i][i]%mod;
	ans=ans*opt;
	cout<<(ans+mod)%mod;
}