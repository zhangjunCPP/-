#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10,INF=1e18;
int dis[N];
bool vis[N];
map<pair<int,int>,int> mp;
void solve(){
	mp.clear();
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int u,v,w;
		cin>>u>>v>>w;
		mp[{u,v}]=w;
		mp[{v,u}]=w;
	}
	if(m==0){cout<<n-1<<"\n";return;}
	for(int i=1;i<=n;i++)dis[i]=INF,vis[i]=false;
	dis[1]=0;
	int ans=0;
	for(int i=1;i<=n;i++){
		int u=-1;
		for(int j=1;j<=n;j++){
			if(!vis[j]){
				if(u==-1)u=j;
				else if(dis[j]<dis[u])u=j;
			}
		}
		// cout<<"i="<<i<<"\n";
		// cout<<"u="<<u<<"\n";
		if(u==-1)break;
		ans+=dis[u];
		// cout<<"ans="<<ans<<"\n";
		vis[u]=true;
		for(int j=1;j<=n;j++){
			if(!vis[j]){
				int val;
				if(mp.count({u,j}))val=mp[{u,j}];
				else val=llabs(u-j);
				dis[j]=min(dis[j],val);
			}
		}
	}
	cout<<ans<<"\n";
}
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int T;
	cin>>T;
	while(T--)solve();
}