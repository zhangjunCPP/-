#include<bits/stdc++.h>
using namespace std;
const int N=1000+10;
int a[N],b[N],c[N];
int dp[N][N];
int pos[N][N];
vector<pair<int,int>>ans,G[2];
void dfs(int x,int y){
	if(!x&&!y) return;
	if(pos[x][y]<2){
		if(a[x+y]<=b[x])G[1].emplace_back(b[x],a[x+y]);
		else G[0].emplace_back(b[x],a[x+y]);
		dfs(x-1,y);
	}
	else{
		if(a[x+y]<=c[y])G[1].emplace_back(c[y],a[x+y]);
		else G[0].emplace_back(c[y],a[x+y]);
		dfs(x,y-1);
	}
}
int main(){
	int n,C;
	string s,t;
	cin>>n>>C>>s>>t;
	int tot1=0,tot2=0;
	for(int i=0,j=0;i<n;i++)if(s[i]=='2')a[++j]=i+1;
	for(int i=0;i<n;i++){
		if(t[i]=='2'){
			if(i&1)b[++tot1]=i+1;
			else c[++tot2]=i+1;
		}
	}
	memset(dp,0x3f,sizeof dp);
	dp[0][0]=0;
	for(int i=0;i<=tot1;i++){
		for(int j=0;j<=tot2;j++){
			if(i<tot1){
				int val=dp[i][j]+abs(a[i+j+1]-b[i+1])/2*(C+4)+abs(a[i+j+1]-b[i+1])%2*(C+3);
				for(int k=1;k<=j;k++)val+=(c[k]>b[i+1]);
				if(dp[i+1][j]>val)dp[i+1][j]=val,pos[i+1][j]=1;
			}
			if(j<tot2){
				int val=dp[i][j]+abs(a[i+j+1]-c[j+1])/2*(C+4)+abs(a[i+j+1]-c[j+1])%2*(C+3);
				for(int k=1;k<=i;k++)val+=(b[k]>c[j+1]);
				if(dp[i][j+1]>val)dp[i][j+1]=val,pos[i][j+1]=2;
			}
		}
	}
	dfs(tot1,tot2);
	sort(G[0].begin(),G[0].end());
	sort(G[1].begin(),G[1].end());
	reverse(G[1].begin(),G[1].end());
	for(auto it:G[1]){
		int u=it.first,v=it.second;
		while(u-v>=2)ans.emplace_back(v,v+2),v+=2;
		if(u!=v)ans.emplace_back(v,u);
	}
	for(auto it:G[0]){
		int u=it.second,v=it.first;
		while(u-v>=2)ans.emplace_back(u-2,u),u-=2;
		if(u!=v)ans.emplace_back(v,u);
	}
	cout<<ans.size()<<"\n";
	for(auto it:ans)cout<<it.first<<" "<<it.second<<"\n";
	return 0;
}