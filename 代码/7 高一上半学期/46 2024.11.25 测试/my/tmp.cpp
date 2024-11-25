#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=2000+10;
const ll INF=1e18;
int n,m,k,t;
int mp[N][N];
struct node{
	int x,y;
	ll val;
	bool operator<(const node&oth)const{return val>oth.val;}
};
ll dis[N][N];
bool vis[N][N];
int dx[4]={-1,0,1,0};
int dy[4]={0,1,0,-1};
inline bool check(int x,int y){
	if(x>n||x<1||y>m||y<1||!mp[x][y])return false;
	return true;
}
int main(){
	freopen("maze.in","r",stdin);
	freopen("maze.out","w",stdout);
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	cin>>n>>m>>k>>t;
	int sx,sy,tx,ty;
	for(int i=1;i<=n;i++){
		string s;
		cin>>s;
		for(int j=1;j<=m;j++){
			if(s[j-1]=='.')mp[i][j]=1;
			if(s[j-1]=='#')mp[i][j]=0;
			if(s[j-1]=='S')sx=i,sy=j,mp[i][j]=1;
			if(s[j-1]=='T')tx=i,ty=j,mp[i][j]=1;
		}
	}
	priority_queue<node> q;
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)dis[i][j]=INF;
	q.push({sx,sy,0});
	dis[sx][sy]=0;
	while(!q.empty()){
		auto now=q.top();q.pop();
		int x=now.x,y=now.y;
		int val=now.val;
		if(vis[x][y])continue;
		vis[x][y]=true;
		for(int i=0;i<4;i++){
			int Dx=x+dx[i];
			int Dy=y+dy[i];
			if(!check(Dx,Dy))continue;
			if(dis[Dx][Dy]>val+1){
				dis[Dx][Dy]=val+1;
				q.push({Dx,Dy,dis[Dx][Dy]});
			}
		}
		for(int i=1;i<=k;i++){
			for(int ddx=0;ddx<=i;ddx++){
				int ddy=i-ddx;
				auto calc=[&](int x,int y){
					if(check(x,y)&&dis[x][y]>val+t){
						dis[x][y]=val+t;
						q.push({x,y,dis[x][y]});
					}
				};
				int Dx=x+ddx;
				int Dy=y+ddy;
				calc(Dx,Dy);
				Dx=x+ddx;
				Dy=y-ddy;
				calc(Dx,Dy);
				Dx=x-ddx;
				Dy=y+ddy;
				calc(Dx,Dy);
				Dx=x-ddx;
				Dy=y-ddy;
				calc(Dx,Dy);
			}
		}
	}
	if(dis[tx][ty]==INF)dis[tx][ty]=-1;
	cout<<dis[tx][ty];
}