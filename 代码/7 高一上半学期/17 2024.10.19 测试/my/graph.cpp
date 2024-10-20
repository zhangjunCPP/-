#include<bits/stdc++.h>
using namespace std;
const int N=2e3+10,INF=1e9;
int n;
struct node{
	int dis[N][N];
	void init(){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++)dis[i][j]=INF;
			dis[i][i]=0;
		}
		for(int i=1;i<n;i++){
			int u,v,w;
			cin>>u>>v>>w;
			dis[u][v]=dis[v][u]=w;
		}
		for(int k=1;k<=n;k++)
			for(int i=1;i<=n;i++)
				for(int j=1;j<=n;j++)dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
	}
}tree1,tree2;
int fa[N];
int find(int x){
	if(fa[x]!=x)fa[x]=find(fa[x]);
	return fa[x];
}
int w[N][N];
struct node2{
	int u,v,val;
};
vector<node2> v;
bool cmp(const node2&x,const node2&y){return x.val<y.val;}
int main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	freopen("graph.in","r",stdin);
	freopen("graph.out","w",stdout);
	cin>>n;
	tree1.init();
	tree2.init();
	for(int i=1;i<=n*2;i++)fa[i]=i;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			for(int x=1;x<=n;x++)
				w[i][j]=max(w[i][j],tree1.dis[i][x]+tree2.dis[j][x]);
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)v.push_back({i,j+n,w[i][j]});
	sort(v.begin(),v.end(),cmp);
	int tot=0,ans=0;
	for(auto it:v){
		int fx=find(it.u),fy=find(it.v);
		if(fx!=fy){
			fa[fx]=fy;
			tot++;
			ans+=it.val;
			if(tot==2*n-1)break;
		}
	}
	cout<<ans;
}