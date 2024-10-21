#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=4e5+10;
const int mod=1e9+7;
int n,m,q;
int qpow(int x,int y){
	int ans=1;
	while(y){
		if(y&1)ans=ans*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return ans;
}
int f(int x,int y){return (x-1)*m+y;}
int mp[100];
int ans;
void dfs(int k){
	if(k>n*m){
		for(int i=1;i<n;i++){
			for(int j=1;j<m;j++){
				int sum=0;
				sum+=mp[f(i,j)]==1;
				sum+=mp[f(i,j+1)]==1;
				sum+=mp[f(i+1,j)]==1;
				sum+=mp[f(i+1,j+1)]==1;
				if(sum&1)return;
			}
		}
		ans++;
		return;
	}
	if(mp[k]){dfs(k+1);return;}
	mp[k]=1;
	dfs(k+1);
	mp[k]=2;
	dfs(k+1);
	mp[k]=0;
}
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	cin>>n>>m>>q;
	cout<<qpow(2,n+m-1)<<'\n';
	while(q--){
		int x,y,c;
		cin>>x>>y>>c;
		c++;
		mp[f(x,y)]=c;
		ans=0;
		dfs(1);
		cout<<ans<<'\n';
	}
}