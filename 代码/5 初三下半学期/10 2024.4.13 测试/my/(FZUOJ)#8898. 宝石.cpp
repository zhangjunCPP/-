#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
int x[N],p[N];
int pos[N];
int dis(int u,int v){return (u&&v?llabs(x[u]-x[v]):0);}
int ans[N];
bool vis[N],vis2[N];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int n,m;
	cin>>n>>m;
	bool flag=true;
	for(int i=1;i<=n;i++){
		cin>>x[i]>>p[i];
		pos[p[i]]=i;
		if(p[i]!=i)flag=false;
	}
	if(flag){for(int i=1;i<=n;i++)cout<<i<<" ";return 0;}
	int l=1,r=n;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(!vis[j]&&(dis(pos[ans[i-1]],pos[j])+min(dis(l,pos[j]),dis(pos[j],r))+dis(l,r))<=m){
				m-=dis(pos[ans[i-1]],pos[j]);
				vis[j]=true;
				vis2[pos[j]]=true;
				while(vis2[l])l++;
				while(vis2[r])r--;
				ans[i]=j;
				break;
			}
		}
	}
	for(int i=1;i<=n;i++)cout<<ans[i]<<" ";
	return 0;
}