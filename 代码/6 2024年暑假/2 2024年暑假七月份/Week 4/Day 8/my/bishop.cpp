#include<bits/stdc++.h>
using namespace std;
int n,m;
bool vis[1000];
vector<pair<int,int>>tmp;
vector<pair<int,int>>ans;
int Max;
void dfs(int k,int sum) {
	if(k>n+m-1) {
		if(sum>Max)Max=sum,ans=tmp;
		return;
	}
	for(int x=1;x<=min(n,k);x++) {
		int y=k+1-x;
		if(y>m)continue;
		if(vis[x-y+m])continue;
		vis[x-y+m]=true;
		tmp.emplace_back(x,y);
		dfs(k+1,sum+1);
		tmp.pop_back();
		vis[x-y+m]=false;
	}
	dfs(k+1,sum);
}
int main() {
	freopen("bishop.in","r",stdin);
	freopen("bishop.out","w",stdout);
	cin>>n>>m;
	if(n==2) {
		cout<<(m+1)/2*2<<"\n";
		for(int i=1;i<=m;i+=2)cout<<"1 "<<i<<"\n"<<"2 "<<i<<"\n";
		return 0;
	}
	if(n==m) {
		cout<<m*2-2<<"\n";
		for(int i=1;i<=m;i++)cout<<"1 "<<i<<"\n";
		for(int i=2;i<m;i++)cout<<n<<" "<<i<<"\n";
		return 0;
	}
	dfs(1,0);
	cout<<Max<<"\n";
	for(auto i:ans)cout<<i.first<<" "<<i.second<<"\n";
}