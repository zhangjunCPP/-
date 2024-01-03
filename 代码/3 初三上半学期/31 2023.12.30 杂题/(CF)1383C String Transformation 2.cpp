#include<bits/stdc++.h>
using namespace std;
const int N=1e7+10;
int fa[N];
int G[N];
int dp[N];
int find(int x){
	if(fa[x]!=x) fa[x]=find(fa[x]);
	return fa[x];
}
void solve(){
	int n;
	cin>>n;
	string s,t;
	cin>>s>>t;
	for(int i=0;i<=25;i++)fa[i]=i,G[i]=0;
	for(int i=0;i<(1<<20);i++)dp[i]=0;
	for(int i=0;i<n;i++){
		int u=s[i]-'a',v=t[i]-'a';
		G[u]|=(1<<v);
		int fu=find(u),fv=find(v);
		if(fu!=fv)fa[fu]=fv;
	}
	int ans=2*20;
	dp[0]=1;
	for(int i=0;i<20;i++)if(fa[i]==i) ans--;
	int Max=-1;
	for(int i=0;i<(1<<20);i++){
		if(dp[i]){
			Max=max(Max,__builtin_popcount(i));
			for(int j=0;j<20;j++)if( !(i&(1<<j)) && ((i&G[j])==0) ) dp[i|(1<<j)]=1;
		}
	}
	cout<<ans-Max<<"\n";
}
int main(){
	int T;
	cin>>T;
	while(T--) solve();
}
