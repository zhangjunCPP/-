#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2005;
int f[N][N];
struct node{
	int val,id;
}a[N];
bool cmp(const node&x,const node&y){return x.val>y.val;}
int fa[N];
vector<int>G[N];
int siz[N];
void dfs(int u){
	siz[u]=1;
	for(int v:G[u]){
		dfs(v);
		siz[u]+=siz[v];
	}
}
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)for(int j=1;j<=i;j++)cin>>f[i][j],f[j][i]=f[i][j];
	for(int i=1;i<=n;i++)a[i]={f[1][i],i};
	sort(a+1,a+n+1,cmp);
	for(int i=2;i<=n;i++){
		int now=a[i].id;
		int pos=1;
		for(int j=2;j<i;j++)if(f[now][a[j].id]>f[now][a[pos].id])pos=j;
		fa[now]=a[pos].id;
		G[fa[now]].push_back(now);
	}
	dfs(1);
	for(int i=2;i<=n;i++)cout<<i<<" "<<fa[i]<<" "<<(f[i][i]-f[i][fa[i]])/(n-siz[i])<<"\n";
}