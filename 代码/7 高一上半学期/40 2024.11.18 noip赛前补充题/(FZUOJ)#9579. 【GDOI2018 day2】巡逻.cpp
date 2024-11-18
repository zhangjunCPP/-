#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=400+10;
const int INF=1e9;
int n;
int val[N][N];
bool flag[N];
pair<int,int> dis[N][2];
bool vis[N];
int solve(int s){
	for(int i=1;i<=n;i++){
		dis[i][0]={INF,0};
		dis[i][1]={INF,0};
		vis[i]=false;
	}
	dis[s][0]=dis[s][1]={0,s};
	for(int k=1;k<=n;k++){//不优化dij
		int pos=0;
		for(int i=1;i<=n;i++){
			if(!vis[i]){
				if(!pos)pos=i;
				else if(dis[i][0].first<dis[pos][0].first)pos=i;
			}
		}
		if(!pos)break;
		vis[pos]=true;
		for(int i=1;i<=n;i++){
			if(flag[i]&&val[pos][i]!=-1){
				for(int opt=0;opt<=1;opt++){
					pair<int,int> tmp={dis[pos][opt].first+val[pos][i],dis[pos][opt].second};
					if(pos==s)tmp.second=i;
					if(tmp.first<dis[i][0].first){
						if(tmp.second!=dis[i][0].second)dis[i][1]=dis[i][0];
						dis[i][0]=tmp;
					}
					else if(tmp.first<dis[i][1].first&&tmp.second!=dis[i][0].second)dis[i][1]=tmp;				}
			}
		}
	}
	int ans=INF;
	for(int i=1;i<=n;i++)if(i!=s&&flag[i])ans=min(ans,dis[i][0].first+dis[i][1].first);
	if(ans==INF)ans=-1;
	return ans;
}
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	cin>>n;
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)cin>>val[i][j];
	for(int i=1;i<=n;i++)flag[i]=true;
	int q;
	cin>>q;
	while(q--){
		int opt,x;
		cin>>opt>>x;
		if(opt)flag[x]^=1;
		else cout<<solve(x)<<"\n";
	}
}