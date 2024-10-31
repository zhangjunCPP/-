#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+10;
int a[N],p[N];
bool vis[N];
int fa[N];
int find(int x){
	if(fa[x]!=x)fa[x]=find(fa[x]);
	return fa[x];
}
int Max[N];
vector<pair<int,int>>G;
void solve(){
	int n;
	cin>>n;
	G.clear();
	for(int i=1;i<=n;i++)cin>>a[i],p[i]=i,fa[i]=i,vis[i]=false,Max[i]=a[i];
	sort(p+1,p+n+1,[](const int&x,const int&y){return a[x]>a[y];});
	for(int i=1;i<=n;i++){
		if(p[i]+1<=n){
			if(!vis[p[i]]){
				G.emplace_back(p[i],p[i]+1);
				vis[p[i]]=true;
			}
		}
		if(p[i]-1>=1){
			if(!vis[p[i]-1]){
				G.emplace_back(p[i],p[i]-1);
				vis[p[i]-1]=true;
			}
		}
	}
	reverse(G.begin(),G.end());
	int ans=0;
	for(int i=0;i<G.size();i++){
		int x=G[i].first,y=G[i].second;
		int fx=find(x),fy=find(y);
		if(fx==fy)continue;
		ans+=llabs(Max[fx]-Max[fy]);
		fa[fx]=fy;
		Max[fy]=max(Max[fy],Max[fx]);
	}
	cout<<ans<<"\n";
}
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int c;
	int T;
	cin>>c>>T;
	while(T--)solve();
}