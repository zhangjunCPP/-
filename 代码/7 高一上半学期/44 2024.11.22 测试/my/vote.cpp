#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
int f[N],a[N],b[N];
vector<int> G[N];
int val[N];
bool vis[N];
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int n,q;
	cin>>n>>n>>q;
	for(int i=2;i<=n;i++)cin>>f[i],G[f[i]].push_back(i);
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)cin>>b[i];
	while (q--){
		int opt;
		cin>>opt;
		if(opt==1){
			int p,x,y;
			cin>>p>>x>>y;
			a[p]=x,b[p]=y;
		}
		else{
			int x,y;
			cin>>x>>y;
			for(int i=1;i<=n;i++)vis[i]=false;
			priority_queue<pair<int,int>>q;
			for(int i=1;i<=n;i++){
				val[i]=a[i];
				for(int it:G[i])val[i]+=b[it];
				q.push({val[i],i});
			}
			while(!q.empty()){
				auto now=q.top();q.pop();
				if(now.first!=val[now.second])continue;
				int u=now.second;
				vis[u]=true;
				if(u==x){cout<<"0\n";break;}
				if(u==y){cout<<"1\n";break;}
				if(!vis[f[u]])val[f[u]]-=b[u],q.push({val[f[u]],f[u]});
			}
		}
	}
	
}