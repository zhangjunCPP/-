#include <bits/stdc++.h>
using namespace std;
const int N=3000+10;
map<char,int>rev;
int mp[N][N];
int sum[N][N][4];
bool vis[N][N];
pair<int,int> nex[N][N][4];
int main(){
	ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr);
	rev['L']=0,rev['U']=1,rev['R']=2,rev['D']=3;
	int n,m,k;
	cin>>n>>m>>k;
	for(int i=0;i<=n+1;i++)for(int j=0;j<=m+1;j++)mp[i][j]=-1;
	for(int i=1;i<=n;i++){
		string s;
		cin>>s;
		for(int j=1;j<=m;j++)mp[i][j]=rev[s[j-1]];
	}
	for(int i=1;i<=n;i++){
		int near=-1;
		for(int j=0;j<=m+1;j++){//找r
			if((near==-1)||(j-near<=k))nex[i][j][2]={(near==-1?-1:i),near};
			else nex[i][j][2]={-1,-1};
			if(mp[i][j]==2)near=j;
		}
		near=-1;
		for(int j=m+1;j>=0;j--){//找l
			if((near==-1)||(near-j<=k))nex[i][j][0]={(near==-1?-1:i),near};
			else nex[i][j][0]={-1,-1};
			if(mp[i][j]==0)near=j;
		}
	}
	for(int j=1;j<=m;j++){
		int near=-1;
		for(int i=0;i<=n+1;i++){//找d
			if((near==-1)||(i-near<=k))nex[i][j][3]={near,(near==-1?-1:j)};
			else nex[i][j][3]={-1,-1};
			if(mp[i][j]==3)near=i;
		}
		near=-1;
		for(int i=n+1;i>=0;i--){//找u
			if((near==-1)||(near-i<=k))nex[i][j][1]={near,(near==-1?-1:j)};
			else nex[i][j][1]={-1,-1};
			if(mp[i][j]==1)near=i;
		}
	}
	queue<pair<int,int>>Q;
	for(int i=1;i<=n;i++)Q.emplace(i,0),Q.emplace(i,m+1);
	for(int i=1;i<=m;i++)Q.emplace(0,i),Q.emplace(n+1,i);
	while(!Q.empty()){
		auto u=Q.front();Q.pop();
		for(int l=0;l<4;l++){
			auto v=nex[u.first][u.second][l];
			if(v.first<=0||v.first>n||v.second<=0||v.second>m)continue;
			if(v.first!=-1&&v.second!=-1&&!vis[v.first][v.second])Q.emplace(v.first,v.second),vis[v.first][v.second]=true;
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)ans+=vis[i][j];
	cout<<ans;
}