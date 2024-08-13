#include<bits/stdc++.h>
using namespace std;
const int N=50+10,M=1e6;
struct node {
	int v,nex;
}a[M];
int first[M],cnt;
void add(int u,int v) {
	a[++cnt]={v,first[u]};
	first[u]=cnt;
}
int match[M];
bool vis[M];
bool del[M];
bool dfs(int u) {
	for(int i=first[u];i;i=a[i].nex) {
		int v=a[i].v;
		if(del[v]||vis[v])continue;
		vis[v]=true;
		if(!match[v]||dfs(match[v])) {
			match[v]=u;
			match[u]=v;
			return true;
		}
	}
	return false;
}
int mp[N][N];
int n,m;
int f(int x,int y) {return (x-1)*m+y;}
int dx[4]={0,-1,0,1};
int dy[4]={1,0,-1,0};
int sx,sy;
bool win[N*20];
int main() {
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	cin>>n>>m;
	for(int i=1;i<=n;i++) {
		string s;
		cin>>s;
		for(int j=1;j<=m;j++) {
			if(s[j-1]=='O')mp[i][j]=0;
			else if(s[j-1]=='X')mp[i][j]=1;
			else sx=i,sy=j,mp[i][j]=1;
		}
	}
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=m;j++) {
			if(!mp[i][j])continue;
			for(int k=0;k<4;k++) {
				int x=i+dx[k];
				int y=j+dy[k];
				if(x<1||x>n||y<1||y>m||mp[x][y])continue;
				add(f(i,j),f(x,y));
				add(f(x,y),f(i,j));
			}
		}
	}
	int sum=0;
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=m;j++) {
			if(mp[i][j])continue;
			memset(vis,false,sizeof vis);
			if(dfs(f(i,j)))sum++;
		}
	}
	int k;
	cin>>k;
	for(int i=1;i<=2*k;i++) {
		del[f(sx,sy)]=true;
		if(!match[f(sx,sy)])win[i]=false;
		else {
			memset(vis,false,sizeof vis);
			int tmp=match[f(sx,sy)];
			match[f(sx,sy)]=match[tmp]=0;
			if(dfs(tmp))win[i]=false;
			else win[i]=true;
		}
		cin>>sx>>sy;
	}
	vector<int>ans;
	for(int i=1;i<=k;i++)if(win[2*i-1]&&win[2*i])ans.push_back(i);
	cout<<ans.size()<<"\n";
	for(int i:ans)cout<<i<<"\n";
}